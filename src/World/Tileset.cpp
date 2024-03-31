#pragma once

#include "Other/Types.cpp"

#include <fstream>
#include <vector>

#define MIPMAP_COUNT 3

// Tile flags
#define TILE_FLAG_FLOOR         0b00000001  // Allow player to walk through
#define TILE_FLAG_TRANSPARENT   0b00000010  // Allow player to see through

class Tile {
    public:
    Vec2<int> size;
    u8 flags = 0b00000000;              // Binary flags
    Texture2D mipmaps[MIPMAP_COUNT];    // Levels of resolution

    Tile(cstr filename, u8 flags) {
        // Load image
        Image image = LoadImage(filename);
        size.x = image.width;
        size.y = image.height;
        
        // Generate mipmaps
        for(int i = 0; i < MIPMAP_COUNT; ++i) {
            mipmaps[i] = LoadTextureFromImage(image);
            ImageResize(&image, image.width / 2, image.height / 2);
        }

        // Unload Image
        UnloadImage(image);
        
        // Set flags
        this->flags = flags;
    }

    // Unload Tile data
    void Unload() {
        for(int i = 0; i < MIPMAP_COUNT; ++i)
            UnloadTexture(mipmaps[i]);
    }
};

namespace Tileset {
    // Tile base sizes
    float size[MIPMAP_COUNT];

    // String representations for different flags
    string flagMap[] = {
        "AIR",
        "TRA"
    };

    vector<Tile> tiles;

    // Get binary form of string tile flag
    u8 GetTileFlag(cstr flag) {
        for(int i = 0; i < sizeof(flagMap) / 4; ++i) {
            if(flag == flagMap[i]) return (1 << i);
        }
        return 0;
    }

    // Load all tiles
    void Load(cstr file) {
        // Calculate tile sizes
        size[0] = 32;
        for(int i = 1; i < MIPMAP_COUNT; ++i) {
            size[i] = size[i-1] / 2;
        }

        // Load file text
        ifstream data(file);

        // Read file lines
        string line;
        while(getline(data, line)) {
            // Split line by whitespace
            int count;
            cstr * tokens = TextSplit(line.c_str(), ' ', &count);

            // Avoid invalid lines or comments
            if(!count) continue;
            if(tokens[0][0] == '#') continue;

            // Seperate name
            cstr name = tokens[0];

            // Construct flags
            u8 flags;
            for(int i = 1; i < count; ++i) {
                flags |= GetTileFlag(tokens[i]);
            }

            // Construct and append Tile
            Tile tile = Tile(name, flags);
            tiles.push_back(tile);
        }
    }
    
    // Unload tileset
    void Unload() {
        for(int i = 0; i < tiles.size(); ++i) tiles[i].Unload();
    }
};