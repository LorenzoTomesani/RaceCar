#pragma once
#include <curses.h>
#include "Player.hpp"
#include "Object.hpp"

class Collision{
private:
	Player *p1;
	Object *obj1;

public:
	Collision(Object *o, Player *p);
	int checkCollisionPlayerWall(int max_width, int max_height, int input_player);
	int checkCollisionPlayerObj(int input_player);
	void checkTypeCollision(int object_code);
};
