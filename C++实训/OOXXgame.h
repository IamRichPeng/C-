//
//  OOXXgame.h
//  C++实训
//
//  Created by 彭睿诚 on 2019/7/5.
//  Copyright © 2019年 Ruicheng Peng. All rights reserved.
//

#ifndef OOXXgame_h
#define OOXXgame_h

#include <iostream>
#include <string>
#include <map>

#define PLAYER1 'X'
#define PLAYER2 'O'


using namespace std;

string board2[3];

pair<int,int>  PLAYERpredicion;

char currentPlayer;

map<string,char> winner; //Key value: string, element aka mapped value(return value): char

map<string,string> bestMove;



void newGame2(){
    currentPlayer = PLAYER1;
    for(int i  = 0; i<3 ; ++i){
        board2[i].resize(3);
        for(int j = 0; j<3; ++j){
            board2[i][j] = '.';
        }
    }
    PLAYERpredicion.first =  PLAYERpredicion.second = 0;
}


// 1 有人赢了 ； 0 继续！ ； -1 平局
char detectVictory(){
    //horizontal and vertical
    for(int i  = 0; i<3 ; ++i){
        if(board2[0][i] != '.'
           && board2[0][i] == board2[1][i] && board2[0][i] == board2[2][i])
            return board2[0][i];
        if(board2[i][0] != '.'
           && board2[i][0] == board2[i][1] && board2[i][0] == board2[i][2])
            return board2[i][0];
    }
    // hardcode, diognal
    if(board2[0][0] != '.'
       && board2[0][0] == board2[1][1] && board2[0][0] == board2[2][2])
        return board2[0][0];
    if(board2[2][0] != '.'
       && board2[2][0] == board2[1][1] && board2[2][0] == board2[0][2])
        return board2[2][0];
    
    int isFull = -1;
    for(int i  = 0; i<3 ; ++i)
        for(int j  = 0; j<3 ; ++j)
            if(board2[i][j] == '.')
                isFull = 0;
    return isFull;
}



void printUI2(){
    system("clear"); //clear screen
    for(int i  = 0; i<3 ; ++i){
        for(int j  = 0; j<3 ; ++j)
            if(make_pair(i, j) ==  PLAYERpredicion && detectVictory() == 0)//有人赢了就不要再输出 预判的下一个玩家。
                cout << currentPlayer; //预判位置，new player的符号显示在上一个插入点
            else
                cout << board2[i][j];
        cout<< "\n";
    }
}


bool inside(pair<int, int> pos){
    return 0<= pos.first && pos.first<3 && 0<= pos.second && pos.second<3 ;
}


char getCurrentPlayer(string boardInLine){
    int Xnums = 0, Onums = 0;
    for( auto c : boardInLine)
        if (c == PLAYER1) {
            ++Xnums;
        }
        else if (c == PLAYER2) {
            ++Onums;
        }
    if(Xnums > Onums)
        return PLAYER2;
    else
        return PLAYER1;
}


void boardInlineConvertBackToBoard(string boardInLine){
    for(int i  = 0; i<3 ; ++i)
        for(int j  = 0; j<3 ; ++j)
            board2[i][j] = boardInLine[i * 3 + j];
}

string boardToBoardInLine(){
    string boardInLine;
    for(int i  = 0; i<3 ; ++i)
        for(int j  = 0; j<3 ; ++j)
            boardInLine += board2[i][j];
    return boardInLine;
}

char changePlayer(){
    if(currentPlayer == PLAYER1)
        return PLAYER2;
    else if (currentPlayer == PLAYER2)
        return PLAYER1;
    else
        return -1;
}


//using recursion to traverse all the possibilities putting currnetplayer in, and calculate who is going to win under this concidion

