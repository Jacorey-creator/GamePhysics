#include "world.h"
#include <stdlib.h>
#include <assert.h>

Body* bodies = NULL;
int bodyCount = 0;

Body* CreateBody()
{
	Body* body = malloc(sizeof(Body));
	assert(body);
	body->prev = NULL;
	body->next = bodies;

	bodyCount++;
	if (bodies) bodies->prev = body;
	bodies = body;
	return body;
}
void DestroyBody(Body* body)
{
	assert(body);

	if (body->prev) body->prev->next = body->next;
	if (body->next) body->next->prev = body->prev;

	bodyCount--;

	free(body);
}