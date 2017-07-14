#ifndef ROOM_H
#define ROOM_H

#include "GameObject.h"

class Room: public GameObject {
private:
public:
	Room();
	virtual void update();
	virtual ~Room();
};

#endif