#include "passssh_native.h"
#include "sshlib2/include/libssh2.h"
#include <cassert>
#include "passsshlog.h"

bool PassSSH::Init(string server, string username, string passphrase, AuthType authType)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	assert(libssh2_init(0));
	return false;
}
 
vector<string> PassSSH::GetPassIDs()
{
/*const char *data[8]= {
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
	
    return ret;*/
	return vector<string>();
}