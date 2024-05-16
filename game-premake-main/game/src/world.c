#include "world.h"
#include "Body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

nc_Body* nc_Bodies = NULL;
int nc_BodyCount = 0;
Vector2 nc_Gravity;

nc_Body* CreateBody(Vector2 position, float mass, nc_BodyType type)
{
	nc_Body* body = malloc(sizeof(nc_Body));
	assert(body);

	memset(body, 0, sizeof(nc_Body));
	body->position = position;
	body->mass = mass;
	body->imass = (type == BT_DYNAMIC) ? 1 / mass : 0;
	body->type = type;
	
	return body;
}
void DestroyBody(nc_Body* body)
{
	assert(body);

	if (body->prev) body->prev->next = body->next;
	if (body->next) body->next->prev = body->prev;

	nc_BodyCount--;

	free(body);
}

void AddBody(nc_Body* body)
{
	assert(body);

	//add element to linked list
	body->prev = NULL;
	body->next = nc_Bodies;

	nc_BodyCount++;
	if (nc_Bodies) nc_Bodies->prev = body;
	nc_Bodies = body;
}