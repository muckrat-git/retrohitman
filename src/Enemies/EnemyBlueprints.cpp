#pragma once

#include "Enemies/Enemy.cpp"

#define ENEMY_TYPES 1
const EnemyBlueprint enemyBlueprints[ENEMY_TYPES] = {

};

// Resolve enemy function prototypes
void Enemy::Update() {
    enemyBlueprints[this->id].Update(this);
}
void Enemy::Render(float tileSize, Vec2<float> camera, Vec2<float> window) {
    const EnemyBlueprint blueprint = enemyBlueprints[this->id];
    // Source rect
    const Rectangle source = {
        blueprint.spriteBounds.x * this->frame,
        0,
        blueprint.spriteBounds.x,
        blueprint.spriteBounds.y
    };
    const Vec2<float> relative = (this->position.Float() - camera) * tileSize;  
    // Destination rect
    const Rectangle dest = {
        window.x / 2 + relative.x, window.y / 2 + relative.y,
        blueprint.renderBounds.x * tileSize, blueprint.renderBounds.y * tileSize
    };

    DrawTexturePro(blueprint.spritesheet, source, dest, {dest.width / 2, dest.height / 2}, 0, WHITE);
}