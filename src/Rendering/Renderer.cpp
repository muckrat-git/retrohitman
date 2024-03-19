#pragma once

// Include raylib headers
#include <raylib.h>
#include <rlgl.h>

// Include types
#include "Other/Types.cpp"
#include "World/World.cpp"
#include "Player/Player.cpp"
#include "World/Tileset.cpp"

// Optimised version of 'DrawTexturePro' from raylib/src/rtextures.c
void DrawTextureFast(Texture2D texture, Rectangle dest, Color tint, bool flipY = false) {
    // Dimension constants
    const float width = (float)texture.width;
    const float height = (float)texture.height;
    const float x = dest.x;
    const float y = dest.y;

    // Get texture vertex coords
    Vector2 topLeft = {x, y};
    Vector2 topRight = {x + dest.width, y};
    Vector2 bottomLeft = {x, y + dest.height};
    Vector2 bottomRight = {x + dest.width, y + dest.height};

    // Set texture and being drawing
    rlSetTexture(texture.id);
    rlBegin(RL_QUADS);

    // Set image tint
    rlColor4ub(tint.r, tint.g, tint.b, tint.a);
    rlNormal3f(0.0f, 0.0f, 1.0f);   // Normal vector pointing towards viewer

    // Top-left corner for texture and quad
    rlTexCoord2f(0, flipY ? 1 : 0);
    rlVertex2f(topLeft.x, topLeft.y);

    // Bottom-left corner for texture and quad
    rlTexCoord2f(0, flipY ? 0 : 1);
    rlVertex2f(bottomLeft.x, bottomLeft.y);

    // Bottom-right corner for texture and quad
    rlTexCoord2f(1, flipY ? 0 : 1);
    rlVertex2f(bottomRight.x, bottomRight.y);

    // Top-right corner for texture and quad
    rlTexCoord2f(1, flipY ? 1 : 0);
    rlVertex2f(topRight.x, topRight.y);

    // End drawing
    rlEnd();
    rlSetTexture(0);
}

// Renderer contains all basic rendering methods
namespace Renderer {
    // Window size
    Vec2<int> window;

    // World pointer
    World * world;

    // Player pointer
    Player * player;

    // Time between frames
    float deltaT = 0;

    void Init(cstr title, Vec2<int> size, unsigned int flags) {
        // Set flags and init window
        SetConfigFlags(flags);
        InitWindow(size.x, size.y, title);

        // Set initial window size
        window = size;
    }
    
    void Render() {
        // Get window size
        window.x = GetRenderWidth();
        window.y = GetRenderHeight();

        // Rendering metrics
        const float xScale = 20 / player->zoom;       // Tiles per width of screen
        const float tileSize = window.x / xScale;     // Size of tile in pixels
        const float yScale = window.y / tileSize;     // Tiles per height of screen

        // Set player info
        player->tileSize = tileSize;

        // Selected mipmap level
        u8 mipmap = 0;
        if(tileSize < Tileset::size[0] * 2) {
            mipmap = (int)log2(Tileset::size[0] / tileSize);
            if(mipmap >= MIPMAP_COUNT) mipmap = MIPMAP_COUNT - 1;
        }

        // Start render
        BeginDrawing();
        {
            // Predefine texture, ratio, and world pos
            Texture2D tex;
            float ratio;
            Vec2<int> worldPos;

            // Calculate offset
            Vec2<float> offset = vec2(modf0(player->camera.x), modf0(player->camera.y));
            
            // Draw world from bottom to top
            for(int y = -yScale / 2 - 1; y < yScale / 2 + 6; ++y) {
                for(int x = -xScale / 2 - 2; x < xScale / 2 + 1; ++x) {
                    // Calculate world-space position
                    worldPos = player->camera.Int() + ivec2(x, y);

                    // Get tile
                    if(world->OutOfBounds(worldPos)) {
                        tex = Tileset::tiles[0].mipmaps[mipmap];
                    }
                    else {
                        const u16 tile = world->Get(worldPos);

                        // Get texture
                        tex = Tileset::tiles[tile].mipmaps[mipmap];
                    }

                    // Calculate display variables
                    ratio = (float)tex.height / Tileset::size[mipmap];
                    const Vec2<float> texSize = vec2(((float)tex.width * tileSize / Tileset::size[mipmap]), tileSize * ratio);

                    // Set texture tint
                    Color tint = WHITE;

                    // Check if tile hover
                    if(player->hoverTile == worldPos)
                        tint = world->OutOfBounds(player->hoverTile) ? (Color){255, 100, 100, 255} : LIGHTGRAY;

                    DrawTextureFast(
                        tex, 
                        {
                            (window.x / 2) + ((x - offset.x) * tileSize) - ((texSize.x - tileSize) / 2), 
                            (window.y / 2) + ((y - offset.y) * tileSize) - texSize.y + tileSize - 1,
                            texSize.x, texSize.y + 2
                        }, 
                        tint
                    );
                }
            }

            // Temp player indicator
            Vec2<float> relativePlayer = player->position - player->camera;
            DrawCircle(window.x / 2 + relativePlayer.x * tileSize, window.y / 2 + relativePlayer.y * tileSize, tileSize / 2, BLACK);
            
            // Draw edit mode menus
            if(world->edit) {
                DrawRectangle(5, 5, 70, 70, BLACK);
                DrawTextureFast(Tileset::tiles[world->select].mipmaps[0], {8, 8, 64, 64}, WHITE);
            }
        }
        // End render
        EndDrawing();

        // Set deltaT
        deltaT = GetFrameTime();
    }
};