#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2d.h"

class Camera
{

public:

	Camera() { this->Position = Vector2d(0, 0); }

	void SetPosition(Vector2d& position) { this->PPosition = this->Position; this->Position = position; }
	Vector2d& GetPosition() { return this->Position; }
	Vector2d& GetPPosition() { return this->PPosition; }
	Vector2d& GetDeltaPosition() { return this->Position - this->PPosition; }


private:

	Vector2d Position;
	Vector2d PPosition;

};

#endif //!CAMERA_H