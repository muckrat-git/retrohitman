#include <raylib.h>

namespace Renderer {
    void BeginRender() {
        BeginDrawing();
        ClearBackground(WHITE);
    }

    void EndRender() {
        EndDrawing();
    }
};