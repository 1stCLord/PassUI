#pragma once
#include <string>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/conf.h>

using namespace std;

class Encryptor
{
public:
	Encryptor(const string &privateKey, const string &passphrase);
	
	string Encrypt(const string &raw) const;
	
private:
	RSA *m_rsa;
};