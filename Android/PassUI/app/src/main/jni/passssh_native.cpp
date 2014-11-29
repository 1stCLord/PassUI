#include "passssh_native.h"
#include "sshlib2/include/libssh2.h"
#include <cassert>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "passsshlog.h"

bool PassSSH::Init(string server, string username, string passphrase, AuthType authType)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	m_server = server;
	m_username = username;
	m_passphrase = passphrase;
	m_authType = authType;
	m_port = 22;
	return libssh2_init(0);
}
 
vector<string> PassSSH::GetPassIDs()
{
	SessionStart();
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

string PassSSH::GetPass(string id)
{
	SessionStart();
}

void PassSSH::InsertPass(string id, string pass)
{
	SessionStart();
}

void PassSSH::GeneratePass(string id, bool withSymbols, int length)
{
	SessionStart();
}

void PassSSH::SessionStart()
{
	DPRINTF( "%s\n", __FUNCTION__ );
	struct sockaddr_in sin;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
 
    sin.sin_family = AF_INET;
    sin.sin_port = htons(m_port);
	struct hostent *he = gethostbyname(m_server.c_str());
    DPRINTF("Official name is: %s\n", he->h_name);
    DPRINTF("    IP addresses: ");
    struct in_addr **addr_list = (struct in_addr **)he->h_addr_list;
    for(int i = 0; addr_list[i] != NULL; i++)
        DPRINTF("%s ", inet_ntoa(*addr_list[i]));
    DPRINTF("\n");
    sin.sin_addr.s_addr = inet_addr(inet_ntoa(*addr_list[0]));
	DPRINTF("%d\n",sin.sin_addr.s_addr);
    if (connect(sock, (struct sockaddr*)(&sin),sizeof(struct sockaddr_in))) 
		DPRINTF("failed to connect!\n");
 
    LIBSSH2_SESSION *session = libssh2_session_init();

    if (libssh2_session_handshake(session, sock))
        DPRINTF("Failure establishing SSH session\n");
		
	const char *fingerprint = libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA1);
	DPRINTF("%s\n",fingerprint);
	char *userauthlist = libssh2_userauth_list(session, m_username.c_str(), m_username.size());
	DPRINTF("%s\n",userauthlist);

	DPRINTF( "%s end\n", __FUNCTION__ );
}