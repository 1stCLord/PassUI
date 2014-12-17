#ifdef __ANDROID__
#include <android/log.h>

//==============================
// Declarations
//==============================
#define LOG_TAG "mainActivity.cpp"
#define DPRINTF(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define IPRINTF(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define EPRINTF(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
#define DPRINTF(...)  printf(__VA_ARGS__)
#endif