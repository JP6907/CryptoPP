#ifndef _Cryptosha256
#define _Cryptosha256

#include <vector>
#include <string>

class CryptoSHA256 {
public:

	CryptoSHA256();
	~CryptoSHA256();

	static std::string CalculateSHA256(std::string Message);
	static bool VerifySHA256(std::string Digest, std::string Message);

};
#endif