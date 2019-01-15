#ifndef _COLOUR_H_
#define _COLOUR_H_

typedef struct GAE_Colour_RGBA_s { 
		unsigned char r, g, b, a;
	} GAE_Colour_RGBA_t;

typedef union GAE_Colour_u { 
	GAE_Colour_RGBA_t rgba;
	unsigned char components[4];
	unsigned int hex;
} GAE_Colour_t;

#endif
