#pragma once
#include <vector>
#include <string>
#include <cstdint>
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
    bool Init(string server, uint16_t port, string username, string passphrase, string privatekey, string publickey, AuthType authType);

    //Fetch
    vector<string> GetPassIDs();
    string GetPass(string id, string gpg_password);

    //Set
    void InsertPass(string id, string pass);
    void GeneratePass(string id, bool withSymbols, int length);
	
private:
	AuthType m_authType;
	string m_server;
	uint16_t m_port;
	string m_username;
	string m_passphrase;
	string m_privatekey;
	string m_publickey;
		
	int m_socket;
	
	void SessionStart();
	void SessionStop();
	void ShellStart();
	vector<string> ReadShell();
};