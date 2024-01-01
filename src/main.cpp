#include <raylib.h>
#include <iostream>

#include "Other/Types.cpp"
#include "Rendering/Renderer.cpp"
#include "World/World.cpp"

using namespace std;

Player player;
World world;

int main() {
    ChangeDirectory("/home/declan/Projects/C++/retrohitman");

    world.player = &player;

    world.Load("resources/worlds/world1");
    world.Unload();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(700, 400, "game");

    Renderer::Init(&world);

    while(!WindowShouldClose()) {
        Renderer::RenderWorld();
    }

    CloseWindow();
}