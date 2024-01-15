#include "stdafx.h"

#include "Object.h"


bool Object::GetActive()
{
	return m_bitFlags & OBF_ACTIVE;
}

void Object::SetActive(bool aActive)
{
	if (aActive)
	{
		// m_bitFlags &= OBF_ACTIVE; - Incorrect
		// When you set &=, object is permanently inactive as long as it's initial state is inactive.
		m_bitFlags |= OBF_ACTIVE; // Correct
	}
	else
	{
		m_bitFlags &= ~OBF_ACTIVE;
	}
}

bool Object::GetInvulnerable()
{
	// return (m_bitFlags & OBF_INVULNERABLE) ? true : false; - Need some changes
	// No issues, but "? true : false" can be removed to make the code clearer and more efficient.
	return m_bitFlags & OBF_INVULNERABLE;
}

// Set an object invulnerable/vulnerable.
void Object::SetInvulnerable(bool aInvulnerable)
{
	if (aInvulnerable)
	{
		// Set an object invulnerable.
		m_bitFlags |= OBF_INVULNERABLE;
	}
	else
	{
		// Set an object vulnerable.
		m_bitFlags &= ~OBF_INVULNERABLE;
	}
}

unsigned int Object::GetObjectId()
{
	return m_objectId;
}

void Object::SetObjectId(unsigned int aObjectId)
{
	m_objectId = aObjectId;
}