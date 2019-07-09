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
    
    int xBoard,yBoard;
    int grade;
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
        if(i==0) cout << "\tGrade:" << grade;
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
        xBoard = (rand() % (N-1))+1;//1到N-1
        yBoard = (rand() % (N-1))+1;
        if(board[xBoard][yBoard] == ' '){
            occupied = 0;
        }
    }
    board[xBoard][yBoard] = FOOD;
}


//snake the Snake
class snake:public snakeBoard{
public:
    int body[2][(N-2)*(N-2)]; //2D array to store the "snake", row1 stands for X pos.
    int x,y;
    int length;
    char direction;
    int head,tail;
    long start;
    int timeover;
    
    snake();
    void update();
};

snake::snake(){
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

void snake:: update(){
    score = 0;
    head = 3;
    tail = 0;
    grade = 1;
    length = 4;
    gamespeed = 1000000;
    direction = 100;
    
    while(1){
        
        timeover = 1;
        start = clock();
        while((timeover=(clock()-start<=gamespeed))&&!kbhit());
        //detect is time run out of "gamespeed" interval, or there is keyboard input
        if(timeover)
        {
            getchar();
            direction = getchar();
        }
        
        //not WSAD
        if(!(direction==119||direction==115||direction==97 ||direction==100)) {
            cout<<"\nPlease Respest the rule, press \"wsad\" to play";
            cout<< direction<< "NO!!";
            break;
        }
        
        switch(direction)
        {
            case 119: x= body[0][head]-1; y= body[1][head];break; // w向上
            case 115: x= body[0][head]+1; y= body[1][head];break; // s向下
            case 97: x= body[0][head]; y= body[1][head]-1;break; // a向左
            case 100: x= body[0][head]; y= body[1][head]+1;break; // d向右
        }
        
        // hit the edge
        if(x==0 || x==N-1 ||y==0 || y==N-1)  {
            cout<<"\n\t******You Suck*******";
            break;
        }
        //not empty cell or food cell => means that it hit itself.
        if (board[x][y]!=' ' && !(x==xBoard && y==yBoard)) {
            cout<<"\n\t******You Suck*******";
            break;
        }
        // hit the FOOD
        if (x == xBoard && y == yBoard) {
            length++;
            score += 100;
            //level up: speeding up based length
            if (length>=7) {
                length -= 7;
                grade++;
                if (gamespeed >= 200000) {
                    gamespeed = 1100000 - grade*100000;
                }
            }
            // update the "snake"
            board[x][y] = '@';//update head
            board[body[0][head]][body[1][head]] = '*'; // head turn into body
            head = (head+1) % ( (N-2)*(N-2) );
            body[0][head] = x;
            body[1][head] = y;
            generateFood();
            printBoard();
        }
        // doesn't hit the food, update "snake"
        else{
            board[body[0][tail]][body[1][tail]] = ' ';
            tail = (tail+1) % ( (N-2)*(N-2) );
            board[body[0][head]][body[1][head]] = '*';
            head = (head+1) % ( (N-2)*(N-2) );
            body[0][head] = x;
            body[1][head] = y;
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
