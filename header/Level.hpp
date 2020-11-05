#include <curses.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "Player.hpp"


class Level{
private:
  char current_level_player[100] = "LEVEL : ";
  char current_score_player[100] = "SCORE : ";
  int x_box;
  int y_box;
  Player *p1;

public:
  Level(Player *p);
  void printInfo(int max_width, int max_height);
  void updateScore();
  void updateLevel();
  void checkScorePerLevel();
  void exitMatch(int max_width, int max_height);
};
