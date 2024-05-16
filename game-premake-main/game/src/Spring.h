#pragma once
#include "Body.h"

typedef struct nc_Spring
{
	struct nc_Body* body1;
	struct nc_Body* body2;
	float restLength;
	float k; // stiffness

	struct nc_Spring* prev;
	struct nc_Spring* next;
}nc_Spring_t;

extern nc_Spring_t* nc_Springs;

nc_Spring_t* CreateSpring(struct nc_Body* body1, struct nc_Body* body2, float restLength, float k);
void DestroySpring(nc_Spring_t* spring);
void DestroyAllSprings();
void AddSpring(nc_Spring_t* spring);
void ApplySpringForce(nc_Spring_t* springs);

