#ifndef ELEMENT_H
#define ELEMENT_H

#include "BasicElement.h"
#include "BasicInterface.h"

class Element : public ElementInterface
{

public:
	Element(BasicInterface* super);

	virtual ~Element() {}

private:

	BasicInterface* Super;

};

#endif // !ELEMENT_H
