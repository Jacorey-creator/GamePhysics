#pragma once
#include "raylib.h"

typedef struct nc_Contact
{
	struct nc_Body* body1;
	struct nc_Body* body2;

	float restitution;
	float depth;
	Vector2 normal;

	struct nc_Contact* next;
} nc_Contact_t;

extern nc_Contact_t* nc_Contacts;
void AddContact(nc_Contact_t* contact, nc_Contact_t** contacts);
void DestroyAllContacts(nc_Contact_t** contacts);
