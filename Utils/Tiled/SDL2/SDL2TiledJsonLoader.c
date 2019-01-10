#include "../TiledJsonLoader.h"
#include "../../../Utils/Array.h"
#include "../../../Graphics/Renderer/Renderer.h"
#include "../../../Graphics/Texture.h"
#include "SDL2/SDL.h"

GAE_Tiled_t* GAE_TiledParser_draw(GAE_Tiled_t* tilemap, GAE_Renderer_t* renderer, const unsigned int layerId) {
	unsigned int y = 0U;
	unsigned int x = 0U;
	
	GAE_Tiled_Layer_t* layer = (GAE_Tiled_Layer_t*)GAE_Array_get(tilemap->layers, layerId);
	GAE_Tiled_Tileset_t* tileset = getTileset(tilemap, *(unsigned int*)GAE_Array_begin(layer->data));
	GAE_SDL2_Texture_t* texture = (GAE_SDL2_Texture_t*)tileset->image->platform;
	
	const unsigned int margin = tileset->margin;
	const unsigned int srcWidth = tileset->tileWidth + margin;
	const unsigned int srcHeight = tileset->tileHeight + margin;
	const unsigned int dstWidth = tilemap->tileWidth + margin;
	const unsigned int dstHeight = tilemap->tileHeight + margin;
	const unsigned int tilemapWidthInTiles = (tileset->imageWidth / srcWidth);
	const unsigned int offsetX = layer->x;
	const unsigned int offsetY = layer->y;
	
	GAE_UNUSED(renderer);

	#define ROWCOL(x,y,width) (x + y * width)
	
	for (y = 0U; y < layer->height; ++y) {
		for (x = 0U; x < layer->width; ++x) {
			const unsigned int tileId = *(unsigned int*)GAE_Array_get(layer->data, ROWCOL(x, y, layer->width)) - 1U;
			SDL_Rect src;
			SDL_Rect dst;
			
			src.x = (tileId % tilemapWidthInTiles) * srcWidth;
			src.y = (tileId / tilemapWidthInTiles) * srcWidth;
			src.w = srcWidth;
			src.h = srcHeight;

			dst.x = (x * dstWidth) + offsetX;
			dst.y = (y * dstHeight) + offsetY;
			dst.w = dstWidth;
			dst.h = dstHeight;

			SDL_RenderCopy(texture->renderer, texture->texture, &src, &dst);
		}
	}
	
	#undef ROWCOL
	
	return tilemap;
}
