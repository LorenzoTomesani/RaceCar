#include "Collision.hpp"

Collision::Collision(Object *obj, Player *p){
	p1 = p;
	obj1 = obj;
}

/* controllo che il player non sia andato contro un muro */
int Collision::checkCollisionPlayerWall(int max_width, int max_height, int input_player){
	int x =p1->getx();
	int y =p1->gety();
	if( ((x+1) ==(max_width/3)*2 && input_player == 100 )|| //d
	((y+1) == max_height-1 && input_player == 115) || //s
	((x-1) ==0 && input_player == 97) ||  //a
	((y-1) == 0 && input_player == 119) ){ //w
		return 1;
	}
	return 0;
}

int Collision::checkCollisionPlayerObj(int input_player){
	int x = p1->getx();
	int y = p1->gety();
	int object_Collision = obj1->checkCollisionPlayer(x,y,input_player);
	checkTypeCollision(object_Collision);
	return object_Collision;
}

/* a seconda dell'oggetto che colpisce, 6 scenari diversi */
/* se non c'è Collisione: -1 */
void Collision::checkTypeCollision(int object_code){
	if(object_code <= 3 && object_code >= 1){
		int immunity = p1->getImmunity();
		if(immunity == 0){
			switch(object_code){
				case 1:
		 			p1->changeScore(-1);
				break;
				case 2:
		 			p1->changeScore(-2);
				break;
				case 3:
		 			p1->changeScore(-3);
				break;
			}
		} else if(immunity > 0){
			p1->decreaseImmunity();
		}
	} else if(object_code > 3){
		if(object_code == 4){
			p1->changeScore(1);
		}	else if(object_code == 5){
			p1->changeScore(3);
		} else if(object_code == 6){
			p1->setImmunity();
		}
	}
}
