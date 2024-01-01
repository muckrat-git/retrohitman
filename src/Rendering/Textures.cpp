#include <raylib.h>
#include <stdint.h>
#include "Other/Types.cpp"

void DrawTextureFrame(Texture2D texture, Vector2 position, Vector2 size, uint16_t index, uint16_t frames) {
    DrawTexturePro(
        texture, 
        {
            (float)(index * texture.width / frames), 0, 
            (float)(texture.width / frames), (float)texture.height
        },
        {
            position.x, position.y,
            size.x, size.y
        },
        {0, 0},
        0,
        WHITE
    );
}

void DrawTextureFrame(Texture2D texture, Vector2 position, Vector2 size, Vec2<int> frame, Vec2<int> frameSize) {
    DrawTexturePro(
        texture, 
        {
            (float)(frame.x * texture.width / frameSize.x), (float)(frame.y * texture.height / frameSize.y), 
            (float)(texture.width / frameSize.x), (float)(texture.height / frameSize.y)
        },
        {
            position.x, position.y,
            size.x, size.y
        },
        {0, 0},
        0,
        WHITE
    );
}