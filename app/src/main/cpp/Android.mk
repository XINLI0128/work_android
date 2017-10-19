LOCAL_PATH := $(call my-dir)
include $(LOCAL_PATH)/assimp.mk
include $(CLEAR_VARS)


LOCAL_MODULE := native-lib

LOCAL_C_INCLUDES += $(LOCAL_PATH)/assimp/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/glm/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/glm/detail/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/glm/gtc/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/glm/gtx/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/glm/simd/



FILE_LIST += $(wildcard $(LOCAL_PATH)/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/assimp/*.hpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/glm/*.hpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/glm/detail/*.hpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/glm/gtx/*.hpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/glm/gtc/*.hpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/glm/simd/*.hpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)


LOCAL_SRC_FILES+=/home/xinli/MyApplication/app/src/main/cpp/libassimp.so
LOCAL_SHARED_LIBRARIES := libassimp


LOCAL_CLANG := true
LOCAL_CPPFLAGS += -std=c++1y -frtti -Wall
LOCAL_LDFLAGS := -llog -lEGL -landroid -lGLESv2 -ljnigraphics

include $(BUILD_SHARED_LIBRARY)







