#pragma once

// - Global Headers -
#include <functional>       // For function type

// - Local Headers -
#include "Other/List.cpp"   // For entity organisation
#include "Other/Types.cpp"  // For type shorthands (cstr)

using namespace std;

// Enemy instance structure
class Enemy {
    public:
    int id, frame;
    float health;
    Vec2<int> position;

    void Update();
    void Render(float tileSize, Vec2<float> camera, Vec2<float> window);
};

// Enemy blueprint/prefab structure
struct EnemyBlueprint {
    cstr name;                  // Enemy name
    Texture2D spritesheet;      // Texture containing all enemy frames
    Vec2<int> spriteBounds;     // Size of individual frame in the sprite sheet
    Vec2<float> renderBounds;   // Size of enemy when rendered (tile is 1x1)

    // - Enemy specific functions -
    function<void(Enemy*)> Update;
};

