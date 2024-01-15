#pragma once

#include "Mine.h"

class Mine;

class Shield
{
public:
	Shield(Mine* mine);
	~Shield();

	void TakeDamage(float aDamage);
	void Regenerate();

private:
	Mine* m_mine;
	float m_health;
	float m_regeneration;
};

