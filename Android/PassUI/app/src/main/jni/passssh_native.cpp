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
	
	m_socket = 0;
	m_channel = NULL;
	m_session = NULL;
	
	return libssh2_init(0);
}
 
vector<string> PassSSH::GetPassIDs()
{
	SessionStart();
	const char * pass_cmd = "ls ~/.password-store/ -1\n";
	libssh2_channel_write(m_channel,pass_cmd,strlen(pass_cmd));
	
	vector<string> lines = ReadShell();
	SessionStop();
	lines.erase(lines.begin());
	lines.erase(lines.begin());
	lines.erase(lines.end());
	
	for(uint16_t i = 0; i < lines.size(); ++ i)
	{
		size_t pos = lines[i].find(".gpg");
		if(pos != string::npos)
		{
			lines[i] = lines[i].substr(0,pos);
		}
	}
	
	return lines;
}

string PassSSH::GetPass(string id)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	SessionStart();
	string pass_cmd = "pass " + id + " \n";
	libssh2_channel_write(m_channel,pass_cmd.c_str(),pass_cmd.size());
	ReadShell();
	string keychain_password = "gIbrAltAr2\n";
	libssh2_channel_write(m_channel,keychain_password.c_str(),keychain_password.size());
	vector<string> pass = ReadShell();
	SessionStop();
	DPRINTF( "%s\n", pass[0].c_str() );
	DPRINTF( "%s end\n", __FUNCTION__ );
	return pass[0];
}

void PassSSH::InsertPass(string id, string pass)
{
	SessionStart();
	SessionStop();
}

void PassSSH::GeneratePass(string id, bool withSymbols, int length)
{
	SessionStart();
	SessionStop();
}

void PassSSH::SessionStart()
{
	DPRINTF( "%s\n", __FUNCTION__ );
	SessionStop();
	
	struct sockaddr_in sin;
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
 
    sin.sin_family = AF_INET;
    sin.sin_port = htons(m_port);
	struct hostent *he = gethostbyname(m_server.c_str());
    struct in_addr **addr_list = (struct in_addr **)he->h_addr_list;
    sin.sin_addr.s_addr = inet_addr(inet_ntoa(*addr_list[0]));
    if (connect(m_socket, (struct sockaddr*)(&sin),sizeof(struct sockaddr_in))) 
	{
		DPRINTF("failed to connect!\n");
		SessionStop();
		return;
	}
 
    m_session = libssh2_session_init();
	libssh2_session_set_timeout(m_session, 2000);

    if (libssh2_session_handshake(m_session, m_socket))
	{
        DPRINTF("Failure establishing SSH session\n");
		SessionStop();
		return;
	}
		
	const char *fingerprint = libssh2_hostkey_hash(m_session, LIBSSH2_HOSTKEY_HASH_SHA1);
	char *userauthlist = libssh2_userauth_list(m_session, m_username.c_str(), m_username.size());
	
	bool success = false;
	/*if (strstr(userauthlist, "publickey") != NULL)
	{
		libssh2_userauth_publickey(m_session, m_username.c_str(), password<unsigned char>().c_str(), m_passphrase.size(), NULL, NULL);
	}
    else */if (strstr(userauthlist, "password") != NULL)
	{
		DPRINTF( "ATTEMPTING PASSWORD AUTH\n");
		string pwrd = password<char>();
		success = !libssh2_userauth_password(m_session, m_username.c_str(), pwrd.c_str());
		 
		 if(success)
		 {
			if ((m_channel = libssh2_channel_open_session(m_session))) 
			{
				DPRINTF( "CHANNEL CONNECTED\n");
				ShellStart();
			}
		}
		else
		{
			DPRINTF("Failure authenticating SSH session\n");
			SessionStop();
			return;
		}
	}

	DPRINTF( "%s end\n", __FUNCTION__ );
}

void PassSSH::SessionStop()
{
	DPRINTF( "%s\n", __FUNCTION__ );
	if(m_channel)
	{
		libssh2_channel_free(m_channel);
		m_channel = NULL;
	}
	if(m_session)
	{
		libssh2_session_disconnect(m_session, "Normal Shutdown");
		libssh2_session_free(m_session);
		m_session = NULL;
	}
		
	if(m_socket)
	{
		close(m_socket);
		m_socket = 0;
	}
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
		DPRINTF( "%s\n",buffer);
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
	DPRINTF( "---------\n");
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