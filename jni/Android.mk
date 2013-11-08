LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := glesgae

FILE_LIST := $(wildcard $(LOCAL_PATH)/../Events/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Events/SDL2/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../External/jsmn/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../File/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../File/Android/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Context/SDL2/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Renderer/SDL2/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Sprite/SDL2/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Target/Texture/SDL2/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Texture/SDL2/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Window/SDL2/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Input/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Input/SDL2/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Maths/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Platform/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Platform/SDL2/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../States/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Time/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Time/Android/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Utils/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../*.c)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

SDL_INCLUDES := ../../SDL2_includes

LOCAL_C_INCLUDES :=	$(LOCAL_PATH)/$(SDL_INCLUDES)

LOCAL_SHARED_LIBRARIES := android_native_app_glue SDL2 SDL2_image
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv1_CM
LOCAL_CFLAGS	:= -DSDL2 -DANDROID
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)

