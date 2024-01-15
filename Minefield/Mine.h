#pragma once

#include "Object.h"
#include "Random.h"

#include "Shield.h"

#include <vector>

class Shield;

class Mine : public Object
{
public:
	Mine();
	// When an object is deleted, mine's destructor would be called.
	~Mine() override;

	float* GetPosition();
	void SetPosition(float* aPosition);

	float GetDistance(float aPositionA[3], float aPositionB[3]);
	void FindCurrentTargets();
	int GetNumberOfEnemyTargets();
	int GetTeam();
	void SetTeam(int team);
	void Explode();
	void TakeDamage(float aDamage);

	// A function needed to give damage to target mines.
	// For example, in TakeDamage function, when a mine is destroyed, it should also be exploded.
	// It means, it should also give damage to target mines.
	void GiveDamage();

	float GetPositionByIndex(int aIndex);					// Get position.
	float GetDestructiveRadius();							// Get destructive radius.
	void SetDestructiveRadius(float destructiveRadius);		// Set destructive radius.
	float GetHealth();										// Get mine health.
	void SetHealth(float aHealth);							// Set mine health.
	float GetExplosiveYield();								// Get explosive yield.

private:
	float* m_position;
	float m_destructiveRadius;
	float m_health;
	float m_explosiveYield;

	std::vector<Object*> m_targetList;

public:
	// Below functions are needed to implement additional logic.
	float GetHealthBar();									// Get mine's original health.
	Shield* GetShield();									// Get shield health.
	void DestroyShield();									// Destroy Shield when it's health is below 0.
	void RegenerateHealth();								// Regenerate mine health.

	void SetBitFlags(int aBitFlags);
	int GetBitFlags();

private:
	// Below variables are needed to implement additional logic.
	float m_healthBar;										// Original mine health
	Shield* m_shield;										// Mine's shield
};
