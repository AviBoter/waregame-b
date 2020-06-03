#pragma once
//
// Created by amichai hadad on 19/05/2020.
//
#include "Soldier.hpp"


class Sniper: public Soldier {
public:
    Sniper(int t) : Soldier(100,50,t,2,false){}
    Soldier* getSold(std::vector<std::vector<Soldier*>> &board, std::pair<int,int> source){
        if (source.first>=0 && source.first < board.size() && source.second >= 0 && source.second < board[0].size())
        {
            Soldier* temp = board[source.first][source.second];
                       // std::cout << "here" << std::endl;
            if (temp == nullptr )
            {
                return nullptr;
            }
           // std::cout << temp << std::endl;

            if(temp->team != this->team){ // not in my team
                return temp;
            }
        }
        return nullptr;
        
    }
    std::pair<Soldier*,std::pair<int,int>> getStronger(std::vector<std::vector<Soldier*>> &board){
        int max = 0; // max health
        Soldier* ans = nullptr; 
        std::pair<int,int> location = {0,0};
        for(int i = 0; i < board.size();i++){
            for(int j = 0; j<board[0].size();j++){
                Soldier* temp = getSold(board,{i,j});
                if (temp != nullptr && temp->team != this->team && temp->healthPoints > max){ // strongest enemy
                    max = temp->healthPoints;
                    ans = temp;
                    location = {i,j};
                }
                
            }
        }
        return {ans,location};
    }
    virtual void attack(std::vector<std::vector<Soldier*>> &board, std::pair<int,int> source) override{
        std::pair<Soldier*,std::pair<int,int>> target = getStronger(board);
        Soldier* victem = target.first; // need to kill him
        std::pair<int,int> location = target.second; // his location
        if (target.first != nullptr)
        {
            std::cout << victem << " is hert and his life is: " << victem->healthPoints <<std::endl;
            victem->healthPoints = victem->healthPoints - this->dpa;
            std::cout << victem << " after attac the life is "<< victem->healthPoints << std::endl;
            if (target.first->healthPoints <= 0){
                board[location.first][location.second] = nullptr;// he is dead!! :[
            }
            
        }
        print_board(board,source);
        
    }
    void restorlife() override{
        this->healthPoints = 100;
    }
    
            
    
};

