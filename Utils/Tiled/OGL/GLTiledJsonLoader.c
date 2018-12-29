#include "../TiledJsonLoader.h"
#include "../../../Utils/Array.h"
#include "../../../Graphics/Renderer/Renderer.h"
#include "../../../Graphics/Sprite.h"
#include "../../../Maths/Matrix.h"
#include "../../../Maths/Vector.h"

GAE_Tiled_t* GAE_TiledParser_draw(GAE_Tiled_t* tilemap, GAE_Renderer_t* renderer, const unsigned int layerId) {
	unsigned int y = 0U;
	unsigned int x = 0U;
	
	GAE_Tiled_Layer_t* layer = (GAE_Tiled_Layer_t*)GAE_Array_get(tilemap->layers, layerId);
	GAE_Tiled_Tileset_t* tileset = getTileset(tilemap, *(unsigned int*)GAE_Array_begin(layer->data));
	
	const unsigned int margin = tileset->margin;
	/*const unsigned int srcWidth = tileset->tileWidth + margin;*/
	/*const unsigned int srcHeight = tileset->tileHeight + margin;*/
	const unsigned int dstWidth = tilemap->tileWidth + margin;
	const unsigned int dstHeight = tilemap->tileHeight + margin;
	/*const unsigned int tilemapWidthInTiles = (tileset->imageWidth / srcWidth);*/
	const unsigned int offsetX = layer->x;
	const unsigned int offsetY = layer->y;
	
	#define ROWCOL(x,y,width) (x + y * width)
	
	for (y = 0U; y < layer->height; ++y) {
		for (x = 0U; x < layer->width; ++x) {
			/*const unsigned int tileId = *(unsigned int*)GAE_Array_get(layer->data, ROWCOL(x, y, layer->width)) - 1U;*/
            GAE_Vector3_t position = {offsetX + (x * dstWidth), offsetY + (y * dstHeight), 0.0};
            position[0] = 0;
            position[1] = 0;
            GAE_Matrix4_setToIdentity(&tileset->image->transform);
            GAE_Matrix4_setPosition(&tileset->image->transform, &position);
			/*
			src.x = (tileId % tilemapWidthInTiles) * srcWidth;
			src.y = (tileId / tilemapWidthInTiles) * srcWidth;
			src.w = srcWidth;
			src.h = srcHeight;

			dst.x = (x * dstWidth) + offsetX;
			dst.y = (y * dstHeight) + offsetY;
			dst.w = dstWidth;
			dst.h = dstHeight;
            */
			
			GAE_Renderer_drawSprite(renderer, tileset->image);
		}
	}
	
	#undef ROWCOL
	
	return tilemap;
}
