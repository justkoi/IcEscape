LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := helloworld_shared

LOCAL_MODULE_FILENAME := libhelloworld

LOCAL_SRC_FILES := helloworld/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/TeamLogoScene.cpp \
                   ../../Classes/LogoScene.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/MenuScene.cpp \
                   ../../Classes/CreditScene.cpp\
                   ../../Classes/Block.cpp \
                   ../../Classes/Map.cpp \
		   ../../Classes/CEffectManager.cpp \
		   ../../Classes/StageMenuScene.cpp \
		   ../../Classes/SeaLevel.cpp \
		   ../../Classes/IceChunk.cpp \
		   ../../Classes/CNumber.cpp \
		   ../../Classes/CParserNumber.cpp \
		   ../../Classes/Ice.cpp \
		   ../../Classes/Sled.cpp \
		   ../../Classes/Fish.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)


