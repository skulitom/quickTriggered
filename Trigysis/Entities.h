#ifndef Entities_H
#define Entities_H

#include "GUIBorder.h"

#define NUM_WIDTH 9
#define NUM_HEIGHT NUM_WIDTH

#define CELL_WIDTH 60
#define SIZE 270

#define BORDER_WIDTH 16
#define BORDER_COLOR XMFLOAT3(0,0.8,0.2)

class Entities{

public:
	Entities(BasicInterface* super);
	~Entities();

	void destroyBorders();
	inline bool checkSpawn(){ return spawned; };

	void spawnBordersAt(Vector2d pos);

protected:
private:

	//- border highlight
	std::vector<GUIBorder* > *borders;
	GUIBorder* border;
	BasicInterface* super;
	bool spawned;
	//
	

};

#endif