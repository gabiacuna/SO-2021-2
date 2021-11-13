#define _XOPEN_SOURCE
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

void handleContinueSignal(int sig);

void movTab(int pos_ant, int av, int i);

void puntajes(int p, int c1, int c2);

void mostrar(char * str);

void mostrarInt(char * str, int a);

void turnoAct(int i);

void avanceAct(int ava);

void dadoAct(int dad);

void jugada(int *pos, int *score, int *jail, int dado, int jugador);

