//
//  OOXXgame.h
//  C++实训
//
//  Created by 彭睿诚 on 2019/7/5.
//  Copyright © 2019年 Ruicheng Peng. All rights reserved.
//

#ifndef OOXXgame_h
#define OOXXgame_h
//#include <map>
//map<string,char> winner; //Key value: string, element aka mapped value(return value): char
//
//map<string,string> bestMove;
//递归，一次性列出OOXX所有的可能结果，存储在bestMove中，每一个bestMove["???"](key value) map一个最优填充方案：bestMove.second(map value)。后面调用map:bestmove就好了。
//递归算法可以在github上旧版本找到。commit: ready to add minimax

#include "Header.h"

void newGame2(){
    currentPlayer = PLAYER1;
    for(int i  = 0; i<3 ; ++i){
        for(int j = 0; j<3; ++j){
            board2[i][j] = '.';
        }
    }
    PLAYERpredicion.first = PLAYERpredicion.second = 0;
}

void printUI2(){
    system("clear"); //clear screen
    cout<<"Use \"wsad\" to move the inserting position, and \"p\" to insert your decision\n";
    for(int i  = 0; i<3 ; ++i){
        for(int j  = 0; j<3 ; ++j)
            if(make_pair(i, j) ==  PLAYERpredicion && !gameOver())//有人赢了就不要再输出 预判的下一个玩家。
                cout << currentPlayer; //预判位置，new player的符号显示在上一个插入点
            else
                cout << board2[i][j];
        cout<< "\n";
    }
}

bool gameOver() {
    if(detectVictory() == PLAYER1) return true;
    if(detectVictory() == PLAYER2) return true;
    if(detectVictory() == 'N') return true;
    return false;
}

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
    
    char emptySpace = 'N';
    for(int i  = 0; i<3 ; ++i){
        for(int j  = 0; j<3 ; ++j){
            if(board2[i][j] == '.')
                emptySpace = 'Y';
        }
    }
    return emptySpace;
}

int score() {
    if(detectVictory() == userchoice) { return 10; }
    else if(detectVictory() == AIchoice) { return -10; }
    return 0; // draw
}



Move Minimax(char AIboard[3][3]) {
    double bestMoveScore = 100; // -100 is arbitrary
    Move bestMove;
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(AIboard[i][j] == '.') {
                AIboard[i][j] = AIchoice;
                int tempMoveScore = maxSearch(AIboard);
                if(tempMoveScore <= bestMoveScore) {
                    bestMoveScore = tempMoveScore;
                    bestMove.x = i;
                    bestMove.y = j;
                }
                AIboard[i][j] = '.';
            }
        }
    }
    
   // cout<<"\n "<<bestMoveScore<<" suppose to be 0";
    return bestMove;
}


int maxSearch(char AIboard[3][3]) {
    if(gameOver()) return score();
    Move bestMove;
    
    int bestMoveScore = -1000;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(AIboard[i][j] == '.') {
                AIboard[i][j] = userchoice;
                int tempScore = minSearch(AIboard);
                if(tempScore >= bestMoveScore) {
                    bestMoveScore = tempScore;
                    bestMove.x = i;
                    bestMove.y = j;
                }
                AIboard[i][j] = '.';
            }
        }
    }
    
    //    cout<< "\n"<<bestMoveScore<<"maxsearch";
    return bestMoveScore;
}


int minSearch(char AIboard[3][3]) {
    if(gameOver()) return score();
    Move bestMove;
    
    int bestMoveScore = 1000;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(AIboard[i][j] == '.') {
                AIboard[i][j] = AIchoice;
                int tempScore = maxSearch(AIboard);
                if(tempScore <= bestMoveScore) {
                    bestMoveScore = tempScore;
                    bestMove.x = i;
                    bestMove.y = j;
                }
                AIboard[i][j] = '.';
            }
        }
    }
    
    return bestMoveScore;
}


char changePlayer(){
    if(currentPlayer == PLAYER1)
        return PLAYER2;
    else if (currentPlayer == PLAYER2)
        return PLAYER1;
    else
        return -1;
}




void mainStream2(){
    //big loop to control one more game
    char startGame = 'y';
    while (startGame == 'y'){
        
        cout<< " Choose what you want to be: O or X, and X go first.\n";
        cin >> userchoice;
        while(userchoice != 'O' && userchoice != 'X'){
            cout<< " Choose what you want to be: O or X, and X go first.\n";
            cin >> userchoice;
        }

     //   currentPlayer = userchoice , 不想user总是先手，把设置currentplayer放在newgame里了
    if(userchoice == PLAYER1) AIchoice = PLAYER2;
    else AIchoice = PLAYER1;
        
    newGame2();
    printUI2();
    
    string inputs = "wasd";
    //把用户输入的asdw指令转化为简单int
    char resignDir[128];
    resignDir['s'] = 0;//下
    resignDir['d'] = 1;//右
    resignDir['w'] = 2;//上
    resignDir['a'] = 3;//左
    
    while(!gameOver()){
        if(currentPlayer == userchoice){
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
                
                if(0<= nextPos.first && nextPos.first<3 && 0<= nextPos.second && nextPos.second<3 )
                    PLAYERpredicion = nextPos;
            }
            // 确定位置，存入board
            else if (input == 'p'){
                if(board2[ PLAYERpredicion.first][ PLAYERpredicion.second] == '.'){
                    board2[ PLAYERpredicion.first][ PLAYERpredicion.second] = currentPlayer;
                    currentPlayer = changePlayer();
                }
                else{
                    cout<< "Don't embarrass yourself. Pick an empty cell!!!\n";
                    usleep(1000000);
                }
            }
            else{
                cout<< "Don't embarrass yourself. Input a valid key!!!\n";
                usleep(1000000);
            }
        }
        
        //Artificial Intelligence is invading us
        else{
            Move AImove = Minimax(board2);
            board2[AImove.x][AImove.y] = AIchoice;
            currentPlayer = changePlayer();
        }
        
        printUI2();
    }
    
    
    if(detectVictory() == userchoice)
        cout<< "\n*****You won! Congratulation*****\n";
    else if (detectVictory() == AIchoice)
        cout<< " ********   YOU SUCK   ********\n";
    else
        cout<<" ******** Draw ********";
        
        cout << "\n Do you wanna try again\n (y)One more game  (n)I quit\n";
        cin >> startGame;
    }
}


#endif /* OOXXgame_h */
