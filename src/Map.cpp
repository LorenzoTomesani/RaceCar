#include "Map.hpp"

#define ENTER_KEY 10
#define TIME_TO_WAIT 10000
#define SPEED_TO_SPAWN 55000
#define MULTIPLIER_DIFFICULTY 1000
#define INPUT_COLLISION_OBJ_PLAYER -1

Map::Map() {}

/* istanzio le classi, vado a creare i vari bordi, disegno il player e le info su livelli e score */
void Map::initWindow(){
  initscr();
  start_color();
  nodelay(stdscr,TRUE);
  noecho();
  curs_set(0);
  getmaxyx(stdscr, max_height, max_width);
  player_handler = new Player();
  levels_handler = new Level(player_handler);
  objects_handler = new Object(player_handler, max_width, max_height);
  collisions_handler = new Collision(objects_handler, player_handler);
  initialMenu();
  drawBorder();
  player_handler->drawPlayer(max_width, max_height);
  usleep(TIME_TO_WAIT);
  levels_handler->printInfo(max_width, max_height);
  usleep(TIME_TO_WAIT);
  inGameController();
  return;
}

void Map::drawBorder(){
  int x = 0;
  int y = 0;
  wmove(stdscr,y,x);
  while(x < max_width){
    wprintw(stdscr,"#");
    refresh();
    usleep(TIME_TO_WAIT);
    x++;
    wmove(stdscr,y,x);
  }
  x--;
  wmove(stdscr,y,x);
  while(y < max_height){
    wprintw(stdscr,"#");
    refresh();
    usleep(TIME_TO_WAIT);
    y++;
    wmove(stdscr,y,x);
  }
  y--;
  while(x > 0){
    wprintw(stdscr,"#");
    refresh();
    usleep(TIME_TO_WAIT);
    x--;
    wmove(stdscr,y,x);
  }
  while(y >= 0){
    wprintw(stdscr,"#");
    refresh();
    usleep(TIME_TO_WAIT);
    y--;
    wmove(stdscr,y,x);
  }
  y = 0;
  x = (max_width/3)*2;
  wmove(stdscr,y,x);
  while(y < max_height){
    wprintw(stdscr,"#");
    refresh();
    usleep(TIME_TO_WAIT);
    y++;
    wmove(stdscr,y,x);
  }
}

void Map::initialMenu(){
  const char *mex_init= "press start to begin the game";
  wmove(stdscr,(max_height)/2,(max_width - strlen(mex_init))/2);
  wprintw(stdscr,mex_init);
  int ch;
  while ((ch = getch()) == ERR || ch != ENTER_KEY){
    in_game = true;
  }
  clear();
  refresh();
}

/* ---------- controllo del gioco --------------- */
void Map::inGameController(){
  int input_player;
  bool game_over = false;
  // quanti cicli sono passati dall'ultima volta che ho spawnato oggetti/che li ho mossi
  int clock_cycle = 0;
  // canMove variabile booleana per capire se il gioco può andare avanti: se in pausa, il gioco riprende. se quit o lo score è a 0, termina il gioco
  bool can_move = 1;
  bool pause = 0;
  bool quit = 0;
  int spawn = SPEED_TO_SPAWN;
  while(true){
    if(can_move){
      if(player_handler->getLevel()>6){
        spawn = SPEED_TO_SPAWN - player_handler->getLevel() * MULTIPLIER_DIFFICULTY;
      } 
      if(clock_cycle == spawn){
        // per evitare di creare due metodi differenti nel caso in cui sia lo spostamento dell'oggetto a creare una collisione, 
        //usiamo solo un metodo considerando che l'input viene posto a "-1"
        int collision_obj_player = collisions_handler->checkCollisionPlayerObj(INPUT_COLLISION_OBJ_PLAYER);
        if(collision_obj_player > -1){
          levels_handler->updateScore();
          levels_handler->checkScorePerLevel();
          if(player_handler->getScore() == 0){
            can_move = 0;
          }
        }
        // tutti gli oggetti vengono spostasti avanti di una casella, aggiunta una riga di oggetti e disegnata essa stessa 
        objects_handler->moveObjectsList();
        objects_handler->addRowObjects();
        objects_handler->drawObjects();
        clock_cycle = 0;
      }
      if ((input_player = getch()) == ERR) {}
      else {
        if(input_player == 113){  //q
          in_game = false;
          can_move = 0;
          quit = 1;
        } else if(input_player == 112){ //p
          pause = 1;
          can_move = !can_move;
        }
        // controllo che non ci siano state collisioni
        int collision_player_wall =  collisions_handler->checkCollisionPlayerWall(max_width, max_height, input_player);
        int collision_player_obj = collisions_handler->checkCollisionPlayerObj(input_player);
        if(collision_player_wall == 0 && collision_player_obj == -1){
          player_handler->movePlayer(input_player);
        } else if(collision_player_wall == 1) {
          player_handler->changeScore(-1);
          levels_handler->updateScore();
          player_handler->setOriginalPosition();
        } else if(collision_player_obj > -1){
          player_handler->movePlayer(input_player);
          levels_handler->updateScore();
        }
        levels_handler->checkScorePerLevel();
        if(player_handler->getScore() == 0){
          can_move = 0;
          game_over = 1;
        }
      }
      clock_cycle++;
    } else {
      if(pause){
        if ((input_player = getch()) == ERR) {}
        else {
          if(input_player == 112){ //p
            can_move = !can_move;
            pause = 0;
          }
        }
      }else if(!pause && !quit){
        // se lo score è uguale a 0, animazione di gameover
        objects_handler->deleteList();
        usleep(TIME_TO_WAIT);
        player_handler->deletePlayer();
        usleep(TIME_TO_WAIT);
        clear();
        refresh();
        usleep(TIME_TO_WAIT);
        levels_handler->exitMatch(max_width, max_height);
        game_over = true;
      }
      if(game_over) {
        while(getch() != 113){ }
        in_game = false;
      }
      if(in_game == false){
        player_handler->exitGame();
      }
    }
  }
}
