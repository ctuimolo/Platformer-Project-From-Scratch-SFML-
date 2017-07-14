#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "tinyxml\tinyxml.h"
#include "tinyxml\tinystr.h"

struct Tileset {

	std::string name;
	int firstgid;
	int tilewidth;
	int tileheight;
	int tilecount;
	int columns;

	sf::Texture texture;
	int image_width;
	int image_height;

	Tileset(TiXmlElement* elem) :

		name(elem->Attribute("name")),
		firstgid(std::stoi(elem->Attribute("firstgid"))),
		tilewidth(std::stoi(elem->Attribute("tilewidth"))),
		tileheight(std::stoi(elem->Attribute("tileheight"))),
		tilecount(std::stoi(elem->Attribute("tilecount"))),
		columns(std::stoi(elem->Attribute("columns"))),

		image_width(std::stoi(elem->FirstChildElement("image")->Attribute("width"))),
		image_height(std::stoi(elem->FirstChildElement("image")->Attribute("height"))) {

			std::string texture_filename = elem->FirstChildElement("image")->Attribute("source");
			texture.loadFromFile(texture_filename);
		};
};

struct Tile {

	int gid;
	Tile(TiXmlElement* elem) :
		gid(std::stoi(elem->Attribute("gid"))) {};
};

struct Layer {

	std::string name;
	int width;
	int height;
	std::vector<Tile> tiles;

	Layer(TiXmlElement* elem) :

		name(elem->Attribute("name")),
		width(std::stoi(elem->Attribute("width"))),
		height(std::stoi(elem->Attribute("height"))) {

			elem = elem->FirstChildElement("data");
			if (elem != NULL)
				for (elem = elem->FirstChildElement("tile"); elem != NULL; elem = elem->NextSiblingElement("tile"))
					tiles.push_back(Tile(elem));
		};
};

struct Object {

	int id;
	std::string name;
	std::string type;
	int x;
	int y;
	int width;
	int height;

	Object(TiXmlElement* elem) :

		id(std::stoi(elem->Attribute("id"))),
		name((elem->Attribute("name") != NULL) ? elem->Attribute("name") : ""),
		type((elem->Attribute("type") != NULL) ? elem->Attribute("type") : ""),
		x(std::stoi(elem->Attribute("x"))),
		y(std::stoi(elem->Attribute("y"))),
		width(std::stoi(elem->Attribute("width"))),
		height(std::stoi(elem->Attribute("height"))) {};
};

struct Objectgroup {

	std::string name;
	std::vector<Object> objects;

	Objectgroup(TiXmlElement* elem) :

		name(elem->Attribute("name")) {
			for (elem = elem->FirstChildElement("object"); elem != NULL; elem = elem->NextSiblingElement("object")) {
				Object new_object(elem);
				objects.push_back(new_object);
			}
		};
};

class XMLMap {

private:
	TiXmlDocument xml_file;

	int width;
	int height;
	int tilewidth;
	int tileheight;

	std::vector<Tileset> tilesets;
	std::vector<Layer> layers;
	std::vector<Objectgroup> objectgroups;

public:
	XMLMap(const char* source_file);
	~XMLMap();

	void generateSpriteMap(std::vector<sf::Sprite*>&);
	void objectlist(std::vector<sf::FloatRect*>&, std::string);
};

#endif