#include "Map.h"
Map::Map(int _width, int _height) {
	width = _width;
	height = _height;
    mapGen();
    
};
Location& Map::getLocation(int x, int y) {
    return grid[y][x];
}
bool Map::xInBounds(int x) {
    if (x < width - 1 && x > -1) {
        return true;
    };
    return false;
};

bool Map::yInBounds(int y) {
    if (y < height - 1 && y > -1) {
        return true;
    };
    return false;
};
void Map::mapGen() {
    std::random_device r;

    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 1);
    
    grid.resize(height);               // resize outer vector (rows)
    for (int y = 0; y < height; ++y) {
              // resize inner vector (columns)
        for (int x = 0; x < width; ++x) {
            int res = uniform_dist(e1);
            LocationType type = static_cast<LocationType>(res);
            grid[y].push_back(Location("test" + std::to_string(x+y), type, x, y)); // initialize Locations
        }
    }
}