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
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := ssh2
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include  $(LOCAL_PATH)/src E:/openssl-android/include
LOCAL_SRC_FILES := src/agent.c \
src/channel.c \
src/comp.c \
src/crypt.c \
src/global.c \
src/hostkey.c \
src/keepalive.c \
src/kex.c \
src/knownhost.c \
src/libgcrypt.c \
src/mac.c \
src/misc.c \
src/openssl.c \
src/packet.c \
src/pem.c \
src/publickey.c \
src/scp.c \
src/session.c \
src/sftp.c \
src/transport.c \
src/userauth.c \
src/version.c \

include $(BUILD_STATIC_LIBRARY)
