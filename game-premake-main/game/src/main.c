#include "Body.h"
#include "world.c"
#include "mathf.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <assert.h>
#define MAX_BODIES 10000
int main(void)
{
	InitWindow(1280, 720, "physics engine");
	SetTargetFPS(120);
	//body management
	//Body* bodies = (Body*)malloc(sizeof(Body));
	
	//checks if bodies is null
	//assert(bodies);
	//int bodyCount = 0;

	//game loop
	while (!WindowShouldClose())
	{
		//Update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 m_position = GetMousePosition();
		if (IsMouseButtonDown(0))
		{
			Body* body = CreateBody();
			/*bodies[bodyCount].position = m_position;
			bodies[bodyCount].velocity = CreateVector2(GetRandomFloatValue02(-5, 5), GetRandomFloatValue02(-5, 5));*/
			body->position = m_position;
			body->velocity = CreateVector2(GetRandomFloatValue02(-5, 5), GetRandomFloatValue02(-5, 5));
			//bodyCount++;

			//CreateBody();
		}

		//Render
		BeginDrawing();
		ClearBackground(BLACK);
		//stats
		DrawText(TextFormat("FPS: %.2f (ms %.2fms)", fps, 1000/fps), 10,10,20,LIME);
		DrawText(TextFormat("FRAME: %.4f", dt), 10,30,20,LIME);

		DrawCircle((int)m_position.x, (int)m_position.y, 30, YELLOW);
		/*for (int i = 0; i < bodyCount; i++) 
		{
			bodies[i].position = Vector2Add(bodies[i].position, bodies[i].velocity);
			DrawCircle((int)(bodies)[i].position.x, (int)(bodies)[i].position.y, 15, RED);
		}*/
		Body* body = bodies;
		while (body) 
		{
			body->position = Vector2Add(body->position, body->velocity);
			DrawCircle((int)(body)->position.x, (int)(body)->position.y, 15, RED);

			body = body->next;
		}
		EndDrawing();
	}
	CloseWindow();

	return 0;
}