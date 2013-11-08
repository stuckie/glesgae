#ifndef _TILED_JSON_H_
#define _TILED_JSON_H_

#include "../../GAE_Types.h"

struct GAE_File_s;
struct GAE_Map_s;
struct GAE_Array_s;
struct GAE_Texture_s;
struct GAE_Renderer_s;

typedef enum GAE_TILED_ORIENTATION_e {
	GAE_TILED_ORTHAGONAL
,	GAE_TILED_ISOMETRIC
,	GAE_TILED_STAGGERED
} GAE_TILED_ORIENTATION;

typedef struct GAE_Tiled_Layer_s {
	char name[128];
	char type[128];
	struct GAE_Array_s* data;
	unsigned int width;
	unsigned int height;
	unsigned int opacity;
	GAE_BOOL visible;
	unsigned int x;
	unsigned int y;
} GAE_Tiled_Layer_t;

typedef struct GAE_Tiled_Terrain_s {
	char name[128];
	unsigned int tile;
} GAE_Tiled_Terrain_t;

typedef struct GAE_Tiled_Tile_s {
	unsigned int id;
	unsigned int terrain[4U]; /* indexes in the terrain array in the order top-left, top-right, bottom-left, bottom-right */
} GAE_Tiled_Tile_t;

typedef struct GAE_Tiled_Tileset_s {
	unsigned int firstGid;
	unsigned int imageWidth;
	unsigned int imageHeight;
	unsigned int margin;
	char name[128];
	struct GAE_Sprite_s* image;
	struct GAE_Map_s* properties;
	struct GAE_Array_s* terrains;
	struct GAE_Array_s* tiles;
	unsigned int spacing;
	unsigned int tileWidth;
	unsigned int tileHeight;
	unsigned int offset[2]; /* 0 - X, 1 - Y */
} GAE_Tiled_Tileset_t;

typedef struct GAE_Tiled_s {
	unsigned int width;
	unsigned int height;
	unsigned int tileWidth;
	unsigned int tileHeight;
	unsigned int version;

	GAE_TILED_ORIENTATION orientation;
	struct GAE_Map_s* properties;
	struct GAE_Array_s* layers;
	struct GAE_Array_s* tilesets;
} GAE_Tiled_t;

GAE_Tiled_t* GAE_TiledParser_create(struct GAE_File_s* const file);
unsigned int GAE_TiledParser_getTileId(GAE_Tiled_t* tilemap, const unsigned int x, const unsigned int y, const unsigned int layerId);
GAE_Tiled_Tileset_t* getTileset(GAE_Tiled_t* tilemap, const unsigned int tileId);
GAE_Tiled_t* GAE_TiledParser_draw(GAE_Tiled_t* tilemap, struct GAE_Renderer_s* renderer, const unsigned int layerId);
void GAE_TiledParser_delete(GAE_Tiled_t* tiledParser);

#endif
