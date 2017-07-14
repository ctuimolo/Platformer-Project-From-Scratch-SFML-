#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

#include "SFML/Graphics.hpp"

class Player: public GameObject {

private:
	// SFML Render window
	sf::RenderWindow* render_window;

	// Player texture and sprite
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f sprite_dimensions;
	sf::Vector2f init_scale = { 2, 2 };

	// Player collision box
	sf::Vector2f hitbox_size   = { 10, 20 };
	sf::Vector2f hitbox_offset = { 11, 12 };
	sf::FloatRect hitbox;
	sf::RectangleShape hitbox_d;

	// Collision vectors
	std::vector<sf::FloatRect*>* collision_rects; 

	// Physics updation
	float xpos = 0; 
	float ypos = 0;
	float x_speed = 0;
	float y_speed = 0;

	float fall_acceleration;
	float max_fallspeed;

	bool floor_contact;

public:
	Player(sf::RenderWindow&);
	~Player();

	void update();
	void setSpeed(float x, float y);
	void setPosition(float x, float y);
	void gravity(float);
	void updateMove();
	void setCollisionRects(std::vector<sf::FloatRect*>& room_collision_rects);
};

#endif