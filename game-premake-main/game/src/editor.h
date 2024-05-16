#pragma once
#include "Body.h"
#include "raylib.h"

typedef struct nc_EditorData
{
	float MassValue;
	bool EditorBoxActive;
	float GravitationalValue;
	float DampenValue;
	float BodyGravityValue;
	nc_BodyType BodyType;
	float stringRestLength;
	float kValue;
}nc_EditorData_t;


extern nc_EditorData_t nc_EditorData;
extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor();

struct nc_Body* GetBodyIntersect(struct nc_Body* bodies, Vector2 position);
void DrawLineBodyToPosition(struct nc_Body* body, Vector2 position);