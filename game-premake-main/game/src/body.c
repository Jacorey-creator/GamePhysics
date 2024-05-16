#include "Body.h"
#include "World.h"
#include "integrator.h"



void Step(nc_Body* body, float timestep)
{
	body->force = Vector2Add(body->force, Vector2Scale(Vector2Scale(nc_Gravity, body->gravityScale), body->mass));
	body->acceleration = Vector2Scale(body->force, body->imass);

	SemiImplicitEuler(body, timestep);
	//Apply Dampening
	float dampening = 1 / (1 + (body->damping * timestep));
	body->velocity = Vector2Scale(body->velocity, dampening);
	ClearForce(body);
}