#pragma once

using namespace std;

class Encryptor
{
public:
	Encryptor(const string &privateKey, const string &passphrase)
	
	string Encrypt(const string &raw) const;
	
private:
	
}