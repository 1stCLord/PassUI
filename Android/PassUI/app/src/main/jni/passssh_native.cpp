#include "passssh_native.h"
#include <cassert>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "passsshlog.h"

bool PassSSH::Init(string server, uint16_t port, string username, wstring passphrase, AuthType authType)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	m_server = server;
	m_username = username;
	m_passphrase = passphrase;
	m_authType = authType;
	m_port = port;
	
	m_channel = NULL;
	
	return libssh2_init(0);
}
 
vector<string> PassSSH::GetPassIDs()
{
	SessionStart();
	const char * pass_cmd = "pass\n";
	libssh2_channel_write(m_channel,pass_cmd,5);
	
	vector<string> lines = ReadShell();
	lines.erase(lines.begin());
	lines.erase(lines.begin());
	lines.erase(lines.end());
	
	return lines;
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
    struct in_addr **addr_list = (struct in_addr **)he->h_addr_list;
    sin.sin_addr.s_addr = inet_addr(inet_ntoa(*addr_list[0]));
    if (connect(sock, (struct sockaddr*)(&sin),sizeof(struct sockaddr_in))) 
		DPRINTF("failed to connect!\n");
 
    LIBSSH2_SESSION *session = libssh2_session_init();
	libssh2_session_set_timeout(session, 2000);

    if (libssh2_session_handshake(session, sock))
        DPRINTF("Failure establishing SSH session\n");
		
	const char *fingerprint = libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA1);
	char *userauthlist = libssh2_userauth_list(session, m_username.c_str(), m_username.size());
	
	bool success = false;
	/*if (strstr(userauthlist, "publickey") != NULL)
	{
		libssh2_userauth_publickey(session, m_username.c_str(), password<unsigned char>().c_str(), m_passphrase.size(), NULL, NULL);
	}
    else */if (strstr(userauthlist, "password") != NULL)
	{
		DPRINTF( "ATTEMPTING PASSWORD AUTH\n");
		string pwrd = password<char>();
		success = !libssh2_userauth_password(session, m_username.c_str(), pwrd.c_str());
		 
		 if(success)
		 {
			if ((m_channel = libssh2_channel_open_session(session))) 
			{
				DPRINTF( "CHANNEL CONNECTED\n");
				ShellStart();
			}
		}
	}

	DPRINTF( "%s end\n", __FUNCTION__ );
}

void PassSSH::ShellStart()
{
	libssh2_channel_request_pty(m_channel, "vanilla");
	libssh2_channel_shell(m_channel);
	ReadShell();
}

vector<string> PassSSH::ReadShell()
{
	DPRINTF( "---------\n");
	vector<string> lines;
	lines.push_back(string());
	char buffer[51];
	do
	{
		memset(buffer,0,51);
		size_t read_amount = libssh2_channel_read(m_channel, buffer, 50);
		DPRINTF( "%d\n",read_amount);
		if(read_amount > 0 && read_amount <= 50)
		{
			string substring = string(buffer);
			size_t pos = substring.find('\n');
			while(pos != string::npos)
			{
				lines.back() += substring.substr(0,pos);
				substring = substring.substr(pos+1,string::npos);
				lines.push_back(string());
				pos = substring.find('\n');
			}
			lines.back() += substring;
		}
		else
			break;
	}while(true);
	return lines;
}

template<typename T>
basic_string<T> PassSSH::password()
{
	basic_string<T> password;
	for(wchar_t wide_char : m_passphrase)
	{
		password += (T)wide_char;
	}
	return password;
}