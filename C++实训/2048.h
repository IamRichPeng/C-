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
#include <iomanip>

#define Win 2187
using namespace std;

// set a global variable
bool failuare;

//棋盘
int board[4][4];


int randomNum(){
    int a = rand() % 2;
    if( a == 0)
        return 3;
    else
        return 6;
}

//找一个空白位置
void generateRandomNum(){
    int occupied,row,column;
    occupied = 1;
    while(occupied){
        row = rand() % 4;
        column = rand() % 4;
        if(board[row][column] == 0){
            board[row][column] = randomNum();
            occupied = 0;
        }
    }
}


//重开游戏，
void newGame(){
    for(int i = 0;i < 4; ++i){
        for(int j = 0;j <4;++j){
            board[i][j] = 0 ;
        }
    }
    generateRandomNum();
    
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

//检测失败,检测是否有空位，且行，列，相邻有无相同。
void detectFailure(){
    failuare = true;
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            if(board[i][j]==0 || board[i][j+1]==0 || board[i][j] == board[i][j+1]){
                failuare = false;
                break;
            }
        }
    }
    for(int j=0; j<4; j++){
        for(int i=0; i<3; i++){
            if(board[i][j]==0 || board[i+1][j]==0 || board[i][j] == board[i+1][j]){
                failuare = false;
                break;
            }
        }
    }
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
    
    int canMove, canAddition = 0;
    switch (direction) {
            //下
        case 0:
            //用循环实现：移动一次，所有数字向该方向移动到不可移动为止。
            do{
                canMove = 0;
                for(int i = 3;i >= 0 && i < 4; i -= 1)
                    for(int j = 0; j >= 0 && j < 4; j += 1){
                        int nextI = 0,nextJ = 0;
                        nextI = i + 1;
                        nextJ = j + 0;
                    
                        //cout<<i<<" "<<j<<" "<<nextI<<" "<<nextJ<<"\n";
                        //check conditions!
                        if (canDoMove(i,j,nextI,nextJ)){
                            board[nextI][nextJ] += board[i][j];
                            board[i][j] = 0;
                            canMove = 1;
                            canAddition = 1;
                        }
                        detectFailure();
                        
                        if (board[nextI][nextJ] == Win)
                            return true;
                    }
            }
            while(canMove);
            
            //do-while全部移动后，并产生新的数字
            if(canAddition){
                generateRandomNum();
            }
            return false;
            break;
          
            //右
        case 1:
            //用循环实现：移动一次，所有数字向该方向移动到不可移动为止。
            do{
                canMove = 0;
                for(int i = 0;i >= 0 && i < 4; i += 1)
                    for(int j = 3; j >= 0 && j < 4; j -= 1){
                        int nextI = 0,nextJ = 0;
                        nextI = i + 0;
                        nextJ = j + 1;
                        
                        //cout<<i<<" "<<j<<" "<<nextI<<" "<<nextJ<<"\n";
                        //check conditions!
                        if (canDoMove(i,j,nextI,nextJ)){
                            board[nextI][nextJ] += board[i][j];
                            board[i][j] = 0;
                            canMove = 1;
                            canAddition = 1;
                        }
                        detectFailure();
                        
                        if (board[nextI][nextJ] == Win)
                            return true;
                    }
            }
            while(canMove);
            
            //do-while全部移动后，并产生新的数字
            if(canAddition){
                generateRandomNum();
            }
            return false;
            break;
            
        case 2:
            //用循环实现：移动一次，所有数字向该方向移动到不可移动为止。
            do{
                canMove = 0;
                for(int i = 0;i >= 0 && i < 4; i += 1)
                    for(int j = 0; j >= 0 && j < 4; j += 1){
                        int nextI = 0,nextJ = 0;
                        nextI = i - 1;
                        nextJ = j + 0;
                        
                        //cout<<i<<" "<<j<<" "<<nextI<<" "<<nextJ<<"\n";
                        //check conditions!
                        if (canDoMove(i,j,nextI,nextJ)){
                            board[nextI][nextJ] += board[i][j];
                            board[i][j] = 0;
                            canMove = 1;
                            canAddition = 1;
                        }
                        detectFailure();
                        
                        if (board[nextI][nextJ] == Win)
                            return true;
                    }
            }
            while(canMove);
            
            //do-while全部移动后，并产生新的数字
            if(canAddition){
                generateRandomNum();
            }
            return false;
            break;
            
        case 3:
            //用循环实现：移动一次，所有数字向该方向移动到不可移动为止。
            do{
                canMove = 0;
                for(int i = 0;i >= 0 && i < 4; i += 1)
                    for(int j = 0; j >= 0 && j < 4; j += 1){
                        int nextI = 0,nextJ = 0;
                        nextI = i + 0;
                        nextJ = j - 1;
                        
                        //cout<<i<<" "<<j<<" "<<nextI<<" "<<nextJ<<"\n";
                        //check conditions!
                        if (canDoMove(i,j,nextI,nextJ)){
                            board[nextI][nextJ] += board[i][j];
                            board[i][j] = 0;
                            canMove = 1;
                            canAddition = 1;
                        }
                        detectFailure();
                        
                        if (board[nextI][nextJ] == Win)
                            return true;
                    }
            }
            while(canMove);
            
            //do-while全部移动后，并产生新的数字
            if(canAddition){
                generateRandomNum();
            }
            return false;
            break;
     
    }
    
    return false;
}


void mainStream(){
    //把用户输入的asdw指令转化为简单int,查个鸡儿ASCII表
    int resignDir[128];
    resignDir['s'] = 0;//下
    resignDir['d'] = 1;//右
    resignDir['w'] = 2;//上
    resignDir['a'] = 3;//左
    
    newGame();
    
    while(true){
        printUI();
        char input;
        cin >>input;
        
        while(input != 'n' && input !='a' && input !='s' && input != 'd' && input !='w' && input != 'q' ){
            cout<<"\n Be a lamb!!! Put a valid number!\n";
            cin >> input;
        }
        
        if (input == 'n')
            newGame();
        else if (input == 'q')
            break;
        else{
            int Direction = resignDir[input];
            
            //移动函数
            int success = applyMove(Direction);
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
