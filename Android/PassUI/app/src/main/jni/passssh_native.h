#pragma once
#include <vector>
#include <string>
#include "sshlib2/include/libssh2.h"
using namespace std;

enum AuthType
{
	AUTH_TYPE_PASSWORD,
	AUTH_TYPE_PRIVATE_KEY
};

class PassSSH
{
public:
    //SSH details to use
    bool Init(string server, uint16_t port, string username, wstring passphrase, AuthType authType);

    //Fetch
    vector<string> GetPassIDs();
    string GetPass(string id);

    //Set
    void InsertPass(string id, string pass);
    void GeneratePass(string id, bool withSymbols, int length);
	
private:
	AuthType m_authType;
	string m_server;
	uint16_t m_port;
	string m_username;
	wstring m_passphrase;
	
	int m_socket;
	LIBSSH2_CHANNEL *m_channel;
	LIBSSH2_SESSION *m_session;
	
	void SessionStart();
	void SessionStop();
	void ShellStart();
	vector<string> ReadShell();
	
	template<typename T>
	basic_string<T> password();
};