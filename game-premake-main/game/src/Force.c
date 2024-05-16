#include "Force.h"
#include "Body.h"

void ApplyGravitation(nc_Body* bodies, float strength)
{
	for (nc_Body* body1 = bodies; body1; body1 = body1->next)
	{
		for (nc_Body* body2 = bodies; body2; body2 = body2->next)
		{
			if (body1 == body2)  continue;

			Vector2 direction =  Vector2Subtract(body1->position, body2->position);
			float distance = Vector2Length(direction);

			distance = fmaxf(1,distance);
			float force = body1->mass * body2->mass / (distance * distance) * strength;

			direction = Vector2Scale(Vector2Normalize(direction), force);

			AppliedForce(body1, Vector2Negate(direction), FM_FORCE);
			AppliedForce(body2, direction, FM_FORCE);
		}
	}

	
}