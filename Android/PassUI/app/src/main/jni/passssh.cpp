#include "passssh.h"
#include "passsshlog.h"

JNIEXPORT jboolean JNICALL Java_com_ratusapparatus_passssh_PassSSH_Init(JNIEnv *, jobject, jstring, jstring, jstring, jobject)
{
	DPRINTF( "%s\n", __FUNCTION__ );
}

JNIEXPORT jobjectArray JNICALL Java_com_ratusapparatus_passssh_PassSSH_GetPassIDs(JNIEnv *, jobject)
{
	DPRINTF( "%s\n", __FUNCTION__ );
}

JNIEXPORT jstring JNICALL Java_com_ratusapparatus_passssh_PassSSH_GetPass(JNIEnv *, jobject, jstring)
{
	DPRINTF( "%s\n", __FUNCTION__ );
}