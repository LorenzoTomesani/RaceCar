#include "Level.hpp"

#define INFO_COLOR 1
#define END_COLOR 2
#define LENGTH_INFO 8


Level::Level(Player *p){
	p1 = p;
	init_color(COLOR_CYAN, 300, 400, 1000);
	init_color(COLOR_RED, 1000, 100, 100);
	init_pair(INFO_COLOR, COLOR_CYAN, COLOR_BLACK);
	init_pair(END_COLOR, COLOR_RED, COLOR_BLACK);
}

void Level::printInfo(int max_width, int max_height){
	char tmp_Level[10];
	char tmp_score[10];
	attron(COLOR_PAIR(INFO_COLOR));
	sprintf (tmp_Level, "%d", p1->getLevel());
	sprintf (tmp_score, "%d", p1->getScore());
	strcat(current_level_player, tmp_Level);
	strcat (current_score_player, tmp_score);
	x_box = ((max_width/6)*5) - 3;
	y_box = (max_height - 2)/2;
	wmove(stdscr, y_box, x_box);
	wprintw(stdscr, current_level_player);
	wmove(stdscr, y_box + 2, x_box);
	wprintw(stdscr, current_score_player);
	refresh();
	attroff(COLOR_PAIR(INFO_COLOR));
}

/* sia per updateScore che per updateLevel, vengono stampati molteplici caratteri vuoti dopo la stringa SCORE:/LEVEL:  e non stampo tutta la stringa */
void Level::updateScore(){
	attron(COLOR_PAIR(INFO_COLOR));
	char tmp_score[10];
	sprintf (tmp_score, "%d", p1->getScore());
	for(int i = 0; i < 4; i++){
		wmove(stdscr, y_box + 2, x_box + LENGTH_INFO + i);
		wprintw(stdscr, " ");
	}
	wmove(stdscr, y_box + 2, x_box + LENGTH_INFO);
	wprintw(stdscr, tmp_score);
	refresh();
	attroff(COLOR_PAIR(INFO_COLOR));
}

void Level::updateLevel(){
	char tmp_Level[10];
	sprintf(tmp_Level, "%d", p1->getLevel());
	for(int i = 0; i < 3; i++){
		wmove(stdscr, y_box, x_box + LENGTH_INFO + i);
		wprintw(stdscr, " ");
	}
	attron(COLOR_PAIR(INFO_COLOR));
	wmove(stdscr, y_box, x_box  + LENGTH_INFO);
	wprintw(stdscr, tmp_Level);
	refresh();
	attroff(COLOR_PAIR(INFO_COLOR));
}

void Level::checkScorePerLevel(){
	// se lo score è minore di Level*10, diminuisco
	if(p1->getScore() < p1->getLevel()*10 && p1->getLevel() > 1) {
		p1->decreaseLevel();
		updateLevel();
	} else if (p1->getScore() >= (p1->getLevel()+1)*10){
		// se lo score è maggiore di (Level+1)*10, diminuisco
		p1->increaseLevel();
		updateLevel();
	}
}

// gameover
void Level::exitMatch(int max_width, int max_height){
	attron(COLOR_PAIR(END_COLOR));
	wmove(stdscr, max_height/2 - 3, max_width/2 - 9/2);
	wprintw(stdscr,"GAME OVER");
	wmove(stdscr, max_height/2 + 2 - 3, max_width/2 - 10);
	wprintw(stdscr, "press Q to exit the game");
	attroff(COLOR_PAIR(END_COLOR));
	refresh();
}
