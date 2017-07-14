#ifndef SIXTEENBLOCK_H
#define SIXTEENBLOCK_H

#include "GameObject.h"

#include "SFML/Graphics.hpp"

class BlockSixteen: public GameObject {

private:
	// SFML Render window
	sf::RenderWindow* render_window;

	// Player texture and sprite
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f sprite_dimensions;
	sf::Vector2f init_scale = { 1, 1 };

public:
	void update();
	BlockSixteen(sf::RenderWindow&);
	~BlockSixteen();

};
 
#endif