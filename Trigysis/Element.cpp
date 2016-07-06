#include "Element.h"

//////////////////////////////////////////////////////////
//**Element
//////////////////////////////////////////////////////////
Element::Element(BasicInterface* super)
	: ElementInterface(super->GetElementBase())
{
	DeclareElementName(Element, this->EName);
	this->Super = super;
}

void Element::Spawn(Vector2d& position, short indexOfVPort)
{

	ElementInterface::Spawn(position, indexOfVPort);
	this->PMLand->AddNewElement(this);

}
