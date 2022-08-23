# RACE CAR GAME IN  C++

## Documentazione
* [Ncurses](#ncurses)
* [Prerequisiti](#prerequisiti)
* [Compilazione](#compilazione)
* [Esecuzione](#esecuzione)
* [Comandi](#comandi)
* [Scopo del Gioco](#scopo)

## Ncurses
È una libreria software che permette di gestire il display di un'applicazione su un terminale. 
Fornisce un'API che permette funzionalità grafiche e l'utilizzo del mouse su un terminale a caratteri.
Libreria sviluppata per sistemi operativi Unix.
	
## Prerequisiti 	
- S.O: Unix-like
- ncurses : sudo apt-get install libncurses5-dev libncursesw5-dev
- make:  sudo apt-get install build-essential

## Compilazione
All'interno della cartella è possibile trovare un "Makefile". 
Per compilare: 
```bash
Make
```
Per pulire i file creati tramite Make:
```bash
Make clean
```

## Esecuzione
Per eseguire: 
```bash
cd bin/
./RaceCar.sh
```

## Comandi
	- p: per mettere in pausa il gioco
	- q: per uscire dal gioco prima che lo score sia uguale a 0
	- w: per spostarsi avanti 
	- s: per sposarsi indietro
	- a: per spostarsi a destra 
	- d: per spostarsi a sinistra

## Scopo
Il player che è una macchina ('V' gialla), deve raccogliere punti (gli oggetti
in verde) evitando di colpire gli ostacoli (gli oggetti in magenta). L'oggetto in rosso
con sfondo giallo consente di essere immune a due collisioni con gli ostacoli.
Raggiunto un certo punteggio, il player passa al livello successivo. All'aumentare 
del livello, aumentano gli oggetti che possono spawnare sulla stessa riga ed 
aumenta leggermente la velocità con cui gli oggetti si muovono in avanti. 
Se il player scende sotto un certo punteggio, torna al livello precedente.
 Il player perde quando lo score risulta essere uguale a 0.
	

