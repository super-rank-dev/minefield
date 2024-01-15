#pragma once

#include "Random.h"

class Object
{
public:
	Object() {
		// Initialize member variables.
		m_objectId = MAXV;
		m_team = -1;
		m_bitFlags = 0;
	}

	// ~Object() {} - Incorrect
	// As recursive explosion is caused in mine's destructor, it should be ignored.
	virtual ~Object() {} // Correct

	unsigned int GetObjectId();
	void SetObjectId(unsigned int aObjectId);

	bool GetActive();
	void SetActive(bool aActive);

	bool GetInvulnerable();
	void SetInvulnerable(bool aInvulnerable);

	virtual float* GetPosition() { return 0; }
	virtual void SetPosition(float*) {}

	virtual void SetBitFlags(int) {};			// Virtual function to set bit flags, ignored.
	virtual int GetBitFlags() { return 0; };	// Virtual function to get bit flags, ignored.

	virtual int GetTeam() { return 0; };		// Virtual function to get team, ignored.
	virtual void SetTeam(int aTeam) {};			// Virtual function to set team, ignored.

protected:
	unsigned int m_objectId;
	int m_team;

	enum ObjectBitFlags
	{
		// OBF_ACTIVE = 0x0000, - Incorrect.
		// As OBF_ACTIVE is 0x0000, it causes logic error.
		// GetActive function returns m_bitFlags & OBF_ACTIVE.
		// But for now, it's value is 0x00.
		// So it always returns false even though an object is active.
		OBF_ACTIVE = 0x0001,
		OBF_INVULNERABLE = 0x0002,
	};

	int m_bitFlags;
};
