#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include "D3DAPP.h"

namespace StringHelp
{

	static INT ASCIIToINT(std::string& str)
	{

		INT Number = 0;
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

}

#endif //STRINGHELPER_H