#include "TiledJsonLoader.h"

#include "../../File/File.h"
#include "../../External/jsmn/jsmn.h"
#include "../../Graphics/Sprite.h"
#include "../Map.h"
#include "../Array.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define JSON_TOKENS 256
char* KEYS[] = { "height", "layers", "data", "name", "opacity", "type", "visible", "width", "x", "y", "orientation", "properties", "tileheight", "tilesets", "firstgid", "image", "imageheight", "imagewidth", "margin", "spacing", "tilewidth", "version", "terrains", "tiles", "tileoffset", "tile", "terrain", "tileproperties", "transparentcolor" };
typedef enum KEY_e { KEY_HEIGHT, KEY_LAYERS, KEY_DATA, KEY_NAME, KEY_OPACITY, KEY_TYPE, KEY_VISIBLE, KEY_WIDTH, KEY_X, KEY_Y, KEY_ORIENTATION, KEY_PROPERTIES, KEY_TILEHEIGHT, KEY_TILESETS, KEY_FIRSTGID, KEY_IMAGE, KEY_IMAGEHEIGHT, KEY_IMAGEWIDTH, KEY_MARGIN, KEY_SPACING, KEY_TILEWIDTH, KEY_VERSION, KEY_TERRAINS, KEY_TILES, KEY_TILEOFFSET, KEY_TILE, KEY_TERRAIN, KEY_TILEPROPERTIES, KEY_TRANSPARENTCOLOR, KEY_MAX } KEY;

jsmntok_t* jsonTokenise(const char* js);
GAE_BOOL json_token_streq(char* js, jsmntok_t* t, char* s);
char* json_token_tostr(char* js, jsmntok_t* t);

void parseRootKey(jsmntok_t* token, char* string, const KEY key, GAE_Tiled_t* tiledParser);
void parseLayerKey(jsmntok_t* token, char* string, const KEY key, GAE_Tiled_Layer_t* layerParser);
void parseTilesetKey(jsmntok_t* token, char* string, const KEY key, GAE_Tiled_Tileset_t* tilesetParser);
void parseTerrainKey(jsmntok_t* token, char* string, const KEY key, GAE_Tiled_Terrain_t* terrainParser);
void parseTileKey(jsmntok_t* token, char* string, const KEY key, GAE_Tiled_Tile_t* tileParser);
GAE_Array_t* parseData(jsmntok_t* token, char* string);

GAE_Tiled_t* handleMap(jsmntok_t* tokens, char* string);
GAE_Tiled_Layer_t* handleLayer(jsmntok_t* tokens, char* string);
GAE_Tiled_Tileset_t* handleTileset(jsmntok_t* tokens, char* string);

GAE_BOOL StringCompare(void* A, void* B) {
	char* a = (char*)A;
	char* b = (char*)B;
	
	return !strncmp(a, b, strlen(a)); /*strncmp returns 0 if they match*/
}

GAE_Tiled_t* GAE_TiledParser_create(struct GAE_File_s* const file) {
	GAE_FILE_STATUS openStatus;
	GAE_FILE_READ_STATUS readStatus;
	jsmntok_t* tokens = 0;

	GAE_File_open(file, GAE_FILE_OPEN_READ, GAE_FILE_ASCII, &openStatus);
	GAE_File_read(file, GAE_FILE_READ_ALL, &readStatus);
	tokens = jsonTokenise((char*)file->buffer);

	return handleMap(tokens, (char*)file->buffer);
}

void GAE_TiledParser_delete(GAE_Tiled_t* tiledParser) {
	free(tiledParser);
	tiledParser = 0;
}

