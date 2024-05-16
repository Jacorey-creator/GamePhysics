#include "Spring.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

nc_Spring_t* nc_Springs = NULL;

nc_Spring_t* CreateSpring(struct nc_Body* body1, struct nc_Body* body2, float restLength, float k)
{
	nc_Spring_t* spring = (nc_Spring_t*)malloc(sizeof(nc_Spring_t));
	assert(spring);

	memset(spring, 0, sizeof(nc_Spring_t));
	spring->body1 = body1;
	spring->body2 = body2;
	spring->restLength = restLength;
	spring->k = k;

	return spring;
}

void AddSpring(nc_Spring_t* spring) 
{
	assert(spring);

	spring->prev = NULL;
	spring->next = nc_Springs;

	if (nc_Springs) nc_Springs->prev = spring;

	nc_Springs = spring;
}
void DestroySpring(nc_Spring_t* spring)
{
	assert(spring);

	if (spring->prev) spring->prev->next = spring->next;
	if (spring->next) spring->next->prev = spring->prev;

	if (spring == nc_Springs) nc_Springs = spring->next;
	free(spring);
}
void ApplySpringForce(nc_Spring_t* springs)
{
	for (nc_Spring_t* spring = springs; spring; spring = spring->next) 
	{
		Vector2 direction = Vector2Subtract(spring->body1->position, spring->body2->position);
		if (direction.x == 0 && direction.y == 0) continue;

		float length = Vector2Length(direction);
		float x = length - spring->restLength;
		float force = spring->k * x;

		Vector2 ndirection = Vector2Normalize(direction);

		AppliedForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		AppliedForce(spring->body2, Vector2Scale(Vector2Negate(ndirection), force), FM_FORCE);
	}

}

void DestroyAllSprings()
{

}