#include <raylib.h>
#include <iostream>

#include "Other/Types.cpp"
#include "Rendering/Renderer.cpp"
#include "World/World.cpp"

using namespace std;

int main() {
    // Init raylib and window
    Renderer::Init("Game", ivec2(700, 400), FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    // Load tileset
    Tileset::Load("resources/base.tileset");

    Player player;
    World world = World("resources/worlds/world1");
    player.position = world.start.Float();

    Renderer::world = &world;
    Renderer::player = &player;

    // Start game loop
    while(!WindowShouldClose()) {
        Renderer::Render();

        player.Update(Renderer::deltaT);

        if(IsKeyPressed(KEY_F1)) {
            world.edit = !world.edit;
        }

        if(world.edit) {
            if(IsKeyPressed(KEY_LEFT) && world.select != 0) 
                --world.select;
            if(IsKeyPressed(KEY_RIGHT) && world.select != Tileset::tiles.size() -1) 
                ++world.select;

            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                world.Get(player.hoverTile) = world.select;

            // Load / Save world
            if(IsKeyPressed(KEY_F2)) {
                world.Save("./save.world");
                cout << "Saved world to ./save.world" << endl;
            }
            if(IsKeyPressed(KEY_F3)) {
                delete world.content;
                world.Load("./save.world");
                cout << "Loaded world from ./save.world" << endl;
            }

            // New world 
            if(IsKeyPressed(KEY_F4)) {
                string widthString, heightString;
                cout << "- New world -" << endl;
                cout << "\twidth:\t";
                cin >> widthString;
                cout << "\theight:\t";
                cin >> heightString;

                // Create new world
                Vec2<int> worldSize = ivec2(stoi(widthString), stoi(heightString));
                world(worldSize, worldSize / 2);
                player.position = (worldSize / 2).Float();
                player.cameraFollow = true;
            }
        }
    }

    CloseWindow();
}