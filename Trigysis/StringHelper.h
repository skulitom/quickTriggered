#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <stdlib.h>

namespace StringHelp
{

	static int ASCIIToINT(std::string& str)
	{

		int Number = 0;
		short sign = 1;

		for (int i = 0; i < str.size(); i++)
		{
			if (str.at(i) != '-')
				Number = Number * 10 + (int)str.at(i) - 48;
			else
				sign = -1;
		}

		return Number * sign;

	}

	static std::vector<std::string> DivideString(std::string& str, char* del)
	{

		std::vector<std::string> Words;

		int Index = -1;
		int PIndex = -1;

		do
		{

			PIndex = Index;
			Index = str.find(del, Index + 1);
			Words.push_back(str.substr(PIndex + 1, Index - PIndex - 1));

		} while (Index != -1);

		return Words;

	}

}

#endif //STRINGHELPER_H