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

using namespace std;

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

//重开游戏，
void newGame(){
    for(int i = 0;i < 4; ++i){
        for(int j = 0;j <4;++j){
            board[i][j] = 0 ;
    }
    }
    pair<int, int> pos = generateUnoccupiedPosition();
    board[pos.first][pos.second] = 2;
    
}

//输出用户界面
void printMenu(){
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

void applyMove(int direction){
   // default上，左
    int startRow = 0, startColumn = 0;
    int rowStep = 1, columnStep = 1;
    
    //下
    if (direction == 0){
        startRow = 3;
        rowStep = -1;
    }
    
    //右
    if(direction == 1){
        startColumn = 3;
        columnStep = -1;
    }
    
    //用循环实现：移动一次，所有数字向该方向移动到不可移动为止。
    int movePossible, canAddition = 0;
    
    do{
        movePossible = 0;
        for(int i = startRow;i >= 0 && i < 4; i += rowStep)
            for(int j = startColumn; j >= 0 && j < 4; j += columnStep){
                int nextI = i + dirRow[direction];
                int nextJ = j + dirColumn[direction];
                
                //cout<<i<<" "<<j<<" "<<nextI<<" "<<nextJ<<"\n";
                //check conditions!
                if (canDoMove(i,j,nextI,nextJ)){
                    board[nextI][nextJ] += board[i][j];
                    board[i][j] = 0;
                    movePossible = 1;
                    canAddition = 1;
            }
        }
    }
    while(movePossible);
    
    //do-while全部移动后，并产生新的数字
    if(canAddition){
        pair<int, int> pos = generateUnoccupiedPosition();
        board[pos.first][pos.second] = 2;
    }
    
    
}









int main(){
    
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
        printMenu();
        char input;
        cin >>input;
        
        if (input == 'n')
            newGame();
        else if (input == 'q')
            break;
        else{
            int currentDirection = resignDir[input];
            
            //移动函数
            applyMove(currentDirection);
        }
        
    }
    
    

    return 0;
  
}
