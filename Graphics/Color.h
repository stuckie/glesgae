#ifndef _COLOR_H_
#define _COLOR_H_

typedef union GAE_Color_u { 
	typedef struct rgba_s { 
		unsigned char r, g, b, a;
	} rgba;
	unsigned char components[4];
	unsigned int hex;
} GAE_Color_t;

#endif
