#pragma once

#include "Other/Types.cpp"

class Player {
    public:
    // Mouse wheel sensitivity
    const float sensitivity = 20;

    // Player movement speed
    const float speed = 10;

    // Camera data
    Vec2<float> camera = vec2(0);
    bool cameraFollow = true;
    float zoom = 1;
    float targetZoom = 1;

    // Player position data    
    Vec2<float> position = vec2(0);
    Vec2<float> destination;

    // Camera dragging data
    Vec2<float> cameraGrabPos;
    Vec2<int> hoverTile;

    // Other rendering data
    float tileSize;

    void Update(float deltaT) {
        // Move zoom value towards target
        zoom = Lerp(zoom, targetZoom, deltaT*10);

        // Get absolute scroll value
        float scroll = GetMouseWheelMove();
        bool scrollUp = scroll > 0;
        scroll = scrollUp ? scroll : -scroll;

        // Apply sensitivity setting to scroll
        scroll = scroll * (sensitivity / 100.0f);

        // Apply scroll to target zoom
        if(scrollUp)
            targetZoom *= (scroll + 1);
        else
            targetZoom /= (scroll + 1);
        
        // Clamp zoom
        targetZoom = min(max(targetZoom, 0.3f), 10.0f);

        // Calculate movement
        Vec2<float> movement = vec2(-IsKeyDown(KEY_A), -IsKeyDown(KEY_W));
        movement += vec2(IsKeyDown(KEY_D), IsKeyDown(KEY_S));
        movement = movement * deltaT * speed;

        // Check if move
        if(movement.x != 0 || movement.y != 0) {
            cameraFollow = true;

            // Apply movement
            position = (position + movement).Max(0, 0);
        }

        // Check for camera grabbing
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            cameraFollow = false;
            cameraGrabPos = VectorToVec(GetMousePosition());
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            // Get mouse
            const Vec2<float> nextGrab = VectorToVec(GetMousePosition());

            // Move camera
            camera += (cameraGrabPos - nextGrab) / tileSize;
            camera = camera.Max(0, 0);

            // Update camera grab
            cameraGrabPos = nextGrab;
        }

        // Update camera
        if(cameraFollow) {
            camera = camera.Lerp(position, deltaT * 5.0f);
        }

        hoverTile = ((VectorToVec(GetMousePosition()) - vec2(GetRenderWidth(), GetRenderHeight()) / 2) / tileSize + camera - vec2(0.5f)).iRound();
    }
};