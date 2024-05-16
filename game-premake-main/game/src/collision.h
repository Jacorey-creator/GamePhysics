#pragma once
#include "raylib.h"

typedef struct nc_Contact nc_Contact_t;
typedef struct nc_Body nc_Body;

void CreateContacts(nc_Body* bodies, nc_Contact_t** contacts);
nc_Contact_t* GenerateContact(nc_Body* body1, nc_Body* body2);

void SeparateContacts(nc_Contact_t* contacts);
void ResolveContacts(nc_Contact_t* contacts);