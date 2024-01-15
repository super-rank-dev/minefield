#pragma once

void SetRandomSeed(const unsigned int aSeed);

unsigned int GetRandomUInt32();

float GetRandomFloat32();

float GetRandomFloat32_Range(float aMin, float aMax);

// Value required to initialize temporary removed objects, check the state of deallocated objects.
const unsigned int MAXV = 3722304989;