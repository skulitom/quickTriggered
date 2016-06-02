#include "Element.h"

//////////////////////////////////////////////////////////
//**Element
//////////////////////////////////////////////////////////
Element::Element(BasicInterface* super)
	: ElementInterface(super->GetElementBase())
{
	DeclareElementName(Element, this->EName);
	this->Super = super;
	this->PMLand->AddNewElement(this);
}
