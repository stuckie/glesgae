#ifndef _BASE_LIFECYCLE_H_
#define _BASE_LIFECYCLE_H_

#include "../GAE_Types.h"

typedef void (*GAE_Lifecycle_onCreate_t)(void);
typedef void (*GAE_Lifecycle_onWindowCreate_t)(void);
typedef void (*GAE_Lifecycle_onStart_t)(void);
typedef void (*GAE_Lifecycle_onResume_t)(void);
typedef GAE_BOOL (*GAE_Lifecycle_onLoop_t)(void);
typedef void (*GAE_Lifecycle_onPause_t)(void);
typedef void (*GAE_Lifecycle_onStop_t)(void);
typedef void (*GAE_Lifecycle_onDestroy_t)(void);

typedef struct GAE_Lifecycle_s {
	GAE_Lifecycle_onCreate_t onCreate;
	GAE_Lifecycle_onWindowCreate_t onWindowCreate;
	GAE_Lifecycle_onStart_t onStart;
	GAE_Lifecycle_onResume_t onResume;
	GAE_Lifecycle_onLoop_t onLoop;
	GAE_Lifecycle_onPause_t onPause;
	GAE_Lifecycle_onStop_t onStop;
	GAE_Lifecycle_onDestroy_t onDestroy;
} GAE_Lifecycle_t;

#endif

