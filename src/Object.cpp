#include "Object.hpp"

#define TIMER 100000
#define MALUS 4
#define BONUS 5
#define STAR  6
#define EMPTY_COLOR 7


Object::Object(Player *p, int max_width, int max_height){
	srand (time(NULL));
	head = NULL;
	max_w = (max_width/3)*2 - 1;
	max_h = max_height;
	p1 = p;
	init_color(COLOR_MAGENTA, 1000, 0, 255);
	init_pair(MALUS,COLOR_MAGENTA ,COLOR_BLACK);
	init_pair(BONUS, COLOR_GREEN, COLOR_BLACK);
	init_pair(STAR, COLOR_RED, COLOR_YELLOW);
	fillListObject();
	addRowObjects();
}

void Object::fillListObject(){
	object_rappresentation[0] = wall; 
	object_rappresentation[1] = vehicle; 
	object_rappresentation[2] = hole; 
	object_rappresentation[3] = gasoline;
	object_rappresentation[4] = nos;  
	object_rappresentation[5] = star; 
}

// scelta del char random con probabilità fatta tramite range
int Object::chooseObjectChar(){
	int min = 1;
	int max = 100;
	int range = max - min;
	int chosen_char = rand() % range + min;
	if(chosen_char >= 1 && chosen_char <= 25){
		return 0;
	}else if(chosen_char >= 26 && chosen_char <= 50){
		return 1;
	}else if(chosen_char >= 51 && chosen_char <= 65){
		return 2;
	}else if(chosen_char >= 66 && chosen_char <= 81){
		return 3;
	}else if(chosen_char >= 81 && chosen_char <= 90){
		return 4;
	}else if(chosen_char >= 91 && chosen_char <= 100){
		return 5;
	}else{
		return -1;
	}
}

void Object::addRowObjects(){
	int max_object_per_level = 0; 
	if(p1->getLevel() == 1){
		max_object_per_level = rand()%p1->getLevel()+2;
	} else if(p1->getLevel() > 1 && p1->getLevel()<=5){
		max_object_per_level = rand()%p1->getLevel()+1;
	} else if(p1->getLevel() > 5){		
		max_object_per_level = rand()%6;
	}
	int i = 1;
	if(max_object_per_level > 0){
		//divido lo schermo in parti uguali, onde evitare di far collisione tra i vari oggetti
		int length_part = max_w/max_object_per_level;
		while (i <= max_object_per_level){
			pt_obj tmp = new desc_object;
			tmp->char_obj = object_rappresentation[chooseObjectChar()];
			// trovo il range su cui può trovarsi l'oggetto
			int min = length_part*(i-1) + strlen(tmp->char_obj);
			int max_tmp = (length_part)*i - strlen(tmp->char_obj) - 1;
			int range = max_tmp - min + 1;
			tmp->x = rand() % range + min;
			tmp->y = 1;
			tmp->next = head;
			head = tmp;
			i++;
		}
	}
}

void Object::drawObjects(){
	pt_obj tmp = head;
	while(tmp != NULL){
		//metodo per stampare usando i colori diversi
		int color_to_disable = -1;
		if(tmp->char_obj[0] == 'V' || tmp->char_obj[0] == '('){
			color_to_disable = 4;
			attron(COLOR_PAIR(MALUS));
		} else if(tmp->char_obj[0] == '[' && tmp->char_obj[1] != '*'){
			color_to_disable = 1;
			attron(COLOR_PAIR(BONUS));
		} else if(tmp->char_obj[0] == '[' && tmp->char_obj[1] == '*'){
			color_to_disable = 2;
			attron(COLOR_PAIR(STAR));
		}
		wmove(stdscr,tmp->y,  tmp->x);
		wprintw(stdscr, tmp->char_obj);
		attroff(color_to_disable);
		tmp = tmp->next;
	}
}