char calculateWinner(string boardInLine){
    
    if(winner.find(boardInLine) != winner.end()) // boardline 在map里，不在的话find会返回winner.end
        return winner[boardInLine]; //  search (map)winner, find the mapped value(char) according to Key value: String
    boardInlineConvertBackToBoard(boardInLine);
    char state = detectVictory();
    if (state != 0) {
        winner[boardInLine] = state;
        return state;
    }
    
    // if the game is still going on , step into recursion
    char currentPlayer = getCurrentPlayer(boardInLine); // local variable,not the global one
    
    char bestResult = changePlayer(); // X,O,-1
    
    string best_current_move;
    
    for(int i = 0;i<9; ++i)
        if(boardInLine[i] == '.') {
            boardInLine[i] = currentPlayer;
            char next_win = calculateWinner(boardInLine);
            if (next_win == currentPlayer) {
                bestResult = currentPlayer;
                best_current_move = boardInLine;
            }
            else if(next_win == -1 && bestResult == changePlayer()) {// draw
                bestResult = -1;
                best_current_move = boardInLine;
            }
            boardInLine[i] = '.';
        }
    
    bestMove[boardInLine] = best_current_move;
    winner[boardInLine] = bestResult;
    return bestResult;
    
}


//****************************************************************

void  mainStream2() {
    //递归，一次性列出OOXX所有的可能结果，存储在bestMove中，每一个bestMove["???"](key value) map一个最优填充方案：bestMove.second(map value)。后面调用map:bestmove就好了。
    calculateWinner(".........");
    
    cout<< " Choose what you want to be: O or X\n";
    char userchoice;
    cin >> userchoice;
    while(userchoice != 'O' && userchoice != 'X'){
        cout<< " Choose what you want to be: O or X\n";
         cin >> userchoice;
    }
    
    //   cout<< winner["XXOO....."]<<" "<< bestMove["XXOO....."];
    newGame2();
    printUI2();
    
    
    string inputs = "wasd";
    //把用户输入的asdw指令转化为简单int
    char resignDir[128];
    resignDir['s'] = 0;//下
    resignDir['d'] = 1;//右
    resignDir['w'] = 2;//上
    resignDir['a'] = 3;//左
    
    while(detectVictory() == 0){
        if( currentPlayer == userchoice){
            char input;
            cin >> input;
            //输入方位，选位置
            if(inputs.find(input) != string::npos){// not position,读取所有有效方位
                pair<int, int> nextPos =  PLAYERpredicion;
                int direction = resignDir[input];
    
                switch (direction) {
                    case 0:
                        nextPos.first += 1;
                        nextPos.second += 0;
                        break;
                    case 1:
                        nextPos.first += 0;
                        nextPos.second += 1;
                        break;
                    case 2:
                        nextPos.first -= 1;
                        nextPos.second += 0 ;
                        break;
                    case 3:
                        nextPos.first += 0;
                        nextPos.second -= 1;
                        break;
                    default:
                        break;
                }

                if(inside(nextPos))
                    PLAYERpredicion = nextPos;
            }
            // 确定位置，存入board
            else if (input == 'p'){
                if(board2[ PLAYERpredicion.first][ PLAYERpredicion.second] == '.'){
                    board2[ PLAYERpredicion.first][ PLAYERpredicion.second] = currentPlayer;
                    currentPlayer = changePlayer();
                    //first edition: two players,no AI
                    //                if ( currentPlayer == FIRST_PLAYER)
                    //                    currentPlayer = SECOND_PLAYER;
                    //                else
                    //                    currentPlayer = FIRST_PLAYER;
                }
            }
        }
        else{
            // generate best move
            string boardInLine = boardToBoardInLine();
            boardInlineConvertBackToBoard(bestMove[boardInLine]);
            currentPlayer = changePlayer();
        }
        printUI2();
    }
    
    char state = detectVictory();
    if( state == -1)
        cout<< "\tDRAW!!\n";
    else if(userchoice == state)
        cout<< state << " You won! Congratulation\n";
    else
        cout<< " ********   YOU SUCK   ********\n";
    
}

#endif /* OOXXgame_h */
