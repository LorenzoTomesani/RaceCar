#pragma once
#include <curses.h>
#include <string.h>
#include <stdlib.h>

class Player{
private:
  const char *player_char = "V\0";
  int x;
  int y;
  int original_x;
  int original_y;
  int score;
  int level;
  int immunity;

public:
  Player();
  void drawPlayer(int max_width, int max_height);
  void changeScore(int point_to_add);
  void movePlayer(int input_player);
  void decreaseLevel();
  void increaseLevel();
  int getScore();
  int getLevel();
  int getx();
  int gety();
  void setImmunity();
  void decreaseImmunity();
  int getImmunity();
  void setOriginalPosition();
  void deletePlayer();
  void exitGame();
};
