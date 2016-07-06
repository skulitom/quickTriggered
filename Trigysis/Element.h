#ifndef ELEMENT_H
#define ELEMENT_H

#include "BasicElement.h"
#include "BasicInterface.h"

class Element : public ElementInterface
{

public:
	Element(BasicInterface* super);

	virtual ~Element() {}

	virtual void Spawn(Vector2d& position, short indexOfVPort) override;

private:

	BasicInterface* Super;

};

#endif // !ELEMENT_H
