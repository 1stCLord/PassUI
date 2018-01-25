#include "passssh_native.h"
#include <cassert>
#ifdef WIN32
#include <winsock2.h>
#else
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define closesocket(x) close(x)
#endif
#include "passsshlog.h"

void destroy_session(ssh_session session)
{
	if(session)
	{
		ssh_disconnect(session);
		ssh_free(session);
	}
}

bool PassSSH::Init(string server, uint16_t port, string username, string passphrase, string privatekey, string publickey, AuthType authType)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	m_server = server;
	m_username = username;
	m_passphrase = passphrase;
	m_privatekey = privatekey;
	m_publickey = publickey;
	m_authType = authType;
	m_port = port;
	
	m_session = nullptr;
}
 
vector<string> PassSSH::GetPassIDs()
{
	SessionStart();
	const char * pass_cmd = "ls ~/.password-store/ -1\n";
	//libssh2_channel_write(m_channel,pass_cmd,strlen(pass_cmd));
	
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

string PassSSH::GetPass(string id, string gpg_password)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	SessionStart();
	string pass_cmd = "pass " + id + " \n";
	//libssh2_channel_write(m_channel,pass_cmd.c_str(),pass_cmd.size());
	ReadShell();
	string keychain_password = gpg_password + "\n";
	//libssh2_channel_write(m_channel,keychain_password.c_str(),keychain_password.size());
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
	m_session = std::unique_ptr<ssh_session, decltype(&destroy_session)>(ssh_new(),destroy_session);

	int verbosity = SSH_LOG_NOLOG;	
	
	ssh_options_set(m_session.get(), SSH_OPTIONS_HOST, m_server.c_str());
	ssh_options_set(m_session.get(), SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
	ssh_options_set(m_session.get(), SSH_OPTIONS_PORT, &m_port);
	
	if(ssh_connect(m_session.get()) != SSH_OK)
	{
		SessionStop();
		return;
	}
	
	static_assert(false, "get the key & check it");
	const ssh_key key;
	ssh_get_publickey_hash(key, SSH_PUBLICKEY_HASH_SHA1, );
	
	static_assert(false, "authenticate");
}

void PassSSH::SessionStop()
{
	m_session.reset();
}

void PassSSH::ShellStart()
{
	static_assert(false, "init channel");
	//libssh2_channel_request_pty(m_channel, "vanilla");
	//libssh2_channel_shell(m_channel);
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
		//memset(buffer,0,51);
		size_t read_amount;// = libssh2_channel_read(m_channel, buffer, 50);
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

