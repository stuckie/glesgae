LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := glesgae

FILE_LIST := $(wildcard $(LOCAL_PATH)/../Events/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Events/Android/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../External/**/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../External/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Factories/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../File/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../File/Android/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Context/Android/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Platform/Android/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Renderer/GLES20/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/State/GLES2/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Target/Buffer/GLES20/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Target/Screen/GLES20/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Graphics/Window/Android/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Input/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Input/Android/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Maths/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Platform/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Platform/Android/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Resources/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Scripting/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../States/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Time/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Time/Android/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../Utils/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../*.cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_CFLAGS	:= -DGLES2 -DANDROID
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)




