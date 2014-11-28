# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
JNIPATH := $(call my-dir)
LOCAL_PATH := $(JNIPATH)

include $(call all-subdir-makefiles)

LOCAL_PATH := $(JNIPATH)

include $(CLEAR_VARS)
LOCAL_MODULE := ssl
LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libssl.so 
LOCAL_EXPORT_C_INCLUDES := E:/openssl-android/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := crypto
LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libcrypto.so
LOCAL_EXPORT_C_INCLUDES := E:/openssl-android/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := passssh
LOCAL_SRC_FILES := passssh.cpp passssh_native.cpp
LOCAL_STATIC_LIBRARIES := ssh2 ssl crypto
LOCAL_LDLIBS := -llog -lz
include $(BUILD_SHARED_LIBRARY)