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
//#include <unistd.h>

#include "2048.h"
#include "OOXXgame.h"
#include "TCSnake.h"

using namespace std;


int main(){
    
    //generate a random value for Generating new numbers at randam position
    srand((int)time(0));
    
    char gameMode;
    //Print Menu
    cout<< "\nPick a game you can't win\n";
    cout<< "1. Hysterical 2048; 2.A bot u can't beat; 3.Snake! 4.Exit game\n";
    cin >> gameMode;
    
    while( gameMode != 52){
        
    switch (gameMode) {
        case 49:
            system("clear");
            mainStream();
            break;
        case 50:
            system("clear");
            mainStream2();
            break;
        case 51:
            system("clear");
            mainstream3();
            break;
        default:
            cout<<"Are u Serious? Put a valid number!\n\n";
            break;
    }
        //reprint menu
//        unsigned int sleep = 1000000;
//        usleep(sleep);
        system("clear");
        cout<< " Pick a game you can't win\n";
        cout<< "1. Hysterical 2048; 2.A bot u can't beat; 3.Snake! 4.Exit game\n";
        cin >> gameMode;
        
    }
    
    return 0;
  
}
