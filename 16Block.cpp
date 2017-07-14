#include "16Block.h"

#include "16Block.h"

BlockSixteen::BlockSixteen(sf::RenderWindow& source_render_window) {

	render_window = &source_render_window;
	texture.loadFromFile("block_16.png");
	sprite.setTexture(texture);
	sprite.setScale(init_scale);
	sprite_dimensions.x = init_scale.x * texture.getSize().x;
	sprite_dimensions.y = init_scale.y * texture.getSize().y;
}

void BlockSixteen::update() {

	render_window->draw(sprite);
}

BlockSixteen::~BlockSixteen() {

}