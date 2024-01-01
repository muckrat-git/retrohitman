#include "Other/Types.cpp"
#include <sstream>
#include <iostream>

class World {
    private:
    Vec2<int> bounds;
    uint8_t * content;

    #define I(x, y) (y * bounds.x) + x

    public:
    Vec2<int> start;
    string name = "NULL";

    void Load(cstr filename) {
        // Load the world file
        string file = LoadFileText(filename);

        // Setup file stream
        istringstream fileStream(file);
        string line;

        // Get world name
        if(!getline(fileStream, line)) {
            cout << "Error loading world '" << filename << "': Missing world name\n";
            return;
        }
        name = line;

        // Get map bounds
        if(!getline(fileStream, line)) {
            cout << "Error loading world '" << filename << "': Missing world bounds\n";
            return;
        }
        int count = 0;
        const char ** tokens = TextSplit(line.c_str(), ':', &count);
        if(count != 2) {
            cout << "Error loading world '" << filename << "': Malformed world bounds (missing ':'?)\n";
            return;
        }
        bounds.x = stoi(tokens[0]);
        bounds.y = stoi(tokens[1]);

        content = new uint8_t[bounds.x * bounds.y];

        int cIndex = 0;
        while(getline(fileStream, line)) {
            tokens = TextSplit(line.c_str(), ' ', &count);

            for(int i = 0; i < count; ++i) {
                content[cIndex] = stoi(tokens[i]);
                if(content[cIndex] == 0) {
                    start.x = cIndex % bounds.x;
                    start.y = cIndex / bounds.y;
                }
                ++cIndex;
            }
        }

        cout << start.Str() << endl;
    }

    void Unload() {
        delete content;
    }
};