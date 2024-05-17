#include "Body.h"
#include "Spring.h"
#include "integrator.h"
#include "render.h"
#include "editor.h"
#include "Force.h"
#include "world.c"
#include "mathf.h"
#include "raylib.h"
#include "raymath.h"
#include "contact.h"
#include "collision.h"
#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 10000
int main(void)
{
	nc_Body* selectedBody = NULL;
	nc_Body* connectedBody = NULL;

	InitWindow(1280, 720, "physics engine");
	InitEditor();
	SetTargetFPS(120);
	//initialize world
	//nc_Gravity = (Vector2){ 0 , -1 };

	//game loop
	while (!WindowShouldClose())
	{
		//Update
		nc_Gravity = (Vector2){ 0 , -nc_EditorData.GravitationalValue };

		float dt = GetFrameTime();
		float fps = (float)GetFPS();
		Vector2 m_position = GetMousePosition();
		ncScreenZoom += GetMouseWheelMove() * 0.2f;
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10);
		UpdateEditor(m_position);

		selectedBody = GetBodyIntersect(nc_Bodies, m_position);
		if (selectedBody)
		{
			Vector2 screen = ConvertWorldToScreen(selectedBody->position);
			DrawCircleLines((int)screen.x, (int)screen.y, ConvertWorldToPixel(selectedBody->mass) + 5, selectedBody->color);
		}
		if (!ncEditorIntersect)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_SHIFT))
			{
				nc_Body* body = CreateBody(ConvertScreenToWorld(m_position), nc_EditorData.MassValue, nc_EditorData.BodyType);

				body->damping = nc_EditorData.DampenValue;
				body->gravityScale = nc_EditorData.BodyGravityValue;
				body->color = ColorFromHSV(GetRandomFloatValue02(0, 360), 1, 1);
				body->restitution = 0.8f;
				AddBody(body);
			}
			//Connect Spring
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody) connectedBody = selectedBody;
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && connectedBody) DrawLineBodyToPosition(connectedBody, m_position);
			if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectedBody)
			{
				if (selectedBody && selectedBody != connectedBody)
				{
					nc_Spring_t* spring = CreateSpring(connectedBody, selectedBody, Vector2Distance(connectedBody->position, selectedBody->position),nc_EditorData.kValue);
					AddSpring(spring);
				}
			}
		}
		//apply force

		ApplyGravitation(nc_Bodies, nc_EditorData.GravitationalValue);
		ApplySpringForce(nc_Springs);

		//update bodies
		for (nc_Body* body = nc_Bodies; body != NULL; body = body->next)
		{
			Step(body, dt);
		}

		//Collision
		nc_Contact_t* contacts = NULL;
		CreateContacts(nc_Bodies, &contacts);
		SeparateContacts(contacts);
		//ResolveContacts(contacts);

		//Render
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (ms %.2fms)", fps, 1000 / fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, LIME);

		// draw bodies
		for (nc_Body* body = nc_Bodies; body; body = body->next)
		{
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass * 0.5f), body->color);
		}

		// draw contacts
		for (nc_Contact_t* contact = contacts; contact; contact = contact->next)
		{
			Vector2 screen = ConvertWorldToScreen(contact->body1->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(contact->body1->mass * 0.5f), RED);
		}

		//draw springs
		for (nc_Spring_t* spring = nc_Springs; spring; spring = spring->next)
		{
			Vector2 screen1 = ConvertWorldToScreen(spring->body1->position);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->position);
			DrawLine((int)screen1.x, (int)screen1.y, (int)screen2.x, (int)screen2.y, YELLOW);
		}
		DrawEditor(m_position);
		
		EndDrawing();
	}
	CloseWindow();
	free(nc_Bodies);

	return 0;
}