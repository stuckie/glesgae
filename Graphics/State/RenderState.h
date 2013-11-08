#ifndef _RENDER_STATE_H_
#define _RENDER_STATE_H_

#include "../../GAE_Types.h"

struct GAE_Camera_s;

typedef struct GAE_RenderState_s {
	struct GAE_Camera_s* camera;
	GAE_BOOL isTexturingEnabled;
	GAE_BOOL isAlphaBlendingEnabled;
	void* platform;
} GAE_RenderState_t;

#endif
