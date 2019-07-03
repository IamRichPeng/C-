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
#include "curses.h"
#include <iomanip>
#include "2048.h"

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



int main(){
    
    char gameMode;
    //Print Menu
    cout<< " Pick a game you can't win\n";
    cout<< "1. Hysterical 2048; 2.A bot u can't beat 3.Exit game\n";
    cin >> gameMode;
    
    while( gameMode != 51){
        
    switch (gameMode) {
        case 49:
            //generate a random value for Generating new numbers at randam position
            srand(time(0));
            
            //把用户输入的asdw指令转化为简单int
            char resignDir[128];
            resignDir['s'] = 0;//下
            resignDir['d'] = 1;//右
            resignDir['w'] = 2;//上
            resignDir['a'] = 3;//左
            
            newGame();
            
            while(true){
                printUI();
                char input;
                cin >>input;
                
                if (input == 'n')
                    newGame();
                else if (input == 'q')
                    break;
                else{
                    int currentDirection = resignDir[input];
                    
                    //移动函数
                    int success = applyMove(currentDirection);
                    if(success){
                        cout<<" *************YOU WIN*************\n";
                        break;
                    }
                    else if (failuare){
                        cout<<" *************YOU SUCK************\n";
                        break;
                    }
                    else continue;
                }
                
            }
            
            break;
            
        case 50:
            break;
        default:
            cout<<"Are u Serious? Put a valid number!\n\n";
            break;
    }
        //reprint menu
        cout<< " Pick a game you can't win\n";
        cout<< "1. Hysterical 2048; 2.A bot u can't beat 3.Exit game\n";
        cin >> gameMode;
        
    }
    
    return 0;
  
}
