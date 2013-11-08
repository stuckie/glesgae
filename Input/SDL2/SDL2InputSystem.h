#ifndef _SDL2_INPUT_SYSTEM_H_
#define _SDL2_INPUT_SYSTEM_H_

struct GAE_EventSystem_s;
struct GAE_Keyboard_s;
struct GAE_Pointer_s;
struct GAE_Pad_s;
struct GAE_Joystick_s;
struct GAE_SingleList_s;
struct GAE_Event_s;

typedef struct GAE_InputSystem_s {
	struct GAE_EventSystem_s* eventSystem;
	struct GAE_Keyboard_s* keyboard;
	struct GAE_Pointer_s* pointer;
	struct GAE_SingleList_s* joysticks;
	struct GAE_SingleList_s* pads;
} GAE_InputSystem_t;

GAE_InputSystem_t* GAE_InputSystem_create(struct GAE_EventSystem_s* eventSystem);
void GAE_InputSystem_delete(GAE_InputSystem_t* system);

GAE_InputSystem_t* GAE_InputSystem_newPointer(GAE_InputSystem_t* system);
GAE_InputSystem_t* GAE_InputSystem_newPad(GAE_InputSystem_t* system);
GAE_InputSystem_t* GAE_InputSystem_newKeyboard(GAE_InputSystem_t* system);
GAE_InputSystem_t* GAE_InputSystem_newJoystick(GAE_InputSystem_t* system);

GAE_InputSystem_t* GAE_InputSystem_removePointer(GAE_InputSystem_t* system, struct GAE_Pointer_s* const pointer);
GAE_InputSystem_t* GAE_InputSystem_removePad(GAE_InputSystem_t* system, struct GAE_Pad_s* const pad);
GAE_InputSystem_t* GAE_InputSystem_removeKeyboard(GAE_InputSystem_t* system, struct GAE_Keyboard_s* const keyboard);
GAE_InputSystem_t* GAE_InputSystem_removeJoystick(GAE_InputSystem_t* system, struct GAE_Joystick_s* const joystick);

GAE_InputSystem_t* GAE_InputSystem_update(GAE_InputSystem_t* system);
void GAE_InputSystem_getEvent(struct GAE_Event_s* const event, void* userData);

#endif
