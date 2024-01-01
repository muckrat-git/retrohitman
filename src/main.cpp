#include <raylib.h>
#include <iostream>

#include "Other/Types.cpp"
#include "Rendering/Renderer.cpp"
#include "World/World.cpp"

using namespace std;

World world;

int main() {
    ChangeDirectory("/home/declan/Projects/C++/retrohitman");

    world.Load("resources/worlds/world1");
    world.Unload();

    return 0;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(700, 400, "game");

    while(!WindowShouldClose()) {
        Renderer::BeginRender();
        {

        }
        Renderer::EndRender();
    }

    CloseWindow();
}