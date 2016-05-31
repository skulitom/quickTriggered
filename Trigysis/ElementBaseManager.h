#ifndef ELEMENT_BASE_MANAGER_H
#define ELEMENT_BASE_MANAGER_H

#include "Element.h"
//#include "LogicalElement.h"

namespace EManager
{

	static void FindAndLoad(ElementsMLand* ptrToMLand, std::string& sFinder)
	{

		//RegisterElement(LogicalElement, ptrToMLand, sFinder);

	}

	static void LoadMaster(ElementsMLand* ptrToMLand)
	{

		if (!ptrToMLand->GetIsLoadMode())
			return;

		//ptrToMLand->OpenSBuffer();
		//ptrToMLand->GetSaveOBuffer();
		std::string Command;
		ptrToMLand->GetFManager()->Open(FM_FILE_READ);

		while (!ptrToMLand->GetFManager()->GetFILE().eof())
		{

			if (ptrToMLand->GetFManager()->GetStringFromFile() == "NewEl")
			{

				FindAndLoad(ptrToMLand, ptrToMLand->GetFManager()->GetStringFromFile());

			}

		}

		ptrToMLand->SetIsLoadMode(false);

		ptrToMLand->GetFManager()->Close();

	}

}

#endif // !ELEMENT_BASE_MANAGER_H
