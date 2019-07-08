//
//  main.cpp
//  C++实训
//
//  Created by 彭睿诚 on 2019/7/2.
//  Copyright © 2019年 Ruicheng Peng. All rights reserved.
//

#include<iostream>
#include <ctime>
#include <cstdlib>
#include "2048.h"
#include "OOXXgame.h"
#include "TCSnake.h"

using namespace std;

//找一个空白位置
pair<int, int> generateUnoccupiedPosition();
//重开游戏，
void newGame();
//输出用户界面
void printUI();
//上下左右移动！！**********************************************************
bool canDoMove(int , int , int , int);
bool applyMove(int);

void  mainStream();


int main(){
    
    //generate a random value for Generating new numbers at randam position
    srand(time(0));
    
    char gameMode;
    //Print Menu
    cout<< "\nPick a game you can't win\n";
    cout<< "1. Hysterical 2048; 2.A bot u can't beat; 3.Snake! 4.Exit game\n";
    cin >> gameMode;
    
    while( gameMode != 52){
        
    switch (gameMode) {
        case 49:
            mainStream();
            break;
            
        case 50:
            mainStream2();
            break;
        case 51:
            mainstream3();
            break;
        default:
            cout<<"Are u Serious? Put a valid number!\n\n";
            break;
    }
        //reprint menu
        system("clear");
        cout<< " Pick a game you can't win\n";
        cout<< "1. Hysterical 2048; 2.A bot u can't beat; 3.Snake! 4.Exit game\n";
        cin >> gameMode;
        
    }
    
    return 0;
  
}