jsmntok_t* jsonTokenise(const char* js) {
	jsmn_parser parser;
	unsigned int numTokens = JSON_TOKENS;
	jsmntok_t* tokens = (jsmntok_t*)malloc(sizeof(jsmntok_t) * numTokens);
	int ret = 0;

	jsmn_init(&parser);
	ret = jsmn_parse(&parser, js, tokens, numTokens);

	while (ret == JSMN_ERROR_NOMEM) { /* Not enough tokens allocated, allocate some more */
		numTokens = numTokens * 2 + 1;
		tokens = realloc(tokens, sizeof(jsmntok_t) * numTokens);
		ret = jsmn_parse(&parser, js, tokens, numTokens);
	}

	if (ret == JSMN_ERROR_INVAL) {
		/*log_die("jsmn_parse: invalid JSON string");*/
	}
	if (ret == JSMN_ERROR_PART) {
		/*log_die("jsmn_parse: truncated JSON string");*/
	}

    return tokens;
}

GAE_BOOL json_token_streq(char* js, jsmntok_t* t, char* s) {
	return (0 == strncmp(js + t->start, s, t->end - t->start)
		&& strlen(s) == (size_t) (t->end - t->start));
}

char* json_token_tostr(char* js, jsmntok_t* t) {
	js[t->end] = '\0';
	return js + t->start;
}

GAE_Tiled_t* handleMap(jsmntok_t* tokens, char* string) {
	GAE_Tiled_t* tiledParser = (GAE_Tiled_t*)malloc(sizeof(GAE_Tiled_t));

	unsigned int index = 0U;
	unsigned int currentToken = 1U;
	unsigned int objects = 0U;
	unsigned int keyIndex = 0U;
	unsigned int depth = 0U;
	int parent = 0U;
	jsmntok_t* token = &tokens[index];

	memset(tiledParser, 0, sizeof(GAE_Tiled_t));

	tiledParser->layers = GAE_Array_create(sizeof(GAE_Tiled_Layer_t));
	tiledParser->tilesets = GAE_Array_create(sizeof(GAE_Tiled_Tileset_t));
	tiledParser->properties = 0;

	assert(token->type == JSMN_OBJECT); /* First token should be the entire JSON object */

	objects = token->size / 2U; /* How many objects and things have we here? JSMN counts open/closed objects. */

	for (index = 0U; index < objects;) {
		token = &tokens[currentToken++];

		if (token->parent < parent) {
			--depth;
			parent = token->parent;

			if (parent == 0)
				depth = 0;
		}

		for (keyIndex = 0U; keyIndex < KEY_MAX; ++keyIndex) {
			if (json_token_streq(string, token, KEYS[keyIndex])) {
				if (0 == depth) {
					parseRootKey(&tokens[currentToken], string, keyIndex, tiledParser);
					++index;
				}
				break;
			}
		}
		if ((token->type == JSMN_OBJECT) || (token->type == JSMN_ARRAY)) {
			++depth;
			parent = currentToken - 1U;
		}
	}

    return tiledParser;
}

GAE_Tiled_Layer_t* handleLayer(jsmntok_t* tokens, char* string) {
	GAE_Tiled_Layer_t* layer = (GAE_Tiled_Layer_t*)malloc(sizeof(GAE_Tiled_Layer_t));

	unsigned int index = 0U;
	unsigned int currentToken = 1U;
	unsigned int objects = 0U;
	unsigned int keyIndex = 0U;
	jsmntok_t* token = &tokens[index];

	memset(layer, 0, sizeof(GAE_Tiled_Layer_t));

	assert(token->type == JSMN_OBJECT);
	objects = token->size / 2U;

	for (index = 0U; index < objects;) {
		token = &tokens[currentToken++];

		for (keyIndex = 0U; keyIndex < KEY_MAX; ++keyIndex) {
			if (json_token_streq(string, token, KEYS[keyIndex])) {
				parseLayerKey(&tokens[currentToken], string, keyIndex, layer);
				++index;
				break;
			}
		}
	}
	return layer;
}

