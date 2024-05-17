#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum 
{
BT_STATIC,
BT_KINEMATIC,
BT_DYNAMIC
}nc_BodyType;

typedef enum 
{
FM_FORCE,
FM_IMPULSE,
FM_VELOCITY
}nc_ForceMode;

typedef struct nc_Body
{
	nc_BodyType type;
	//acceleration -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 force;
	Vector2 acceleration;

	float mass;
	float damping;
	float imass; // 1 / mass (static = 0)
	float gravityScale; //allow objects to fall faster or slower
	float restitution;

	Color color;

	struct nc_Body* next;
	struct nc_Body* prev;

} nc_Body;

inline void AppliedForce(nc_Body* body, Vector2 force, nc_ForceMode forceMode)
{
	if (body->type != BT_DYNAMIC) return;

	switch (forceMode) 
	{
	case FM_FORCE:
		body->force = Vector2Add(body->force, force);
		break;
	case FM_IMPULSE:
		//sudden change in velocity "momentum"
		body->velocity = Vector2Add(body->velocity,Vector2Scale(force, body->imass));
		break;
	case FM_VELOCITY:
		body->velocity = force;
	}
}

inline void ClearForce(nc_Body* body) 
{
	body->force = Vector2Zero();
}

void Step(nc_Body* body, float timestep);