#include <iostream>

#include <SFML/Graphics.hpp>

#include "tinyxml\tinyxml.h"
#include "tinyxml\tinystr.h"

#include "GameObject.h"
#include "Room.h"
#include "Map.h"
#include "TestRoom.h"

int main() {

	// SFML window object initializing
	sf::RenderWindow window(sf::VideoMode(512, 384), "SFML Test");
	window.setFramerateLimit(60);
	sf::Event event_listener;

	sf::View view(sf::Vector2f(256, 192), sf::Vector2f(512, 384));
	window.setView(view);
	
	//////////////////////////


	std::vector<GameObject*> active_objects;

	TestRoom* test_room = new TestRoom(window, active_objects);
	active_objects.push_back(test_room);
	test_room->pushbackPlayer();


	while (window.isOpen()) {

		// Poll event and close SFML window on OS app close
		while (window.pollEvent(event_listener))
			if (event_listener.type == sf::Event::Closed)
				window.close();

		window.clear();

		for (std::vector<GameObject*>::size_type i = 0; i < active_objects.size(); i++) {
			active_objects[i]->update();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			view.move(2, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			view.move(-2, 0);
		}

		window.setView(view);
		window.display();
	}
}