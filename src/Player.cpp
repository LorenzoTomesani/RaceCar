#include "Player.hpp"

#define COLOR_PLAYER 3
#define ORIGINAL_IMMUNITY 2

Player::Player(){
  score = 10;
  level = 1;
  immunity = 0;
  init_pair(COLOR_PLAYER, COLOR_YELLOW , COLOR_BLACK);
}

void Player::drawPlayer(int max_width, int max_height){
  attron(COLOR_PAIR(COLOR_PLAYER));
  //cerco di trovare il centro dell'area di gioco
  original_x = (max_width/3);
  original_y = (max_height/10)*9;
  x = original_x;
  y = original_y;
  wmove(stdscr,y, x);
  wprintw(stdscr, player_char);
  refresh();
  attroff(COLOR_PAIR(COLOR_PLAYER));
}

int Player::getScore(){
  return score;
}

int Player::getLevel(){
  return level;
}

void Player::changeScore(int point_to_add){
  if(point_to_add < 0 && score + point_to_add <= 0){
    score = 0;
  } else {
    score = score + point_to_add;
  }
}

void Player::movePlayer(int input_player){
  attron(COLOR_PAIR(COLOR_PLAYER));
  switch(input_player){
    case 119: //w
    wmove(stdscr,y,x);
    wprintw(stdscr, " ");
    y = y - 1;
    wmove(stdscr,y,x);
    wprintw(stdscr, player_char);
    refresh();
    break;
    case 97:   //a
    wmove(stdscr,y,x);
    wprintw(stdscr, " ");
    refresh();
    x = x - 1;
    wmove(stdscr,y,x);
    wprintw(stdscr, player_char);
    refresh();
    break;
    case 115:  //s
    wmove(stdscr,y, x);
    wprintw(stdscr, " ");
    refresh();
    y = y + 1;
    wmove(stdscr,y,  x);
    wprintw(stdscr, player_char);
    refresh();
    break;
    case 100:  //d
    wmove(stdscr, y,  x);
    wprintw(stdscr, " ");
    refresh();
    x = x + 1;
    wmove(stdscr,y,  x);
    wprintw(stdscr, player_char);
    refresh();
    break;
  }
  attroff(COLOR_PAIR(COLOR_PLAYER));
}

void Player::setOriginalPosition(){
  attron(COLOR_PAIR(COLOR_PLAYER));
  wmove(stdscr,y,  x);
  wprintw(stdscr, " ");
  x = original_x;
  y = original_y;
  wmove(stdscr,y,  x);
  wprintw(stdscr, player_char);
  refresh();
  attroff(COLOR_PAIR(COLOR_PLAYER));
}

int Player::getx(){
  return x;
}

int Player::gety(){
  return y;
}

void Player:: decreaseLevel(){
  level--;
}

void Player::increaseLevel(){
  level++;
}

void Player::setImmunity(){
  immunity = ORIGINAL_IMMUNITY;
}

void Player::decreaseImmunity(){
  immunity--;
}

int Player::getImmunity(){
  return immunity;
}

void Player::exitGame(){
  endwin();
  exit(1);
}

void Player::deletePlayer(){
  player_char = "\0";
  setOriginalPosition();
}