void Object::moveObjectsList(){
	pt_obj tmp = head;
	pt_obj pre_tmp = tmp;
	while(tmp != NULL){
		int color_to_disable = -1;
		if(tmp->char_obj[0] == 'V' || tmp->char_obj[0] == '('){
			color_to_disable = 4;
			attron(COLOR_PAIR(MALUS));
		} else if(tmp->char_obj[0] == '[' && tmp->char_obj[1] != '*'){
			color_to_disable = 1;
			attron(COLOR_PAIR(BONUS));
		} else if(tmp->char_obj[0] == '[' && tmp->char_obj[1] == '*'){
			color_to_disable = 2;
			attron(COLOR_PAIR(STAR));
		}
		cleanLastObjectPosition(*tmp);
		attroff(EMPTY_COLOR);
		//se non è fine schermo, sposto di una casella avanti
		if(tmp->y + 1 < max_h - 1){
			tmp->y = tmp->y + 1;
			wmove(stdscr,tmp->y,  tmp->x);
			wprintw(stdscr, tmp->char_obj);
			pre_tmp = tmp;
			tmp=tmp->next;
		} else {
			//elimino l'oggetto una volta che la y è oltre la lunghezza dello schermo
			deleteObject(tmp, pre_tmp);
			tmp = pre_tmp->next;
		}
		attroff(color_to_disable);
	}
}

int Object::checkCollisionPlayer(int x,int y,int input_player){
	pt_obj tmp = head;
	pt_obj pre_tmp = head;
	// non c'è nessuna collisione -1
	int output = -1;
	while(tmp != NULL && output == -1){
		//controllare ogni char
		if(input_player==119 && y-1 == tmp->y && (unsigned) x <= tmp->x + strlen(tmp->char_obj) && x >= tmp->x){ //w
			output = 0;
		} else if(input_player==97 && (unsigned) x-1 == tmp->x +strlen(tmp->char_obj)-1 && y == tmp->y){ //a
			output = 0;
		} else if((input_player==115 && y+1 == tmp->y && (unsigned) x <= tmp->x+strlen(tmp->char_obj) && x >= tmp->x)
		||  (input_player==-1 && tmp->y+1 == y && (unsigned) x <= tmp->x+strlen(tmp->char_obj) && x >= tmp->x)){ //s
			output = 0;
		} else if(input_player==100 && x+1 == tmp->x && y == tmp->y){ //d
			output = 0;
		}
		if(output == -1){
			pre_tmp = tmp;
			tmp = tmp->next;
		}
	}
	if(output == 0){
		output = checkMalusBonus(tmp);
		cleanLastObjectPosition(*tmp);
		deleteObject(tmp, pre_tmp);
	}
	return output;
}

int Object::checkMalusBonus(pt_obj tmp){
	int which_one = 0;
	if(tmp->char_obj[0] == 'V'){
		which_one = 1;
	} else if(tmp->char_obj[0] == '('){
		if(tmp->char_obj[1] == '@'){
			which_one = 2;
		} else if(tmp->char_obj[1] == 'X'){
			which_one = 3;
		}
	} else if(tmp->char_obj[0] == '['){
		if(tmp->char_obj[1] == '+'){
			which_one = 4;
		} else if(tmp->char_obj[1] == 'N'){
			which_one = 5;
		} else if(tmp->char_obj[1] == '*'){
			which_one = 6;
		}
	}
	return which_one;
}

void Object::deleteObject(pt_obj &tmp, pt_obj &pre_tmp){
	if(tmp == head){
		head = tmp->next;
		delete tmp;
	} else {
		pre_tmp->next = tmp->next;
		delete tmp;
	}
	tmp = NULL;
}

void Object::cleanLastObjectPosition(desc_object tmp){
	attron(COLOR_PAIR(EMPTY_COLOR));
	int n = strlen(tmp.char_obj);
	for(int i = 0; i<n; i++){
		wmove(stdscr,tmp.y,  tmp.x+i);
		wprintw(stdscr, " ");
	}
	refresh();
	attroff(EMPTY_COLOR);
}

void Object::deleteList(){
	pt_obj tmp = head;
	pt_obj null_pointer = NULL;
	while(tmp != NULL){
		cleanLastObjectPosition(*tmp);
		usleep(TIMER);
		deleteObject(tmp, null_pointer);
		tmp = head;
	}
}
