#include "Crypter.h"
/**
	The Crypter class allows to encrypt our save files
	This wouldn't have been possible without Crypto++ ---> https://www.cryptopp.com

	The following class uses DefaultEncryptorWithMAC and DefaultDecryptorWithMAC
	which in tern uses 2-key Triple DES as the default encryptor and SHA1 as default hash
*/

using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::FileSource;
using CryptoPP::FileSink;
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
using CryptoPP::DefaultDecryptorWithMAC;
using CryptoPP::DefaultEncryptorWithMAC;


Crypter::Crypter()
{
	// random password
	this->password = "pvxWty782qw";
	this->fileName = "./saves.txt";
	fileManager = new FileManager();
	fileManager->Open(fileName, 1);
}

std::string Crypter::readFile()
{
	fileManager->Close();
	// open file for reading
	fileManager->Open(fileName, 0);
	encrypted = fileManager->GetStringFromFile(); 
	this->decrypted = "";
	// if file empty return empty string
	if (encrypted == "")
	{
		return decrypted;
	}
	decrypt();
	this->fileManager->clearFile();
	// open file to write
	this->fileManager->Open(fileName, 1);
	writeToFile(decrypted);
	return decrypted;
}

void Crypter::writeToFile(std::string& toEncrypt)
{
	// remove previus encrypted values
	this->encrypted = "";
	// get new values and write to file
	encrypt(toEncrypt);
	this->fileManager->writeToFile(encrypted);
	// erase encrypted value
	this->encrypted = "";
}

// decrypts a string
void Crypter::encrypt(std::string& toEncrypt)
{
	StringSource ss1(toEncrypt, true,
		new DefaultEncryptorWithMAC(
			(byte*)this->password.data(), this->password.size(),
				new HexEncoder(
				// encrypted result stored in encrypted
				new StringSink(this->encrypted)
			)
		)
	);

}

// encrypts a string
void Crypter::decrypt()
{
	StringSource ss1(this->encrypted, true,
		new HexDecoder(
			new DefaultDecryptorWithMAC(
				(byte*)this->password.data(), this->password.size(),
				new StringSink(this->decrypted)
			)
		)
	);

}

Crypter::~Crypter()
{
	delete this->fileManager;
}