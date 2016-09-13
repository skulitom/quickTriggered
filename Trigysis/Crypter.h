#ifndef Crypter_H
#define Crypter_H

#include "Crypto\filters.h"
#include "crypto\files.h"
#include "crypto\hex.h"
#include "crypto\default.h"
#include "Files.h"

class Crypter {
public:
	Crypter();
	~Crypter();
	std::string openFile();


protected:
private:
	void encrypt();
	void decript();
	std::string fileName;
	std::string password;
	std::string encrypted, decrypted;
	FileManager *fileManager;


};

#endif