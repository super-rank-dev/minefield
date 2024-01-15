#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#pragma once

#include "Mutex.h"

#include <vector>

class Object;

const int cMaximumNumberOfObjects = 1000000;

class ObjectManager
{
public:

	static ObjectManager& GetSingleton();

	int GetNumberOfObjects();
	Object* GetObject(int aIndex) { return m_objects[aIndex]; };
	Object* GetObjectByObjectId(int aObjectId);
	bool IsValidObject(Object* apObject);

	void RemoveObject(unsigned int aObjectId);

	void AddMineObject(unsigned int aObjectId, float aPosition[3], int aTeam);

	int GetNextFindTargetsIndex();
	void ResetNextFindTargetIndex();

	Object* GetObjectWithMostEnemyTargets(int aTeam);
	int GetNumberOfObjectForTeam(int aTeam);

	void RegenerateObjectsHealth();

private:

	Mutex m_lock;
	int m_numberOfObjects;
	Object* m_objects[cMaximumNumberOfObjects];

	int m_nextFindTargetIndex;

	ObjectManager();

	~ObjectManager();
};

#endif // OBJECTMANAGER_H
