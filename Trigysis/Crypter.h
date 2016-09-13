#ifndef Crypter_H
#define Crypter_H

#include "crypto\filters.h"
#include "crypto\files.h"
#include "crypto\hex.h"
#include "crypto\default.h"
#include "Files.h"
#include <string.h>


class Crypter {
public:
	Crypter();
	~Crypter();
	std::string readFile();
	void writeToFile(std::string& toEncrypt);


protected:
private:
	void encrypt(std::string& toEncrypt);
	void decrypt();
	std::string fileName;
	std::string password;
	std::string encrypted, decrypted;
	FileManager *fileManager;


};

#endif