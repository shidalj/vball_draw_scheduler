/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Team.h"
#include "globals.h"
#include<iostream>


using namespace std;

    Team::Team(unsigned int num) : number(num), games_played(0), games_sat(0) {}
    bool Team::operator <(const Team &t) const{
        if(games_sat > t.games_sat)
            return true;
        if(games_sat == t.games_sat)
            return games_played < t.games_played;
        return false;
    }
    
    bool Team::operator ==(const Team& t) const {
        return number == t.number;
    }
    
    TeamPTR::TeamPTR(unsigned int num) {
        t = make_shared<Team>(num);
    }
    
    TeamPTR::TeamPTR(const TeamPTR & tp) : t(tp.t){
    }
  
    bool TeamPTR::operator<(const TeamPTR & tp) const {
        return *t < *(tp.t);
    }
    bool TeamPTR::operator==(const TeamPTR & tp) const{
        return *t == *(tp.t);
    }
    
    bool not_maxed_out(const TeamPTR & tp){
        return tp.t->games_played < NUM_GAMES;
    }