
#ifndef LCONST_H
#define LCONST_H

//Screen dimension constants
constexpr int kScreenWidth{ 1536 };
constexpr int kScreenHeight{ 512 };
constexpr int kScreenFps{ 60 };
// The dimensions of the TileMap
static constexpr float kTileMapWidth = 32.0f;
static constexpr float kTileMapHeight = 32.0f;
enum LocationType {

	FOREST = 0,
	VILLAGE = 1
};
#endif
