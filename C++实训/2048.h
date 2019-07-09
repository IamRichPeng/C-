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

//find a space to generate number
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

//print out the user interface (array)
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

//Detective failure or not. 1. is there empty cell 2.any two neighbours are identical? horizontal and vertical
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


//Moving around!!! **********************************************************

bool canDoMove(int row, int column, int nextRow, int nextColumn){
    if (nextRow < 0 || nextColumn < 0 || nextRow>=4 || nextColumn >= 4){
        return  false; // outside the board
    }
    if(board[row][column] == 0){
        return false; // damn bug wasting hours 该位为零！！不然就会无止尽移动
    }
    if (board[row][column] != board[nextRow][nextColumn] && board[nextRow][nextColumn]!= 0){
        return false; //different numbers
    }
    return true;
}


bool applyMove(int direction){
    
    int canMove, moveAccomplished = 0;
    switch (direction) {
            //下
        case 0:
            //use loop to implement movement, move until not moveable. and the direction matters (variable "i" or "j" should be correspond to nextI,nextJ; otherwise there will be sequential addition in single row or column; 0336=>00012)
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
                            moveAccomplished = 1;
                        }
                        detectFailure();
                        
                        if (board[nextI][nextJ] == Win)
                            return true;
                    }
            }
            while(canMove);
            
            //generate a new num if there is movement
            if(moveAccomplished){
                generateRandomNum();
            }
            return false;
            break;
          
            //右
        case 1:
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
                            moveAccomplished = 1;
                        }
                        detectFailure();
                        
                        if (board[nextI][nextJ] == Win)
                            return true;
                    }
            }
            while(canMove);
            
            //generate a new num if there is movement
            if(moveAccomplished){
                generateRandomNum();
            }
            return false;
            break;
            
        case 2:
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
                            moveAccomplished = 1;
                        }
                        detectFailure();
                        
                        if (board[nextI][nextJ] == Win)
                            return true;
                    }
            }
            while(canMove);
            
            //generate a new num if there is movement
            if(moveAccomplished){
                generateRandomNum();
            }
            return false;
            break;
            
        case 3:
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
                            moveAccomplished = 1;
                        }
                        detectFailure();
                        
                        if (board[nextI][nextJ] == Win)
                            return true;
                    }
            }
            while(canMove);
            
            //generate a new num if there is movement
            if(moveAccomplished){
                generateRandomNum();
            }
            return false;
            break;
     
    }
    
    return false;
}


void mainStream(){
        

    //turing user's input command into simple int. fk away ACCII
    int resignDir[128];
    resignDir['s'] = 0;//下 down
    resignDir['d'] = 1;//右 right
    resignDir['w'] = 2;//上 up
    resignDir['a'] = 3;//左 left
    
    newGame();
    
    char startGame = 'y';
    while (startGame == 'y'){
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
            
            //Moving Function
            int success = applyMove(Direction);
            if(success){
                cout<<" *************YOU WIN*************\n";
                cout << "\n Challenger! Do you wanna try again\n (y)One more game  (n)I quit\n";
                cin >> startGame;
                if (startGame == 'y'){
                    newGame();
                }
            }
            else if (failuare){
                cout<<" *************YOU SUCK************\n";
                cout << "\n Game Over! Do you wanna try again\n (y)One more game  (n)I quit\n";
                cin >> startGame;
                if (startGame == 'y'){
                    newGame();
                }
            }
            else continue;
        }
        
    }
}

#endif /* _048_h */
