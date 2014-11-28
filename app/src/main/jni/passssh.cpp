#include "passssh.h"
#include "passssh_native.h"
#include "passsshlog.h"
#include <cstdint>

template<typename T>
T *ptr(JNIEnv *env, jobject obj)
{
  jclass javaClass = env->GetObjectClass(obj);
  jmethodID methodID = env->GetMethodID(javaClass, "ptr", "()J");
  if(methodID)
  {
	return (T*)(uintptr_t)env->CallLongMethod(obj, methodID);
  }
  return NULL;
}

JNIEXPORT jlong JNICALL Java_com_ratusapparatus_passssh_PassSSH_Create(JNIEnv *, jobject)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	return (uintptr_t)new PassSSH();
}

JNIEXPORT jboolean JNICALL Java_com_ratusapparatus_passssh_PassSSH_Init(JNIEnv * env, jobject obj, jstring jserver, jstring jusername, jstring jpassphrase, jobject jauthtype)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	jclass javaClass = env->GetObjectClass(jauthtype);
	DPRINTF( "%d\n", __LINE__ );
	jmethodID authTypeOrdinal = env->GetMethodID(javaClass, "ordinal", "()I");	
	DPRINTF( "%d\n", __LINE__ );
	PassSSH *passSSH = ptr<PassSSH>(env, obj);
	DPRINTF( "%d\n", __LINE__ );
	return passSSH->Init(env->GetStringUTFChars(jserver, JNI_FALSE), env->GetStringUTFChars(jusername, JNI_FALSE), env->GetStringUTFChars(jpassphrase, JNI_FALSE), (AuthType)env->CallIntMethod(jauthtype, authTypeOrdinal));
}

JNIEXPORT jobjectArray JNICALL Java_com_ratusapparatus_passssh_PassSSH_GetPassIDs(JNIEnv *env, jobject obj)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	PassSSH *passSSH = ptr<PassSSH>(env, obj);
}

JNIEXPORT jstring JNICALL Java_com_ratusapparatus_passssh_PassSSH_GetPass(JNIEnv *env, jobject obj, jstring)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	PassSSH *passSSH = ptr<PassSSH>(env, obj);
}

JNIEXPORT void JNICALL Java_com_ratusapparatus_passssh_PassSSH_InsertPass(JNIEnv *env, jobject obj, jstring, jstring)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	PassSSH *passSSH = ptr<PassSSH>(env, obj);
}

JNIEXPORT void JNICALL Java_com_ratusapparatus_passssh_PassSSH_GeneratePass(JNIEnv *env, jobject obj, jstring, jboolean, jint)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	PassSSH *passSSH = ptr<PassSSH>(env, obj);
}