#ifndef TESTROOM_H
#define TESTROOM_H

#include "Room.h"
#include "Map.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "tinyxml\tinyxml.h"
#include "tinyxml\tinystr.h"
#include <iostream>

class TestRoom : public Room {
private:

	sf::RenderWindow* render_window;
	std::vector<GameObject*>* active_objects;

	XMLMap* map;
	Player* meko;
	std::vector<sf::Sprite*> map_tiles;
	std::vector<sf::FloatRect*> rect_walls;

public:

	TestRoom(sf::RenderWindow&, std::vector<GameObject*>& active_objects = std::vector<GameObject*>());
	~TestRoom();

	void update();
	void pushbackPlayer();
};

#endif