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

jobjectArray vectorToList(JNIEnv * env, const vector<string> &list)
{
	jclass jstringClass = env->FindClass("java/lang/String");
	jobjectArray jlist = env->NewObjectArray(list.size(),jstringClass, 0); 

	for(uint16_t i = 0; i < list.size(); ++i)
	{
		jstring jvalue = env->NewStringUTF(list[i].c_str());
		env->SetObjectArrayElement(jlist, i, jvalue);
	}
	return jlist;
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
	jmethodID authTypeOrdinal = env->GetMethodID(javaClass, "ordinal", "()I");	
	PassSSH *passSSH = ptr<PassSSH>(env, obj);
	return passSSH->Init(env->GetStringUTFChars(jserver, JNI_FALSE), env->GetStringUTFChars(jusername, JNI_FALSE), env->GetStringUTFChars(jpassphrase, JNI_FALSE), (AuthType)env->CallIntMethod(jauthtype, authTypeOrdinal));
}

JNIEXPORT jobjectArray JNICALL Java_com_ratusapparatus_passssh_PassSSH_GetPassIDs(JNIEnv *env, jobject obj)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	PassSSH *passSSH = ptr<PassSSH>(env, obj);
	vector<string> passIDs = passSSH->GetPassIDs();
	return vectorToList(env, passIDs);
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