GAE_Tiled_Tileset_t* handleTileset(jsmntok_t* tokens, char* string) {
	GAE_Tiled_Tileset_t* tileset = (GAE_Tiled_Tileset_t*)malloc(sizeof(GAE_Tiled_Tileset_t));
	unsigned int index = 0U;
	unsigned int currentToken = 1U;
	unsigned int objects = 0U;
	unsigned int keyIndex = 0U;
	jsmntok_t* token = &tokens[index];
	int parent = (&tokens[currentToken])->parent;

	memset(tileset, 0, sizeof(GAE_Tiled_Tileset_t));
	tileset->terrains = GAE_Array_create(sizeof(GAE_Tiled_Terrain_t));
	tileset->tiles = GAE_Array_create(sizeof(GAE_Tiled_Tile_t));

	assert(token->type == JSMN_OBJECT);
	objects = token->size / 2U;

	for (index = 0U; index < objects;) {
		token = &tokens[currentToken++];

		if ((&tokens[currentToken])->parent == parent) {
			for (keyIndex = 0U; keyIndex < KEY_MAX; ++keyIndex) {
				if (json_token_streq(string, token, KEYS[keyIndex])) {
					parseTilesetKey(&tokens[currentToken], string, keyIndex, tileset);
					++index;
					break;
				}
			}
		}
	}

	return tileset;
}

GAE_Tiled_Terrain_t* handleTerrains(jsmntok_t* tokens, char* string) {
	GAE_Tiled_Terrain_t* terrain = malloc(sizeof(GAE_Tiled_Terrain_t));
	unsigned int index = 0U;
	unsigned int currentToken = 1U;
	unsigned int objects = 0U;
	unsigned int keyIndex = 0U;
	jsmntok_t* token = &tokens[index];
	int parent = (&tokens[currentToken])->parent;

	objects = token->size / 2U;
	memset(terrain, 0, sizeof(GAE_Tiled_Terrain_t));

	for (index = 0U; index < objects;) {
		token = &tokens[currentToken++];

		if ((&tokens[currentToken])->parent == parent) {
			for (keyIndex = 0U; keyIndex < KEY_MAX; ++keyIndex) {
				if (json_token_streq(string, token, KEYS[keyIndex])) {
					parseTerrainKey(&tokens[currentToken], string, keyIndex, terrain);
					++index;
					break;
				}
			}
		}
	}

	if (0 == strlen(terrain->name)) {
		free (terrain);
		terrain = 0;
	}

	return terrain;
}

GAE_Tiled_Tile_t* handleTiles(jsmntok_t* tokens, char* string) {
	GAE_Tiled_Tile_t* tile = malloc(sizeof(GAE_Tiled_Tile_t));
	unsigned int index = 0U;
	unsigned int currentToken = 1U;
	unsigned int objects = 0U;
	unsigned int keyIndex = 0U;
	jsmntok_t* token = &tokens[index];

	memset(tile, 0, sizeof(GAE_Tiled_Tile_t));
	tile->id = atoi(json_token_tostr(string, token));
	token = &tokens[1U];

	objects = tokens->size / 2U;
	printf("Objects: %d\n%s\n", objects, json_token_tostr(string,tokens));

	for (index = 0U; index < objects;) {
		for (keyIndex = 0U; keyIndex < KEY_MAX; ++keyIndex) {
			if (json_token_streq(string, &token[currentToken], KEYS[keyIndex])) {
				parseTileKey(&token[currentToken], string, keyIndex, tile);
				++index;
				break;
			}
		}
	}
	
	return tile;
}

GAE_Map_t* handleProperties(jsmntok_t* tokens, char* string) {
	char keyBuffer[256];
	char valueBuffer[256];
	unsigned int index = 0;
	unsigned int objects = 0U;
	unsigned int currentToken = 1U;
	unsigned int keySize = 256U;
	unsigned int valueSize = 256U;
	char* keyString = 0;
	char* valueString = 0;

	GAE_Map_t* map = GAE_Map_create(sizeof(keyBuffer), sizeof(valueBuffer), StringCompare);
	jsmntok_t* key = tokens;
	jsmntok_t* value = tokens;

	assert(key->type == JSMN_OBJECT); /* First token should be the entire JSON object */

	objects = key->size / 2U; /* How many objects and things have we here? JSMN counts open/closed objects. */

	for (index = 0U; index < objects; ++index) {
		key = &tokens[currentToken++];
		value = &tokens[currentToken++];

		keyString = json_token_tostr(string, key);
		valueString = json_token_tostr(string, value);

		if (255 > strlen(keyString))
			keySize = strlen(keyString) + 1;
		else keySize = 255;

		if (255 > strlen(valueString))
			valueSize = strlen(valueString) + 1;
		else valueSize = 255;
		
		strncpy(keyBuffer, (void*)json_token_tostr(string, key), keySize);
		strncpy(valueBuffer, json_token_tostr(string, value), valueSize);
		GAE_Map_push(map, (void*)keyBuffer, (void*)valueBuffer);
      }

    return map;
}

