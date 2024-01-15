#include "stdafx.h"

#ifdef __linux
#include <stdio.h>
#endif

#include "ObjectManager.h"
#include "Object.h"
#include "Mine.h"

ObjectManager::ObjectManager()
	: m_numberOfObjects(0)
	, m_nextFindTargetIndex(0)
{
}

ObjectManager::~ObjectManager()
{
}

static ObjectManager* s_pObjectManager;

ObjectManager& ObjectManager::GetSingleton()
{
	static ObjectManager* pSingletonInstance = new ObjectManager();
	return *pSingletonInstance;
}

void ObjectManager::AddMineObject(unsigned int aObjectId, float aPosition[3], int aTeam)
{
	MutexLock lock(m_lock);

	for (int i = 0; i < m_numberOfObjects; i++)
	{
		if (m_objects[i]->GetObjectId() == aObjectId)
		{
			// If objectId matches an existing entry then just consider it as getting updated (even potentially switched to a new team)
			Mine* pMineObject = new Mine();
			pMineObject->SetObjectId(m_objects[i]->GetObjectId());

			// pMineObject->m_team = m_objects[i]->m_team; - Incorrect
			// Object(Mine)'s team value should also be changed.
			// Original logic is also okay, but regarding your output example and deep analyzation, I guess below code is closer to what you were thinking before.
			pMineObject->SetTeam(aTeam); // Correct

			pMineObject->SetBitFlags(m_objects[i]->GetBitFlags());
			pMineObject->SetPosition(aPosition);
			pMineObject->SetDestructiveRadius(static_cast<Mine*>(m_objects[i])->GetDestructiveRadius());

			delete m_objects[i];
			m_objects[i] = pMineObject;

			return;
		}
	}

	if (m_numberOfObjects == cMaximumNumberOfObjects)
		return;

	m_objects[m_numberOfObjects] = new Mine();
	m_objects[m_numberOfObjects]->SetObjectId(aObjectId);
	m_objects[m_numberOfObjects]->SetTeam(aTeam);
	m_objects[m_numberOfObjects]->SetPosition(aPosition);
	static_cast<Mine*>(m_objects[m_numberOfObjects])->SetDestructiveRadius(GetRandomFloat32_Range(10.0f, 100.0f));

	bool active = (GetRandomFloat32() < 0.95f);
	m_objects[m_numberOfObjects]->SetActive(active);

	// if (GetRandomFloat32() < 0.1f)
	// {
	//	 m_objects[m_numberOfObjects]->m_bitFlags = Object::OBF_INVULNERABLE;
	// }
	// Above code is not perfect.
	// May be, Object can be both active & invulnerable.
	bool invulnerable = (GetRandomFloat32() < 0.1f);
	m_objects[m_numberOfObjects]->SetInvulnerable(invulnerable);

	m_numberOfObjects++;

	return;
}

void ObjectManager::RemoveObject(unsigned int aObjectId)
{
	for (int i = 0; i < m_numberOfObjects; i++)
	{
		if (m_objects[i]->GetObjectId() == aObjectId)
		{
			// Common practice to ensure the removal of the object upon the completion of this function.
			m_objects[i]->SetObjectId(MAXV);

			delete m_objects[i];

			// Do a fast remove and replace this location with object currently at end
			m_objects[i] = m_objects[m_numberOfObjects - 1];
			m_objects[m_numberOfObjects - 1] = nullptr;

			// When an object is removed, decrease m_numberOfObjects.
			// Originally, as below code is missing, some functions access to null reference.
			m_numberOfObjects--;

			// And also, break the loop to improve project performance.
			break;
		}
	}

	if (m_numberOfObjects % 100 == 0)
		printf("Number of objects in system %u\n", m_numberOfObjects);

	return;
}

Object* ObjectManager::GetObjectByObjectId(int aObjectId)
{
	for (int i = 0; i < m_numberOfObjects; i++)
	{
		if (m_objects[i]->GetObjectId() == aObjectId)
		{
			return m_objects[i];
		}
	}

	return NULL;
}

bool ObjectManager::IsValidObject(Object* apObject)
{
	for (int i = 0; i < m_numberOfObjects; i++)
	{
		if (m_objects[i] == apObject)
		{
			return true;
		}
	}

	return false;
}

int ObjectManager::GetNextFindTargetsIndex()
{
	MutexLock lock(m_lock);

	int index = m_nextFindTargetIndex;
	m_nextFindTargetIndex++;

	return index;
}

Object* ObjectManager::GetObjectWithMostEnemyTargets(int aTeam)
{
	Object* pBestObject = NULL;
	for (int i = 0; i < m_numberOfObjects; i++)
	{
		// Skip inactive objects.
		if (!m_objects[i]->GetActive()) {
			continue;
		}
		if (m_objects[i]->GetTeam() == aTeam)
		{
			if (pBestObject == NULL)
			{
				pBestObject = m_objects[i];
			}
			else if (static_cast<Mine*>(m_objects[i])->GetNumberOfEnemyTargets() > static_cast<Mine*>(pBestObject)->GetNumberOfEnemyTargets())
			{
				pBestObject = m_objects[i];
			}
		}
	}

	return pBestObject;
}

int ObjectManager::GetNumberOfObjectForTeam(int aTeam)
{
	int count = 0;
	for (int i = 0; i < m_numberOfObjects; i++)
	{
		if (m_objects[i]->GetTeam() == aTeam)
		{
			count++;
		}
	}

	return count;
}

void ObjectManager::RegenerateObjectsHealth()
{
	for (int i = 0; i < m_numberOfObjects; i++)
	{
		if (static_cast<Mine*>(m_objects[i])->GetShield()) {
			static_cast<Mine*>(m_objects[i])->RegenerateHealth();
		}
	}
}

int ObjectManager::GetNumberOfObjects()
{
	return m_numberOfObjects;
}

void ObjectManager::ResetNextFindTargetIndex()
{
	m_nextFindTargetIndex = 0;
}
