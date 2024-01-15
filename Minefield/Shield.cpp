#include "stdafx.h"
#include "Shield.h"

Shield::Shield(Mine* mine) {
	m_mine = mine;
	m_health = 100.0f;
	m_regeneration = 50.0f;
}

Shield::~Shield() {

}

void Shield::TakeDamage(float aDamage) {
	m_health -= aDamage;
	if (m_health <= 0.0f) {
		m_mine->DestroyShield();
	}
}

void Shield::Regenerate() {
	m_mine->SetHealth(m_mine->GetHealth() + m_regeneration);
	if (m_mine->GetHealth() > m_mine->GetHealthBar()) {
		m_mine->SetHealth(m_mine->GetHealthBar());
	}
}