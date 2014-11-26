#include "passssh.h"
#include "passsshlog.h"

class PassSSH
{
};

PassSSH passSSH;

JNIEXPORT jboolean JNICALL Java_com_ratusapparatus_passssh_PassSSH_Init(JNIEnv *, jobject, jstring, jstring, jstring, jobject)
{
	DPRINTF( "%s\n", __FUNCTION__ );
}

JNIEXPORT jobjectArray JNICALL Java_com_ratusapparatus_passssh_PassSSH_GetPassIDs(JNIEnv *env, jobject)
{
	DPRINTF( "%s\n", __FUNCTION__ );
    const char *data[8]= {
	"google.com", 
	"outlook.com", 
	"paypal.com", 
	"github.com", 
	"facebook.com", 
	"twitter.com", 
	"youtube.com", 
	"wordpress.com"};

    //ret = (jobjectArray)env->NewObjectArray(8,env->FindClass("java/lang/String"),env->NewStringUTF(""));
	jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray ret = env->NewObjectArray(8, stringClass, 0);

    for (int i = 0; i < 8; ++i) 
	{
		env->SetObjectArrayElement(ret, i, env->NewStringUTF(data[i]));
    }
	
    return ret;
}

JNIEXPORT jstring JNICALL Java_com_ratusapparatus_passssh_PassSSH_GetPass(JNIEnv *env, jobject, jstring)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	return env->NewStringUTF("pass");
}

JNIEXPORT void JNICALL Java_com_ratusapparatus_passssh_PassSSH_InsertPass(JNIEnv *, jobject, jstring, jstring)
{
	DPRINTF( "%s\n", __FUNCTION__ );
}

JNIEXPORT void JNICALL Java_com_ratusapparatus_passssh_PassSSH_GeneratePass(JNIEnv *, jobject, jstring, jboolean, jint)
{
	DPRINTF( "%s\n", __FUNCTION__ );
}