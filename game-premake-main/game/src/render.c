#include "render.h" 
#include "raymath.h"

Vector2 ncScreenSize = { 1280, 720 }; // Define the screen size
float ncScreenZoom = 1.0f; // Define the screen zoom level
float ncViewSize = 25.0f; // Define the view size

// Function to convert screen coordinates to world coordinates
Vector2 ConvertScreenToWorld(Vector2 screen)
{
    float ratio = ncScreenSize.x / ncScreenSize.y; // Calculate aspect ratio
    Vector2 extents = (Vector2){ ncViewSize * ratio, ncViewSize }; // Calculate view extents
    extents = Vector2Scale(extents, ncScreenZoom); // Scale the extents based on zoom level

    Vector2 lower = Vector2Negate(extents); // Calculate lower bound of world coordinates
    Vector2 upper = extents; // Calculate upper bound of world coordinates

    float nx = screen.x / ncScreenSize.x; // Normalize x coordinate
    float ny = (ncScreenSize.y - screen.y) / ncScreenSize.y; // Normalize y coordinate

    Vector2 world;
    world.x = ((1 - nx) * lower.x) + (nx * upper.x); // Convert x coordinate from screen to world
    world.y = ((1 - ny) * lower.y) + (ny * upper.y); // Convert y coordinate from screen to world

    return world; // Return the world coordinates
}

// Function to convert world coordinates to screen coordinates
Vector2 ConvertWorldToScreen(Vector2 world)
{
    float ratio = ncScreenSize.x / ncScreenSize.y; // Calculate aspect ratio
    Vector2 extents = (Vector2){ ncViewSize * ratio, ncViewSize }; // Calculate view extents
    extents = Vector2Scale(extents, ncScreenZoom); // Scale the extents based on zoom level

    Vector2 lower = Vector2Negate(extents); // Calculate lower bound of world coordinates
    Vector2 upper = extents; // Calculate upper bound of world coordinates

    float nx = (world.x - lower.x) / (upper.x - lower.x); // Normalize x coordinate
    float ny = (world.y - lower.y) / (upper.y - lower.y); // Normalize y coordinate

    Vector2 screen;
    screen.x = nx * ncScreenSize.x; // Convert x coordinate from world to screen
    screen.y = (1.0f - ny) * ncScreenSize.y; // Convert y coordinate from world to screen

    return screen; // Return the screen coordinates
}

// Function to convert world coordinates to pixel coordinates
float ConvertWorldToPixel(float world)
{
    float ratio = ncScreenSize.x / ncScreenSize.y; // Calculate aspect ratio
    Vector2 extents = (Vector2){ ncViewSize * ratio, ncViewSize }; // Calculate view extents
    extents = Vector2Scale(extents, ncScreenZoom); // Scale the extents based on zoom level

    float nx = world / extents.x; // Normalize world coordinate
    float pixel = nx * ncScreenSize.x; // Convert world coordinate to pixel coordinate

    return pixel; // Return the pixel coordinate
}
