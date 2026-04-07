#pragma once
struct Position
{
    int x;
    int y;

    bool operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }
};

struct PositionHash
{
    std::size_t operator()(const Position& p) const
    {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

bool isAdjacent(Position pos1, Position pos2) {
    int xDif = abs(pos1.x - pos2.x);
    int yDif = abs(pos1.y - pos2.y);
    if (abs(xDif - yDif) == 1) {
        return true;
    }
    else {
        return false;
    }

}