/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: user
 *
 * Created on August 7, 2017, 7:58 PM
 */

#include <cstdlib>
#include<iostream>
#include<vector>
#include "globals.h"
#include "utilities.h"
#include "draw.h"
#include<sstream>

using namespace std;

/*
 * 
 */
unsigned int NUM_GAMES = 0;

int main(int argc, char** argv) {
    ostringstream argsout;
    argsout << argv[1] << " " << argv[2] << " " << argv[3] << endl;
    istringstream argsin(argsout.str());
    unsigned int teams;
    unsigned int perside;
    unsigned int games;
    argsin >> teams >> perside >> games;
    NUM_GAMES = games;
    Draw sched(teams,perside,games);
    return sched.schedule();
}

