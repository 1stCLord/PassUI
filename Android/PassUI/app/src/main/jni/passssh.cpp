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

std::wstring JStringToWString(JNIEnv *env, jstring string)
{
    std::wstring value;

    const jchar *raw = env->GetStringChars(string, 0);
    jsize len = env->GetStringLength(string);
    const jchar *temp = raw;

    value.assign(raw, raw + len);

    env->ReleaseStringChars(string, raw);

    return value;
}

jobjectArray vectorToList(JNIEnv * env, vector<string> &list)
{
	jclass jstringClass = env->FindClass("java/lang/String");
	jobjectArray jlist = env->NewObjectArray(list.size(),jstringClass, 0); 

	for(uint16_t i = 0; i < list.size(); ++i)
	{
		for(uint16_t j = 0; j < list[i].size(); ++ j)
		{
			list[i][j] = list[i][j] < 127 ? list[i][j] : ' ';
		}
	
		jstring jvalue = env->NewStringUTF(list[i].c_str());
		env->SetObjectArrayElement(jlist, i, jvalue);
	}
	return jlist;
}

string stripEndWhiteSpace(string input)
{
	size_t posStart = input.find_first_not_of(" \n\r");
	size_t posEnd = input.find_last_not_of(" \n\r");
	return input.substr(posStart,posEnd-posStart);
}

JNIEXPORT jlong JNICALL Java_com_ratusapparatus_passssh_PassSSH_Create(JNIEnv *, jobject)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	return (uintptr_t)new PassSSH();
}

JNIEXPORT jboolean JNICALL Java_com_ratusapparatus_passssh_PassSSH_Init(JNIEnv * env, jobject obj, jstring jserver, jint jport, jstring jusername, jstring jpassphrase, jstring jkey, jstring jpubkey, jobject jauthtype)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	jclass javaClass = env->GetObjectClass(jauthtype);
	jmethodID authTypeOrdinal = env->GetMethodID(javaClass, "ordinal", "()I");	
	PassSSH *passSSH = ptr<PassSSH>(env, obj);
	return passSSH->Init(env->GetStringUTFChars(jserver, JNI_FALSE), jport, env->GetStringUTFChars(jusername, JNI_FALSE), env->GetStringUTFChars(jpassphrase,JNI_FALSE), env->GetStringUTFChars(jkey, JNI_FALSE), env->GetStringUTFChars(jpubkey, JNI_FALSE), (AuthType)env->CallIntMethod(jauthtype, authTypeOrdinal));
}

JNIEXPORT jobjectArray JNICALL Java_com_ratusapparatus_passssh_PassSSH_GetPassIDs(JNIEnv *env, jobject obj)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	PassSSH *passSSH = ptr<PassSSH>(env, obj);
	vector<string> passIDs = passSSH->GetPassIDs();
	return vectorToList(env, passIDs);
}

JNIEXPORT jstring JNICALL Java_com_ratusapparatus_passssh_PassSSH_GetPass(JNIEnv *env, jobject obj, jstring jid, jstring jgpg_password)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	PassSSH *passSSH = ptr<PassSSH>(env, obj);
	string id = env->GetStringUTFChars(jid, JNI_FALSE);
	string gpg_password = env->GetStringUTFChars(jgpg_password, JNI_FALSE);
	string pass = passSSH->GetPass(id,gpg_password);
	pass = stripEndWhiteSpace(pass);
	return env->NewStringUTF(pass.c_str());
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