#ifndef FILES_H
#define FILES_H

#include <fstream>
#include <sstream>

#include <Windows.h>
#include <Shlwapi.h>

#include <vector>
#include <string>

#include "StringHelper.h"

#define FM_FILE_READ 0
#define FM_FILE_WRITE 1

class FileManager
{

public:

	FileManager();
	FileManager(std::string& fileName);

	~FileManager();

	void Open(std::string& fileName, char FM_FILE_READ_OR_WRITE = 0);
	void Open(char FM_FILE_READ_OR_WRITE = 0);
	void Close();
	void writeToFileAt(int num, int loc);
	void writeToFileAt(std::string& name, int loc);

	std::string& GetStringFromFile();
	int FindString(std::string findName);
	int getIntFromLine(int lineNum);
	int getLineQuo();

	bool GetBoolFromString();
	int GetINTFromFile();

	inline std::string& GetCString(){ return this->CString; }
	inline char GetCSymbol() { return this->CSymbol; }
	inline unsigned __int64 GetCurrentSIndex() { return this->CurrentSIndex; }
	inline void writeToFile(int num){ this->FILE << num << std::endl; }
	inline void writeToFile(std::string& name){ this->FILE << name << std::endl; }

	std::fstream& GetFILE() { return this->FILE; }

private:

	std::fstream FILE;
	std::string FileName;

	unsigned __int64 CurrentSIndex;
	std::string CString;
	char CSymbol;

};

namespace FileHelp
{

	static std::vector<std::string> FindFiles(std::string catalogName)
	{

		WIN32_FIND_DATAA LFD;

		HANDLE hFind;

		hFind = FindFirstFile(catalogName.c_str(), &LFD);

		std::vector<std::string> Files;

		if (hFind != INVALID_HANDLE_VALUE)
		{

			do
			{

				if (LFD.cFileName != "." && LFD.cFileName != "..")
				{

					Files.push_back(LFD.cFileName);

				}

			} while (FindNextFile(hFind, &LFD));

			FindClose(hFind);

		}
		else
		{

			std::cout << "Error!" << std::endl;

		}

		return Files;

	}
}
//
//	static void GetStringFromFile(std::ifstream& fin, std::string& rLine)
//	{
//
//		std::getline(fin, rLine);
//
//	}
//
//	static bool GetBoolFromString(std::ifstream& fin, std::string& rLine = std::string())
//	{
//
//		std::getline(fin, rLine);
//
//		if (rLine == "True" || rLine == "true")
//			return true;
//		else if (rLine == "False" || rLine == "false")
//			return false;
//
//	}
//
//	static INT GetINTFromFile(std::ifstream& fin, std::string& rLine = std::string())
//	{
//		std::getline(fin, rLine);
//		return StringHelp::ASCIIToINT(rLine);
//	}
//
//}//namespace FileHelp

#endif //FILES_H