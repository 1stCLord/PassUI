#include "encryptor.h"
#include "passsshlog.h"

Encryptor::Encryptor(const string &privateKey, const string &passphrase)
{
	DPRINTF( "%s\n", __FUNCTION__ );
	OPENSSL_load_builtin_modules();
	
	DPRINTF("%s\n",privateKey.c_str());

	BIO *biomemkey = BIO_new_mem_buf((void *)privateKey.data(), privateKey.size());
	EVP_PKEY *pkey = PEM_read_bio_PrivateKey(biomemkey,NULL,NULL, (void *)passphrase.c_str());
	m_rsa=NULL;
	if (pkey != NULL)
		m_rsa = EVP_PKEY_get1_RSA(pkey);
	EVP_PKEY_free(pkey);
	BIO_set_close(biomemkey, BIO_NOCLOSE);
	BIO_free(biomemkey);
	
	//string publicKey(512,'*');
	//BIO *biomempubkey = BIO_new_mem_buf((void *)publicKey.data(), publicKey.size());
	unsigned char *publicKey = NULL;
	i2d_RSAPublicKey(m_rsa, &publicKey);
	
	DPRINTF("%s\n",publicKey);
	//DPRINTF("%s\n",publicKey.c_str());
}

string Encryptor::Encrypt(const string &raw) const
{
	DPRINTF( "%s\n", __FUNCTION__ );
	if(m_rsa)
	{
		DPRINTF( "encrypting\n" );
		//TODO
	}
    return "";
}