#pragma once

#include "Other/Types.cpp"
#include <cstring> // For memory management

// World class contains world data and loading/saving methods
class World {
    public:
    u16 * content;      // World content data
    Vec2<int> bounds;   // World boundries
    Vec2<int> start;    // Player start point

    // If world in edit mode
    bool edit = false;
    u16 select = 0;

    // Manual constructor
    World(Vec2<int> bounds, Vec2<int> start) {
        this->bounds = bounds;
        this->start = start;

        // Allocate content
        content = new u16[bounds.x*bounds.y];
    } 

    // Reconstructor operator
    void operator()(Vec2<int> bounds, Vec2<int> start) {
        this->bounds = bounds;
        this->start = start;

        // Deallocate content and reallocate
        delete content;
        content = new u16[bounds.x*bounds.y];

        // Fill content
        for(int i = 0; i < bounds.x*bounds.y; ++i) content[i] = 0;

        // Add fences
        for(int x = 1; x < bounds.x-1; ++x) {
            Get(ivec2(x, 0)) = 3;
            Get(ivec2(x, bounds.y - 1)) = 3;
        }
        for(int y = 1; y < bounds.y-1; ++y) {
            Get(ivec2(0, y)) = 4;
            Get(ivec2(bounds.x - 1, y)) = 4;
        }
        Get(ivec2(0, 0)) = 5;
        Get(ivec2(0, bounds.y - 1)) = 7;
        Get(ivec2(bounds.x - 1, 0)) = 6;
        Get(ivec2(bounds.x - 1, bounds.y - 1)) = 8;
    }

    // Load constructor
    World(cstr file) {
        Load(file);
    }

    // Empty constructor
    World() = default;

    // De-constructor
    ~World() {
        delete content;
    }

    // Save the world to a file
    void Save(cstr file) {
        // Allocate and copy new data array
        size_t size = bounds.x*bounds.y + 4;
        u16 * data = new u16[size];
        memcpy(data, content, bounds.x*bounds.y*sizeof(u16));

        // Set last 4 bytes to bounds.x and bounds.y
        data[bounds.x*bounds.y] = bounds.x;
        data[bounds.x*bounds.y + 1] = bounds.y;
        data[bounds.x*bounds.y + 2] = start.x;
        data[bounds.x*bounds.y + 3] = start.y;

        // Save file
        SaveFileData(file, (u8*)data, size*2);

        // Deallocate data
        delete data;
    }

    // Load the world from file
    void Load(cstr file) {
        // Load file
        int size;
        u16 * data = (u16*)LoadFileData(file, &size);
        size /= 2;

        // Get bounds
        bounds.x = data[size-4];
        bounds.y = data[size-3];
        start.x = data[size-2];
        start.y = data[size-1];

        // Allocate and set content
        content = new u16[bounds.x*bounds.y];
        memcpy(content, data, (size-2) * 2);

        // Deallocate data
        free(data);
    }

    // Get world content at position
    u16 & Get(Vec2<int> pos) {
        return content[pos.x * bounds.y + pos.y];
    }

    // Check if position is out of bounds
    bool OutOfBounds(Vec2<int> pos) {
        return (pos.x >= bounds.x || pos.y >= bounds.y || pos.x < 0 || pos.y < 0);
    }

    // World content access operator
    u16 * operator[](int x) const {
        return content + (x*bounds.y);
    }
};