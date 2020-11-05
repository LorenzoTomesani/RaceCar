#pragma once
#include <curses.h>
#include <unistd.h>
#include <string.h>
#include "Object.hpp"
#include "Player.hpp"
#include "Collision.hpp"
#include "Level.hpp"

class Map{
private:
	int max_width;
	int max_height;
	bool in_game;
	Player *player_handler;
	Level *levels_handler;
	Collision *collisions_handler;
	Object *objects_handler;
	void drawBorder();
	void initialMenu();
	void inGameController();
public:
	Map();
	void initWindow();
};
