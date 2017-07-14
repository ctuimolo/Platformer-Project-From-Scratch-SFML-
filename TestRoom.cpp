#include "TestRoom.h"

/*================================================*/
/*     SFML RenderWindow dependant constructor    */
/*================================================*/

/*
 *	Similar to all GameObjects right now, it must be initalized with
 *	a reference to the &RenderWindow which is drawn to in main()
 */

TestRoom::TestRoom(sf::RenderWindow& render_window_source, std::vector<GameObject*>& active_objects_list) {

	/*==========================================*/
	/*     Load XML and SFML Render Window&     */
	/*==========================================*/

	// Reference to main SFML render window
	render_window  = &render_window_source;
	active_objects = &active_objects_list;

	map = new XMLMap("test_level.tmx");
	map->generateSpriteMap(map_tiles);
	map->objectlist(rect_walls, "walls");

	meko = new Player(render_window_source);
	meko->setCollisionRects(rect_walls);
	meko->setPosition(40, 150);
}

TestRoom::~TestRoom() {
	delete map;
	delete meko;
	for (sf::Sprite* map_tile : map_tiles) {
		delete map_tile;
	}

	for (sf::FloatRect* rect_wall : rect_walls) {
		delete rect_wall;
	}
}

void TestRoom::pushbackPlayer() {
	active_objects->push_back(meko);
}

void TestRoom::update() {

	for (sf::Sprite* map_tile : map_tiles) {
		render_window->draw(*map_tile);
	}

	for (sf::FloatRect* rect_wall : rect_walls) {
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(rect_wall->width, rect_wall->height));
		rect.setPosition(rect_wall->left, rect_wall->top);
		rect.setFillColor(sf::Color(0,0,255,80));
		render_window->draw(rect);
	}
}