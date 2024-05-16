#include "collision.h"
#include "Body.h"
#include "raymath.h"
#include "mathf.h"
#include "contact.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

bool Intersects(nc_Body* body1, nc_Body* body2)
{
//if distance < radius
	float distance = Vector2Distance(body1->position, body2->position);
	float radius = body1->mass + body2->mass;

	return (distance <= radius);
}


void CreateContacts(nc_Body* bodies, nc_Contact_t** contacts)
{
	for (nc_Body* body1 = bodies; body1; body1 = body1->next)
	{
		for (nc_Body* body2 = body1->next; body2; body2 = body2->next)
		{
			if (body1 == body2) continue;
			if (body1->type != BT_DYNAMIC && body2->type != BT_DYNAMIC) continue;
			if (Intersects(body1, body2)) 
			{
				nc_Contact_t* contact = GenerateContact(body1, body2);
				AddContact(contact, contacts);
			}
		}
	}
}

nc_Contact_t* GenerateContact(nc_Body* body1, nc_Body* body2)
{
	nc_Contact_t* contact = (nc_Contact_t*)malloc(sizeof(nc_Contact_t));
	assert(contact);
	memset(contact, 0, sizeof(nc_Contact_t));

	contact->body1 = body1;
	contact->body2 = body2;

	Vector2 direction = Vector2Subtract(body1->position, body2->position);
	float distance = Vector2Length(direction);
	if (distance == 0) direction = (Vector2){ GetRandomFloatValue02(-0.5, 0.05f), GetRandomFloatValue02(-0.5, 0.05f) };

	float radius = (body1->mass + body2->mass);
	contact->depth = radius - distance;
	contact->normal = Vector2Normalize(direction);
	contact->restitution = (body1->restitution + body2->restitution) * 0.5f;

	return contact;
}

void SeparateContacts(nc_Contact_t* contacts)
{

}

void ResolveContacts(nc_Contact_t* contacts)
{

}
