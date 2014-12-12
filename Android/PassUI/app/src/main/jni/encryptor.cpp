#include "encryptor.h"
#include <openssl/pem.h>
#include <openssl/bio.h>

Encryptor::Encryptor(const string &privateKey, const string &passphrase)
{
	OPENSSL_load_builtin_modules();

	BIO *biomemkey = BIO_new_mem_buf(privateKey.data(), privateKey.size());
	EVP_PKEY *pkey = PEM_read_bio_PrivateKey(biomemkey,NULL,NULL, passphrase.c_str());
	RSA *rsa=NULL;
	if (pkey != NULL)
		rsa = EVP_PKEY_get1_RSA(pkey);
	EVP_PKEY_free(pkey);
	BIO_set_close(mem, BIO_NOCLOSE);
	BIO_free(mem);
}