void parseRootKey(jsmntok_t* token, char* string, const KEY key, GAE_Tiled_t* tiledParser) {
	switch (key) {
		case KEY_HEIGHT: {
			tiledParser->height = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_WIDTH: {
			tiledParser->width = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_PROPERTIES: {
			if (0 == tiledParser->properties)
				tiledParser->properties = handleProperties(token, string);
		}
		break;
		case KEY_ORIENTATION: {
			if (json_token_streq(string, token, "isometric"))
				tiledParser->orientation = GAE_TILED_ISOMETRIC;
			else if (json_token_streq(string, token, "orthagonal"))
				tiledParser->orientation = GAE_TILED_ORTHAGONAL;
			else if (json_token_streq(string, token, "staggered"))
				tiledParser->orientation = GAE_TILED_STAGGERED;
		}
		break;
		case KEY_TILEHEIGHT: {
			tiledParser->tileHeight = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_TILEWIDTH: {
			tiledParser->tileWidth = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_VERSION: {
			tiledParser->version = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_LAYERS: {
			unsigned int objects = token->size;
			unsigned int index = 0U;
			if (token->type == JSMN_OBJECT) {
				index = 1U;
				objects = 1U;
			}

			for (index = 0U; 0U != objects; ++index) {
				if (JSMN_OBJECT == token[index].type) {
					GAE_Tiled_Layer_t* newLayer = handleLayer(&token[index], string);
					assert(newLayer);
					GAE_Array_push(tiledParser->layers, newLayer);
					--objects;
				}
			}
		}
		break;
		case KEY_TILESETS: {
			unsigned int objects = token->size;
			unsigned int index = 0U;
			if (token->type == JSMN_OBJECT) {
				objects = 1U;
				index = 1U;
			}

			for (index = 0U; 0U != objects; ++index) {
				if (JSMN_OBJECT == token[index].type) {
					GAE_Tiled_Tileset_t* newTileset = handleTileset(&token[index], string);
					assert(newTileset);
					GAE_Array_push(tiledParser->tilesets, newTileset);
					--objects;
				}
			}
		}
		default:
		break;
	}
}

void parseLayerKey(jsmntok_t* token, char* string, const KEY key, GAE_Tiled_Layer_t* layerParser) {
	switch (key) {
		case KEY_HEIGHT: {
			layerParser->height = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_WIDTH: {
			layerParser->width = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_DATA: {
			if (0 == layerParser->data)
				layerParser->data = parseData(token, string);
		}
		break;
		case KEY_NAME: {
			char* name = json_token_tostr(string, token);
			unsigned int length = strlen(name);

			if (127 > length)
				length = 127;

			strncpy(layerParser->name, name, length);
		}
		break;
		case KEY_OPACITY: {
			layerParser->opacity = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_TYPE: {
			char* type = json_token_tostr(string, token);
			unsigned int length = strlen(type);

			if (127 > length)
				length = 127;

			strncpy(layerParser->type, type, length);
		}
		break;
		case KEY_VISIBLE: {
			layerParser->visible = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_X: {
			layerParser->x = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_Y: {
			layerParser->y = atoi(json_token_tostr(string, token));
		}
		default:
		break;
	}
}

void parseTilesetKey(jsmntok_t* token, char* string, const KEY key, GAE_Tiled_Tileset_t* tilesetParser) {
	switch (key) {
		case KEY_FIRSTGID: {
			tilesetParser->firstGid = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_IMAGEWIDTH: {
			tilesetParser->imageWidth = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_IMAGEHEIGHT: {
			tilesetParser->imageHeight = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_MARGIN: {
			tilesetParser->margin = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_SPACING: {
			tilesetParser->spacing = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_TILEWIDTH: {
			tilesetParser->tileWidth = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_TILEHEIGHT: {
			tilesetParser->tileHeight = atoi(json_token_tostr(string, token));
		}
		break;
		case KEY_TILEOFFSET: {
			tilesetParser->offset[0] = atoi(json_token_tostr(string, token + 2));
			tilesetParser->offset[1] = atoi(json_token_tostr(string, token + 4));
		}
		break;
		case KEY_IMAGE: {
			tilesetParser->image = GAE_Sprite_create(json_token_tostr(string, token));			
		}
		break;
		case KEY_TERRAINS: {
		}
		break;
		case KEY_TILES: {
		}
		break;
		case KEY_PROPERTIES: {
			tilesetParser->properties = handleProperties(token, string);
		}
		break;
		case KEY_NAME: {
			char* name = json_token_tostr(string, token);
			unsigned int length = strlen(name);

			if (127 > length)
				length = 127;

			strncpy(tilesetParser->name, name, length);
		}
		break;
		default:
		break;
	}
}

void parseTerrainKey(jsmntok_t* token, char* string, const KEY key, GAE_Tiled_Terrain_t* terrainParser) {
	switch (key) {
		case KEY_NAME: {
			char* name = json_token_tostr(string, token);
			unsigned int length = strlen(name);

			if (127 > length)
				length = 127;

			strncpy(terrainParser->name, name, length);
			printf("Terrain: %s\n", terrainParser->name);
		}
		break;
		case KEY_TILE: {
			terrainParser->tile = atoi(json_token_tostr(string, token));
		}
		break;
		default:
		break;
	}
}

void parseTileKey(jsmntok_t* token, char* string, const KEY key, GAE_Tiled_Tile_t* tileParser) {
	switch (key) {
		case KEY_TERRAIN: {
			tileParser->terrain[0U] = atoi(json_token_tostr(string, token + 2U));
			tileParser->terrain[1U] = atoi(json_token_tostr(string, token + 3U));
			tileParser->terrain[2U] = atoi(json_token_tostr(string, token + 4U));
			tileParser->terrain[3U] = atoi(json_token_tostr(string, token + 5U));
		}
		break;
		default:
		break;
	}
}

GAE_Array_t* parseData(jsmntok_t* token, char* string) {
	GAE_Array_t* data = GAE_Array_create(sizeof(unsigned int));
	unsigned int index = 0U;
	unsigned int currentToken = 1U;
	const unsigned int size = token->size;
	unsigned int value = 0U;
	assert(token->type == JSMN_ARRAY);

	for (index = 0U; index < size; ++index) {
		value = atoi(json_token_tostr(string, token + currentToken));
		GAE_Array_push(data, (void*)&value);
		++currentToken;
	}

	return data;
}


GAE_Tiled_Tileset_t* getTileset(GAE_Tiled_t* tilemap, const unsigned int tileId) {
	const unsigned int tilesetCount = GAE_Array_length(tilemap->tilesets);
	unsigned int index = 0U;
	
	if (tilesetCount == 1U)
		return (GAE_Tiled_Tileset_t*)GAE_Array_begin(tilemap->tilesets);
	
	for (index = 0U; index < tilesetCount; ++index) {
		GAE_Tiled_Tileset_t* tileset = (GAE_Tiled_Tileset_t*)GAE_Array_get(tilemap->tilesets, index);
		if (tileId > tileset->firstGid)
			return tileset;
	}
	
	return NULL;
}

unsigned int GAE_TiledParser_getTileId(GAE_Tiled_t* tilemap, const unsigned int x, const unsigned int y, const unsigned int layerId) {
	GAE_Tiled_Layer_t* layer = (GAE_Tiled_Layer_t*)GAE_Array_get(tilemap->layers, layerId);
	return *(unsigned int*)GAE_Array_get(layer->data, y * layer->width + x) - 1U;
}

