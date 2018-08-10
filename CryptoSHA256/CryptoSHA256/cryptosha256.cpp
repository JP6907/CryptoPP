#include "cryptosha256.h"

#include "sha.h"
#include "secblock.h"
#include "modes.h"
#include "hex.h"

#pragma comment(lib, "cryptlib.lib")

using namespace std;
using namespace CryptoPP;

CryptoSHA256::CryptoSHA256()
{
}

CryptoSHA256::~CryptoSHA256()
{
}

string CryptoSHA256::CalculateDigest(std::string data)
{
	byte const* pbData = (byte*)data.data();
	unsigned int nDataLen = data.size();
	byte abDigest[CryptoPP::SHA256::DIGESTSIZE];

	CryptoPP::SHA256().CalculateDigest(abDigest, pbData, nDataLen);

	return string((char*)abDigest);
}

bool CryptoSHA256::VerifyDigest(std::string Digest, std::string Message) {
	bool Result;
	byte byDigest[CryptoPP::SHA256::DIGESTSIZE];

	strcpy((char*)byDigest, Digest.data());

	Result = CryptoPP::SHA256().VerifyDigest(byDigest, (const byte *)Message.c_str(), Message.size());

	return Result;
}
