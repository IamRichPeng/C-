//
//  TCSnake.h
//  C++实训
//
//  Created by 彭睿诚 on 2019/7/5.
//  Copyright © 2019年 Ruicheng Peng. All rights reserved.
//

#ifndef TCSnake_h
#define TCSnake_h

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>

#include "keyboardhit.h"


#define  N 12
#define FOOD 'o'
using namespace std;

bool isGameRunning;


//define the board of "SNAKE"
class snakeBoard{
public:
    char board[N][N];//定义贪吃蛇棋盘，包括墙壁。
    snakeBoard();   //初始化函数
    void printBoard();
    void generateFood();
    void getgrade();
    
    int foodX,foodY;
    int level;
    double gamespeed;
    int score;
};

//定义初始化函数，将贪吃蛇的棋盘图进行初始化
snakeBoard::snakeBoard()
{
    //empty cell
    for(int i = 1;i<=N-2;i++)
        for(int j=1;j<=N-2;j++)
            board[i][j]=' ';
    //edge
    for(int i =0;i<=N-1;i++)
        board[0][i] = board[N-1][i] = '-';
    for(int i =1;i<=N-2;i++)
        board[i][0] = board[i][N-1] = '|';
    generateFood();
}

//输出贪吃蛇棋盘信息
void snakeBoard::printBoard()
{
    system("clear"); // 清屏
    int i,j;
    cout << "\tuse \"wsad\" to move\n";
    for(i=0;i<N;i++)
    {
        cout << '\t';
        for(j=0;j<N;j++)
            cout<<setw(2)<<board[i][j]; // output board
        if(i==0) cout << "\tGrade:" << level;
        if(i==2) cout << "\tScore:" << score;
        if(i==4) cout << "\ttime interval:" << gamespeed/1000000 << "s";
        cout<<"\n";
    }
}

void snakeBoard::generateFood(){
    srand((int)time(0));
    int occupied;
    occupied = 1;
    while(occupied){
        foodX = (rand() % (N-2))+1;//1到N-2
        foodY = (rand() % (N-2))+1;
        if(board[foodX][foodY] == ' '){
            occupied = 0;
        }
    }
    board[foodX][foodY] = FOOD;
}

void snakeBoard::getgrade(){
    system("clear");
    cout<<"\n Input the starting level you want:\n level 1: 1s moving interval \n level 2: 0.9s moving interval\n level 3: 0.8s moving interval\n level 4: 0.7s moving interval \n level 5: 0.6s moving interval\n";
    cin >> level;
    
    while(level != 1 && level != 2 && level != 3 && level != 4 && level != 5 ){
        cout<<"\n Be a lamb!!! Put a valid number!\n";
        cin >> level;
    }
    switch (level) {
        case 1:
            gamespeed = 1000000;
            break;
        case 2:
            gamespeed = 900000;
            break;
        case 3:
            gamespeed = 800000;
            break;
        case 4:
            gamespeed = 700000;
            break;
        case 5:
            gamespeed = 600000;
            break;
        default:
            break;
    }
}



//snake the Snake
class snake:public snakeBoard{
public:
    int body[2][(N-2)*(N-2)]; //2D array to store the "snake", row1 stands for X pos.
    int headX,headY;
    int length;
    char direction;
    int head,tail;
    long start;
    
    snake();
    void update();
};

// initialize
snake::snake(){
    getgrade();
    
    length = 4;
    head = 3;
    tail = 0;
    direction = 100;
    score = 0;
    
    cout<<"\n\tSNAKE game is about to begin!\n";
    for(int i=1;i>=0;i--)
    {
        start=clock();
        while(clock()-start<=1000000);
        system("clear");
        if(i>0)
            cout << "\tIn:" << i << "sec"<<endl;
    }
    for(int i = 1;i<=3;i++)
        board[1][i] = '*';
        board[1][4] = '@';
    
    for(int i=0; i<4; i++)
    {
        body[0][i] = 1; // X坐标
        body[1][i] = i + 1; //y坐标
    }
}

//****************** Moving Function********************
void snake:: update(){
    
    while(true){
        
        start = clock();
        //in the timeintreval, if there is keyboard hit, resign direction
        while(clock()-start<=gamespeed)
        {
            while(kbhit()!= 0){
                direction = getchar();
            }
        }

        
        //not WSAD
        if(!(direction==119||direction==115||direction==97 ||direction==100)) {
            cout<<"\nPlease Respest the rule, press \"wsad\" to play";
            cout<< direction<< "\t NO!!";
            break;
        }
        
        //update the head of snake x,y
        switch(direction)
        {
            case 119:
                headX= body[0][head]-1; headY= body[1][head];
                break; // w向上
            case 115:
                headX= body[0][head]+1; headY= body[1][head];
                break; // s向下
            case 97:
                headX= body[0][head]; headY= body[1][head]-1;
                break; // a向左
            case 100:
                headX= body[0][head]; headY= body[1][head]+1;
                break; // d向右
        }
        
        // hit the edge
        if(headX==0 || headX==N-1 ||headY==0 || headY==N-1)  {
            cout<<"\n\t******You Suck*******";
            break;
        }
        //not empty cell or food cell => means that it hit itself.
        if (board[headX][headY]!=' ' && !(headX==foodX && headY==foodY)) {
            cout<<"\n\t******You Suck*******";
            break;
        }
        
        // hit the FOOD
        if (headX == foodX && headY == foodY) {
            length++;
            score += 100;
            //level up: speeding up based length
            if (length>=7) {
                length -= 7;
                level++;
                if (gamespeed >= 200000) {
                    gamespeed = 1100000 - level*100000;
                }
            }
            // update the "snake"
            board[headX][headY] = '@';//update head
            board[body[0][head]][body[1][head]] = '*'; // head turn into body
            head = head+1;
            body[0][head] = headX;
            body[1][head] = headY;
            generateFood();
            printBoard();
        }
        // doesn't hit the food, update "snake"
        else{
            board[body[0][tail]][body[1][tail]] = ' ';
            tail = tail+1;
            
            board[body[0][head]][body[1][head]] = '*';
            
            //update new head, both in body array and board.
            head = head+1 ;
            body[0][head] = headX;
            body[1][head] = headY;
            board[body[0][head]][body[1][head]] = '@';
            printBoard();
        }
        
    }
    
}


void mainstream3(){
    char startGame = 'y';
    while (startGame == 'y'){
        snakeBoard Board;
        snake ssss;
        ssss.update();
        cout << "\n Game Over! Do you wanna try again\n (y)One more game  (n)I quit\n";
        cin >> startGame;
    }
}



#endif /* TCSnake_h */
