#pragma once
#include"Body.h"
#include "raylib.h"

typedef struct nc_Body nc_Body;

extern nc_Body* nc_Bodies;
extern int nc_BodyCount;
extern Vector2 nc_Gravity;

nc_Body* CreateBody(Vector2 position, float mass, nc_BodyType type);
void DestroyBody(nc_Body* body);
void AddBody(nc_Body* body);