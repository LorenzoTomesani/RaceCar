#pragma once
#include <curses.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include "Player.hpp"
#include "object_char.hpp"

using namespace std;

struct desc_object{
	int x;
	int y;
	const char *char_obj;
    struct desc_object *next;
};

typedef desc_object *pt_obj;

class Object{
private:
	const char *object_rappresentation[6];
	pt_obj head;
	int max_h;
	int max_w;
	Player *p1;
	int checkMalusBonus(pt_obj tmp);
	void deleteObject(pt_obj &tmp, pt_obj &pre_tmp);
	void cleanLastObjectPosition(desc_object tmp);
	void fillListObject();

public:
	Object(Player *p,int max_width, int max_height);
	void addRowObjects();
	void moveObjectsList();
	int checkCollisionPlayer(int x,int y,int input_player);
	void drawObjects();
	int chooseObjectChar();
	void deleteList();
};
