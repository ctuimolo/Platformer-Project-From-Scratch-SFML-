#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
private:
public:
	GameObject();
	virtual void update();
	virtual void draw_object();
	virtual ~GameObject();
};

#endif