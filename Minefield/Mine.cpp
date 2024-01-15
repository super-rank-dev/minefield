#include "stdafx.h"

#ifdef __linux
#include <math.h>
#endif
#include "Mine.h"

#include "ObjectManager.h"

Mine::Mine()
{
	m_position = new float[3];
	m_team = 0;
	m_destructiveRadius = 0.0f;
	m_health = 100.0f;
	m_explosiveYield = 500;

	// Health bar, shield initialization.
	m_healthBar = 100.0f;
	m_shield = new Shield(this);
}

Mine::~Mine()
{
	// Explode();
	// delete m_position;
	// Rather than above code, to avoid confusing, only give damage.
	// When a mine is destroyed and it's active state, it also should be exploded and give damage to target mines.
	if (!GetActive()) {
		return;
	}
	GiveDamage();
}

void Mine::SetPosition(float* aPosition)
{
	for (int i = 0; i < 3; i++)
		m_position[i] = aPosition[i];
}

float Mine::GetDistance(float aPositionA[3], float aPositionB[3])
{
	float distance = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		// distance += pow((aPositionA[i] - aPositionB[i]), 2.0f); - Incorrect
		// Cannot convert double to float.
		distance += powf((aPositionA[i] - aPositionB[i]), 2.0f); // Correct
	}

	// return sqrt(distance); - Incorrect
	// Cannot return double.
	return sqrtf(distance); // Correct
}

// Invulnerable mines do not take damage, but can be manually exploded if they are active
void Mine::FindCurrentTargets()
{
	if (!GetActive())
	{
		return;
	}

	m_targetList.clear();

	for (int i = 0; i < ObjectManager::GetSingleton().GetNumberOfObjects(); ++i)
	{
		Object* pObject = ObjectManager::GetSingleton().GetObject(i);

		float distance = GetDistance(GetPosition(), pObject->GetPosition());
		if (distance > m_destructiveRadius)
		{
			// break; - Incorrect
			// If distance between 2 mines is longer than destructive radius, skip it, not break.
			continue;
		}

		// TODO: Any other reasons to not add this object?
		// Yes, of course. Below code contains additional conditions not to add this object.
		// May be, it could be better to write at the top of this loop to improve performance a bit.

		// Skip an object itself.
		if (pObject->GetObjectId() == GetObjectId()) continue;

		// Skip invulnerable mines regarding your description and output result.
		if (static_cast<Mine*>(pObject)->GetInvulnerable()) continue;

		m_targetList.push_back(pObject);
	}
}

int Mine::GetNumberOfEnemyTargets()
{
	int numberOfEnemyTargets = 0;
	for (unsigned int i = 0; i < m_targetList.size(); ++i)
	{
		// Potential problem exists here.
		// Some mines of m_targetList could have already been removed.
		// Then, it should be skipped.
		if (m_targetList[i]->GetObjectId() == MAXV) continue;

		if (static_cast<Mine*>(m_targetList[i])->GetTeam() != GetTeam())
		{
			numberOfEnemyTargets++;
		}
	}

	return numberOfEnemyTargets;
}

void Mine::Explode()
{
	// Original code is removed and implemented in TakeDamage function.
	// And also, explosion logic is changed a bit.
	// Now, mines are exploded and give damage to target mines recursively.
	// Destroy self
	TakeDamage(m_health);
}

void Mine::TakeDamage(float aDamage)
{
	//printf("%f\n", aDamage);
	m_health -= aDamage;

	// Reduce shield health.
	if (m_shield) {
		m_shield->TakeDamage(aDamage);
	}

	// if (m_health < 0.0f) { - Incorrect
	// Explode function gives m_health damage to itself.
	// It means, when a team explodes a mine, it's health should be 0.
	// Originally, some of mines are exploded twice but it's confusing.
	if (m_health <= 0.0f) { // Correct
		ObjectManager::GetSingleton().RemoveObject(GetObjectId());
	}
}

// Give damage to target mines.
void Mine::GiveDamage()
{
	for (unsigned int i = 0; i < m_targetList.size(); ++i)
	{
		// Potential problem exists here.
		// Some mines of m_targetList could have already been removed.
		// Then, it should be skipped.
		if (m_targetList[i]->GetObjectId() == MAXV) continue;

		float distance = GetDistance(GetPosition(), m_targetList[i]->GetPosition());

		// damage is inverse-squared of distance
		float factor = 1.0f - (distance / m_destructiveRadius);
		float damage = (factor * factor) * m_explosiveYield;
		static_cast<Mine*>(m_targetList[i])->TakeDamage(damage);
	}
}

Shield* Mine::GetShield()
{
	return m_shield;
}

void Mine::DestroyShield()
{
	delete m_shield;
	m_shield = nullptr;
}

void Mine::RegenerateHealth()
{
	m_shield->Regenerate();
}

float* Mine::GetPosition()
{
	return m_position;
}

float Mine::GetPositionByIndex(int aIndex)
{
	return m_position[aIndex];
}

float Mine::GetDestructiveRadius()
{
	return m_destructiveRadius;
}

float Mine::GetHealth()
{
	return m_health;
}

void Mine::SetHealth(float aHealth)
{
	m_health = aHealth;
}

float Mine::GetExplosiveYield()
{
	return m_explosiveYield;
}

float Mine::GetHealthBar()
{
	return m_healthBar;
}

void Mine::SetDestructiveRadius(float aDestructiveRadius)
{
	m_destructiveRadius = aDestructiveRadius;
}

int Mine::GetBitFlags()
{
	return m_bitFlags;
}

void Mine::SetBitFlags(int aBitFlags)
{
	m_bitFlags = aBitFlags;
}

int Mine::GetTeam()
{
	return m_team;
}

void Mine::SetTeam(int team) {
	m_team = team;
}