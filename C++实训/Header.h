//
//  Header.h
//  tictactoe
//
//  Created by 彭睿诚 on 2019/7/12.
//  Copyright © 2019年 Ruicheng Peng. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <string>
#include <unistd.h>

#define PLAYER1 'X'
#define PLAYER2 'O'

char userchoice;
char AIchoice;

using namespace std;

char board2[3][3];

pair<int,int>  PLAYERpredicion;

char currentPlayer;



void newGame2();

void printUI2();


bool gameOver();
char detectVictory();

int score();

struct Move{
    int x;
    int y;
};


int minSearch(char AIboard[3][3]);

int maxSearch(char AIboard[3][3]) ;

Move Minimax(char AIboard[3][3]) ;

char changePlayer();

void mainStream2();

#endif /* Header_h */
