/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   draw.h
 * Author: user
 *
 * Created on August 7, 2017, 8:09 PM
 */

#ifndef DRAW_H
#define DRAW_H

#include "globals.h"
#include "utilities.h"
#include "Team.h"
#include<vector>
#include<iostream>
#include<fstream>


class Draw {
private:
    std::vector<TeamPTR> teams;
    std::vector<std::vector<unsigned int> > adjacency;
    unsigned int num_teams;
    unsigned int teams_per_side;
    unsigned int games_per_team;
public:
    Draw(unsigned int teams,unsigned int per_side, unsigned int games);
    int schedule();
};


#endif /* DRAW_H */

