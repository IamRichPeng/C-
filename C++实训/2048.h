//
//  2048.h
//  C++实训
//
//  Created by 彭睿诚 on 2019/7/3.
//  Copyright © 2019年 Ruicheng Peng. All rights reserved.
//

#ifndef _048_h
#define _048_h

#include<iostream>
#include <ctime>
#include <cstdlib>
//#include "curses.h"
#include <iomanip>

#define Win 2187
using namespace std;

// set a global variable
bool failuare;

//棋盘
int board[4][4];

//方向：下（0） 右（1） 上（2） 左（3）,省去用四种case。
int dirRow[] = {1,0,-1,0};
int dirColumn[] = {0,1,0,-1};

//找一个空白位置
pair<int, int> generateUnoccupiedPosition(){
    int occupied,row,column;
    occupied = 1;
    while(occupied){
        row = rand() % 4;
        column = rand() % 4;
        if(board[row][column] == 0){
            occupied = 0;
        }
    }
    return make_pair(row,column);
}

int randomNum(){
    int a = rand() % 2;
    if( a == 0)
        return 3;
    else
        return 6;
}

//重开游戏，
void newGame(){
    for(int i = 0;i < 4; ++i){
        for(int j = 0;j <4;++j){
            board[i][j] = 0 ;
        }
    }
    pair<int, int> pos = generateUnoccupiedPosition();
    board[pos.first][pos.second] = randomNum();
    
}

//输出用户界面
void printUI(){
    system("clear"); //clear screen
    for(int i =0;i < 4; ++i){
        for(int j =0; j<4;++j)
            if(board[i][j]==0)
                cout<< setw(4)<<"."; // simple way to align 对齐
            else
                cout<< setw(4)<< board[i][j];
        cout<<"\n";
    }
    cout<<"N: new game, A: left S: down, D: right , W:up, Q: quit\n";
}

//检测失败
void detectFailure(int canAddition){
    int a = 16;
    if (canAddition == 0){
        for(int i =0;i < 4; ++i){
            for(int j =0; j<4;++j)
        if (board[i][j] != 0) {
            a--;
        }
        }
        if(a==0)
        failuare = true;//输了，不能移动且没有空位了
    }
    else
        failuare = false;
}


//上下左右移动！！**********************************************************

bool canDoMove(int row, int column, int nextRow, int nextColumn){
    if (nextRow < 0 || nextColumn < 0 || nextRow>=4 || nextColumn >= 4){
        return  false; // outside the board
    }
    if(board[row][column] == 0){
        return false; // 该位为零！！不然就会无止尽移动
    }
    if (board[row][column] != board[nextRow][nextColumn] && board[nextRow][nextColumn]!= 0){
        return false; //different numbers 不同数字
    }
    return true;
}

bool applyMove(int direction){
    // default上，左
    int startRow = 0, startColumn = 0;
    int rowDir = 1, colDir = 1;
    
    //下
    if (direction == 0){
        startRow = 3;
        rowDir = -1;
    }
    
    //右
    if(direction == 1){
        startColumn = 3;
        colDir = -1;
    }
    
    //用循环实现：移动一次，所有数字向该方向移动到不可移动为止。
    int canMove, canAddition = 0;
    
    do{
        canMove = 0;
        for(int i = startRow;i >= 0 && i < 4; i += rowDir)
            for(int j = startColumn; j >= 0 && j < 4; j += colDir){
                int nextI = i + dirRow[direction];
                int nextJ = j + dirColumn[direction];
                
                //cout<<i<<" "<<j<<" "<<nextI<<" "<<nextJ<<"\n";
                //check conditions!
                if (canDoMove(i,j,nextI,nextJ)){
                    board[nextI][nextJ] += board[i][j];
                    board[i][j] = 0;
                    canMove = 1;
                    canAddition = 1;
                }
                detectFailure(canAddition);
                
                if (board[nextI][nextJ] == Win)
                    return true;
            }
    }
    while(canMove);
    
    //do-while全部移动后，并产生新的数字
    if(canAddition){
        pair<int, int> pos = generateUnoccupiedPosition();
        board[pos.first][pos.second] = randomNum();
    }
    return false;
    
}

void mainStream(){
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
}

#endif /* _048_h */
