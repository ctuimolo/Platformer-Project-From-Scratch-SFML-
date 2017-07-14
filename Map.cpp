#include "Map.h"
#include <iostream>

XMLMap::XMLMap(const char* source_file) {

	// Load XML level map
	if (!xml_file.LoadFile(source_file))
		std::cerr << xml_file.ErrorDesc() << std::endl;

	/*======================================*/
	/*      Load map elements from XML      */
	/*======================================*/

	TiXmlElement* elem = xml_file.FirstChildElement("map");
	if (elem != NULL) {

		// General map elements
		width = std::stoi(elem->Attribute("width"));
		height = std::stoi(elem->Attribute("height"));
		tilewidth = std::stoi(elem->Attribute("tilewidth"));
	std::vector<Object> walls_objects;
		tileheight = std::stoi(elem->Attribute("tileheight"));

		for (elem = elem->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {

			// Load all Tileset elements
			if (std::strcmp(elem->Value(), "tileset") == 0) {
				Tileset new_tileset = Tileset(elem);
				tilesets.push_back(new_tileset);
			}

			// Load all layer elements
			else if (std::strcmp(elem->Value(), "layer") == 0) {
				Layer new_layer = Layer(elem);
				layers.push_back(new_layer);
			}

			// Load all objectgroup elements
			else if (std::strcmp(elem->Value(), "objectgroup") == 0) {
				Objectgroup new_objectgroup = Objectgroup(elem);
				objectgroups.push_back(new_objectgroup);
			}
		}
	// else there was an error loading (no 'map' element)
	}
	else {
		std::cerr << "Map loading error : " << source_file << std::endl;
	}
}

void XMLMap::objectlist(std::vector<sf::FloatRect*>& objects_list, std::string tag) {

	for (Objectgroup& objectgroup : objectgroups) {
		if (tag.compare(objectgroup.name) == 0) {
			for (Object& object : objectgroup.objects) {
				sf::FloatRect* new_rect_wall = new sf::FloatRect();
				new_rect_wall->top  = object.y;
				new_rect_wall->left = object.x;
				new_rect_wall->width  = object.width;
				new_rect_wall->height = object.height;
				objects_list.push_back(new_rect_wall);
			}
		}
	}
}

/*===============================================*/
/*    Parse XML doc for gid values to tilemap    */
/*    Load sprites into level map                */
/*===============================================*/

void XMLMap::generateSpriteMap(std::vector<sf::Sprite*>& sprite_map) {

	for (Layer& layer : layers) {
		int index = 0;
		for (Tile& tile : layer.tiles) {
			
			if (tile.gid > 0) {

				int map_x = (index % layer.width) * tilewidth;
				int map_y = (index / layer.width) * tileheight;

				Tileset* tileset = &tilesets.front();

				if (tilesets.size() > 1) {
					for (int i = 1; i < tilesets.size(); i++) {
						Tileset* next_tileset = &(tilesets)[i];
						if (tile.gid >= tileset->firstgid && tile.gid < next_tileset->firstgid) {
							break;
						}
						else {
							tileset = &(tilesets)[i];
						}
					}
				}

				int gid_value = tile.gid - tileset->firstgid;
				int gid_x = (gid_value % tileset->columns) * tileset->tilewidth;
				int gid_y = (gid_value / tileset->columns) * tileset->tileheight;

				sf::Sprite* tile_sprite = new sf::Sprite();
				tile_sprite->setTexture(tileset->texture);
				tile_sprite->setTextureRect(sf::IntRect(gid_x, gid_y, tileset->tilewidth, tileset->tileheight));
				tile_sprite->setPosition(sf::Vector2f(map_x, map_y));
				sprite_map.push_back(tile_sprite);
			}

			index++;
		}
	}	
}

XMLMap::~XMLMap() {
	xml_file.Clear();
}