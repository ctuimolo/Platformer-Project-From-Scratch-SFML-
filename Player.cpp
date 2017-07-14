#include "Player.h"
#include <iostream>

Player::Player(sf::RenderWindow& source_render_window) {
	
	render_window   = &source_render_window;

	texture.loadFromFile("meko.png");
	sprite.setTexture(texture);
	sprite.setScale(init_scale);
	sprite_dimensions.x = init_scale.x * texture.getSize().x;
	sprite_dimensions.y = init_scale.y * texture.getSize().y;

	sprite.setOrigin(hitbox_offset.x, hitbox_offset.y);

	hitbox_size.x *= init_scale.x;
	hitbox_size.y *= init_scale.y;

	hitbox = sf::FloatRect(0, 0, hitbox_size.x, hitbox_size.y);
	hitbox_d.setPosition(hitbox.left, hitbox.top);
	hitbox_d.setSize(sf::Vector2f(hitbox.width, hitbox.height));
	hitbox_d.setFillColor(sf::Color(220,150,0,180));

	fall_acceleration = 0.5;
	y_speed = 0;
	y_speed = 0;
	max_fallspeed = 10;

}

void Player::setCollisionRects(std::vector<sf::FloatRect*>& room_collision_rects) {
	collision_rects = &room_collision_rects;
}

void Player::setPosition(float new_x, float new_y) {
	sprite.setPosition(new_x, new_y);
}

void Player::setSpeed(float x_change, float y_change) {
	x_speed = x_change;
	y_speed = y_change;
}

void Player::gravity(float down_acceleration) {
	y_speed += down_acceleration;
}

void Player::updateMove() {

	std::cout << "X: " << hitbox.left << std::endl;
	std::cout << "Y: " << hitbox.top << std::endl;

	if (x_speed > 0 || y_speed > 0) {

		for (sf::FloatRect* collision_rect : *collision_rects) {

			hitbox.left += x_speed;
			if (hitbox.intersects(*collision_rect)) {
				hitbox.left -= x_speed;
				std::cout << "X Collision: " << hitbox.left + x_speed << std::endl;
				x_speed = 0;
			}

			hitbox.top += y_speed;
			if (hitbox.intersects(*collision_rect)) {
				hitbox.top -= y_speed;
				floor_contact = true;
				std::cout << "Y Collision: " << hitbox.top + y_speed << std::endl;
				y_speed = 0;
			}
		}

		setPosition(xpos + x_speed, ypos + y_speed);
		xpos = sprite.getPosition().x;
		ypos = sprite.getPosition().y;
		hitbox.left = xpos;
		hitbox.top  = ypos;
		hitbox_d.setPosition(hitbox.left, hitbox.top);
	}

	std::cout << std::endl;

}

void Player::update() {

	xpos = sprite.getPosition().x;
	ypos = sprite.getPosition().y;

	if (hitbox.top + hitbox.height + y_speed < render_window->getSize().y ) {
		if (y_speed < max_fallspeed)
			gravity(fall_acceleration);

	} else {
		y_speed = 0;
		sprite.setPosition(xpos, render_window->getSize().y - hitbox.height);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		x_speed = -2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		x_speed = 2;
	}
	else {
		x_speed = 0;
	}


	updateMove();


	// Apply transformations to the display window
	render_window->draw(sprite);
	render_window->draw(hitbox_d);
}

Player::~Player() {

}