#include <raylib.h>
#include "World/World.cpp"

#define SCREEN_TILE_W 70

namespace Renderer {
    float scale;    // Camera-Tile scale (pixels per tile)
    Vec2<float> window;
    Rect<int> viewport; // Tile space bounds

    // World pointer
    World * world;

    void UpdateWindow() {
        // Get window bounds
        window.x = GetRenderWidth();
        window.y = GetRenderHeight();

        // Calculate screen bounds
        scale = window.x / SCREEN_TILE_W;
        viewport.size.x = SCREEN_TILE_W;
        viewport.size.y = window.y;
        viewport.position.x = viewport.size.x / 2;
        viewport.position.y = viewport.size.y / 2;
    }
    
    void Init(World * worldPtr) {
        world = worldPtr;
        UpdateWindow();
    }

    void RenderWorld() {
        if(IsWindowResized()) UpdateWindow();

        BeginDrawing();
        {
            ClearBackground(BLACK);
            
            // Calculate viewport offset
            Vec2<int> viewOffset = {
                (int)(modf0(world->player->position.x) * scale), 
                (int)(modf0(world->player->position.y) * scale)
            };

            // Draw tiles in view area
            for(int x = viewport.position.x; x < viewport.size.x; ++x) {
                for(int y = viewport.position.y; y < viewport.size.y; ++y) {
                    // TODO: world.get(x, y)   + resolve tile texture
                }
            }
        }
        EndDrawing();
    }
};