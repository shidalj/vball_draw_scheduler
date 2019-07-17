/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "draw.h"
#include<list>
#include<algorithm>
#include<utility>
#include<fstream>
#include<string>
#include<sstream>
#include<iterator>

using namespace std;

Draw::Draw(unsigned int teams,unsigned int per_side, unsigned int games) : num_teams(teams), 
        teams_per_side(per_side), games_per_team(games) {
    for(int i = 0; i < num_teams; ++i){
        this->teams.push_back(TeamPTR(i));
        adjacency.push_back(vector<unsigned int>());
        for(int j = 0; j < num_teams; ++j){
            if(i != j){
                adjacency[i].push_back(0);
            }
            else {
                adjacency[i].push_back(10000);
            }
        }
    }
}

int Draw::schedule(){
    string filename;
    ostringstream fname;
    fname << num_teams << "teams_" << teams_per_side * 2 << "s_" << games_per_team << "games.csv";
    filename = fname.str();
    ofstream f_out(filename);
    f_out << "game #," << "side 1," << "side2," << "score" << endl; 
    unsigned int game_number = 1;
    while(1){
        vector<TeamPTR> game; // 0,1,2 teammates  3,4,5...teammates
        sort(teams.begin(),teams.end()); // sort by games played, increasing
        TeamPTR next_up = teams[0]; // start with team that has played least games
        game.push_back(next_up);
        list<TeamPTR> remaining;
        back_insert_iterator<list<TeamPTR> > bi(remaining);
        copy_if(++teams.begin(),teams.end(), bi, not_maxed_out);

        if(remaining.size() < teams_per_side * 2 - 1){
            break;
        }
        for(unsigned int j = 1; j < teams_per_side; ++j){
            list<TeamPTR>::iterator li = remaining.begin();
            pair<unsigned int, TeamPTR> mins = make_pair(100000, *li); // set current min to team 1
            auto min_it = remaining.begin();
            while(li != remaining.end()){
                unsigned int adj_sum = 0;
                for(int i = 0; i < j; ++i){
                    adj_sum += adjacency[game[i].t->number][li->t->number];
                }
                if(li->t->games_sat < 2){
                    adj_sum += 6 / (li->t->games_sat + 1);
                }
                if(adj_sum < mins.first){
                    mins.first = adj_sum;
                    mins.second = *li;
                    min_it = li;
                }
                ++li;
            }
            game.push_back(mins.second);
            remaining.erase(min_it);
        }
        // select opponents
        for(unsigned int j = 0; j < teams_per_side; ++j){
            list<TeamPTR>::iterator li = remaining.begin();
            pair<unsigned int, TeamPTR> mins = make_pair(100000, *li); // set current min to team 1
            auto min_it = remaining.begin();
            while(li != remaining.end()){
                unsigned int adj_sum = 0;
                for(int i = 0; i < j + teams_per_side; ++i){
                    adj_sum += adjacency[game[i].t->number][li->t->number];
                }
                if(li->t->games_sat < 2){
                    adj_sum += 6 / (li->t->games_sat + 1);
                }
                if(adj_sum < mins.first){
                    mins.first = adj_sum;
                    mins.second = *li;
                    min_it = li;
                }
                ++li;
            }
            game.push_back(mins.second);
            remaining.erase(min_it);
        }
        auto it = remaining.begin();
        while(it != remaining.end()){
            it->t->games_sat += 1;
            ++it;
        }
        cout << "game: ";
        f_out << game_number << ",";
        ++game_number;
        for(int i = 0; i < game.size()/2; ++i){
            ++(game[i].t->games_played);
            game[i].t->games_sat = 0;
            cout << game[i].t->number << " ";
            f_out << game[i].t->number + 1 << "   ";
            for(int j = 0; j < game.size(); ++j){
                if(j < game.size()/2){
                    adjacency[game[i].t->number][game[j].t->number] += 30;
                }
                else {
                    adjacency[game[i].t->number][game[j].t->number] += 3;
                }
            }
        }
        cout << "vs. ";
        f_out << ",";
        for(int i = game.size()/2; i < game.size(); ++i){
            ++(game[i].t->games_played);
            game[i].t->games_sat = 0;
            cout << game[i].t->number << " ";
            f_out << game[i].t->number + 1 << "   ";
            for(int j = 0; j < game.size(); ++j){
                if(j < game.size()/2){
                    adjacency[game[i].t->number][game[j].t->number] += 3;
                }
                else {
                    adjacency[game[i].t->number][game[j].t->number] += 30;
                }
            }
        }
        cout << endl;
        f_out << ", " <<endl;
    }
    f_out << endl << endl;
    list<TeamPTR> remaining;
    back_insert_iterator<list<TeamPTR> > bi(remaining);
    copy_if(teams.begin(),teams.end(), bi, not_maxed_out);
    cout << "Teams with games remaining:" << endl;
    f_out << "teams short,";
    for(auto it = remaining.begin(); it != remaining.end(); ++it){
        cout << "Team " << it->t->number << "   games played: " << it->t->games_played << endl;
        f_out << it->t->number + 1 << " played: " << it->t->games_played << ",";
    }
    f_out << endl;
    for(int i = 0; i < teams.size(); ++i){
        cout << "team " << teams[i].t->number << " played " << teams[i].t->games_played << " games" << endl;
    }
    return 0;
}