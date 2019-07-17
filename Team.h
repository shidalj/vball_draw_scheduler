/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.h
 * Author: user
 *
 * Created on August 7, 2017, 7:59 PM
 */



#ifndef TEAM_H
#define TEAM_H

#include<memory>

extern unsigned int NUM_GAMES;
struct Team {
    unsigned int number;
    unsigned int games_played;
    unsigned int games_sat;
    Team(unsigned int num);
    bool operator<(const Team &t) const;
    bool operator==(const Team &t) const;
};

struct TeamPTR {
    std::shared_ptr<Team> t;
    TeamPTR(unsigned int num);
    TeamPTR(const TeamPTR &);
    bool operator<(const TeamPTR & tp) const;
    bool operator==(const TeamPTR & tp) const;
    
};

bool not_maxed_out(const TeamPTR &);
#endif /* TEAM_H */

