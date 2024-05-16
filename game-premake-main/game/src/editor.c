#include "editor.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;
nc_EditorData_t nc_EditorData;

Vector2 anchor01 = { 752, 120 };
Texture2D cursorTexture; 
bool WindowBox000Active = true;

bool DropDownEditMode = false;
int DropDownActive = 0;


void InitEditor()
{
	GuiLoadStyle("raygui/styles/terminal/style_terminal.rgs");
	Image image = LoadImage("resources/reticle 1.png");
	cursorTexture = LoadTextureFromImage(image);
	UnloadImage(image);
	nc_EditorData.stringRestLength = 0.5f;
	nc_EditorData.EditorBoxActive = true;
	nc_EditorData.GravitationalValue = 2;
	nc_EditorData.BodyType = BT_STATIC;
	nc_EditorData.MassValue = 2;
	nc_EditorData.kValue = 10.0f;
	HideCursor();
}

void UpdateEditor(Vector2 position)
{
	//toggle
	if (IsKeyPressed(KEY_TAB)) nc_EditorData.EditorBoxActive = !nc_EditorData.EditorBoxActive;

	ncEditorIntersect = nc_EditorData.EditorBoxActive && CheckCollisionPointRec(position, editorRect);
}

void DrawEditor(Vector2 position)
{
	if (nc_EditorData.EditorBoxActive)
	{
		nc_EditorData.EditorBoxActive = !GuiWindowBox((Rectangle) { 752, 160, 296, 416 }, "Editor Box");

		GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 72, 120, 16 }, "MassMin", NULL, & nc_EditorData.MassValue, 0, 5);
		GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 92, 120, 16 }, "StringLength", NULL, & nc_EditorData.stringRestLength, 0, 5);
		GuiSliderBar((Rectangle) { anchor01.x + 100, anchor01.y + 112, 120, 16 }, "String Stiffness", NULL, & nc_EditorData.kValue, 0, 5);
		GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 136, 120, 16 }, "Gravitational", NULL, & nc_EditorData.GravitationalValue, 0, 5);
		
		GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 150, 120, 16 }, "Damping", NULL, & nc_EditorData.DampenValue, 0, 5);
		GuiSliderBar((Rectangle) { anchor01.x + 115, anchor01.y + 167, 120, 16 }, "Body Gravity Scale", NULL, & nc_EditorData.BodyGravityValue, 0, 5);
		if (DropDownEditMode) GuiLock();

		if (GuiDropdownBox((Rectangle) { anchor01.x + 80, anchor01.y + 183, 120, 40 }, "Dynamic;Static;Kinematic", & DropDownActive, DropDownEditMode)) DropDownEditMode = !DropDownEditMode;
		switch (DropDownActive)
		{
		case 0:
			nc_EditorData.BodyType = BT_DYNAMIC;
			break;
		case 1:
			nc_EditorData.BodyType = BT_STATIC;
			break;
		case 2:
			nc_EditorData.BodyType = BT_KINEMATIC;
			break;
		}
		
		

		GuiUnlock();
	}
	DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, PINK);
}

nc_Body* GetBodyIntersect(nc_Body* bodies, Vector2 position)
{
	for (nc_Body* body = bodies; body; body = body->next)
	{
		Vector2 screen = ConvertWorldToScreen(body->position);
		if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass * 0.5f)))
		{
			return body;
		}
	}

	return NULL;
}

void DrawLineBodyToPosition(nc_Body* body, Vector2 position)
{
	Vector2 screen = ConvertWorldToScreen(body->position);
	DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}
