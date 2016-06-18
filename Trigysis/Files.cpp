#include "Files.h"

FileManager::FileManager(){}

FileManager::FileManager(std::string& fileName)
{

	this->FileName = fileName;

}

FileManager::~FileManager()
{

	this->Close();

}

void FileManager::Open(std::string& fileName, char FM_FILE_READ_OR_WRITE)
{

	if (FM_FILE_READ_OR_WRITE == FM_FILE_READ)
		this->FILE.open(fileName);
	else
		this->FILE.open(fileName);



}

void FileManager::Open(char FM_FILE_READ_OR_WRITE)
{

	FileManager::Open(this->FileName, FM_FILE_READ_OR_WRITE);
	// TODO exception when no FileName
	
}

void FileManager::Close()
{

	this->FILE.close();

}

std::string& FileManager::GetStringFromFile()
{

	std::getline(this->FILE, this->CString);
	return this->CString;

}

int FileManager::FindString(std::string findName){
	this->FILE.seekg(0);
	int lineNumber = 0;
	
	while (!this->FILE.eof()){
		std::getline(this->FILE, this->CString);
		if (this->CString==findName){
			break;
		}
		lineNumber++;
	}
	if (this->CString != findName){
		lineNumber = -1;
	}
	this->FILE.seekg(0);
	return lineNumber;

}

int FileManager::getIntFromLine(int lineNum){
	this->FILE.seekg(lineNum);
	int num = GetINTFromFile();
	this->FILE.seekg(0);
	return num;
}

bool FileManager::GetBoolFromString()
{

	FileManager::GetStringFromFile();

	if (this->CString == "True" || this->CString == "true")
		return true;
	else if (this->CString == "False" || this->CString == "false")
		return false;

}

int FileManager::GetINTFromFile()
{

	FileManager::GetStringFromFile();
	if (StringHelp::ASCIIToINT(this->CString) == 31)
		this->CString = this->CString;
	return StringHelp::ASCIIToINT(this->CString);

}