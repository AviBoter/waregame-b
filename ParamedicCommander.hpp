#pragma once
//
// Created by amichai hadad on 19/05/2020.
//
#include "Soldier.hpp"
#include <iostream>


class ParamedicCommander: public Soldier {
public:
    ParamedicCommander(int t) : Soldier(200,100,t,3,true){}
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

            if(temp->team == this->team){ // in my team
                return temp;
            }
        }
        return nullptr;
        
    }
    void allattack(std::vector<std::vector<Soldier*>> &board, std::pair<int,int> source){
        for(int i=0;i<board.size();i++){
            for(int j=0;j< board[0].size();j++){
                Soldier* temp = board[i][j];
                if(temp!=nullptr && temp->team == this->team && temp->type == this->type){
                    temp->attack(board,{i,j});
                }
            }
        }
    }
    virtual void attack(std::vector<std::vector<Soldier*>> &board, std::pair<int,int> source) override{
       int x  = source.first;
        int y = source.second;
        int startX = x-1, endX = x+1 ,startY = y-1,endY = y+1;
        /*
        *  [1][1][1]
        *  [1][0][1]
        *  [1][1][1]
        * 
        */
        for(int i = startX; i <= endX; i++){
            for(int k = startY ; k<= endY; k++){
                if (!(i==x && k==y))
                {
                    Soldier* temp = getSold(board,{i,k});
                    if(temp != nullptr){ // help him he is closest
                        std::cout << this << " is the helper" << std::endl;
                        std::cout << temp << " is got help and his life is: " << temp->healthPoints <<std::endl;
                        temp->restorlife();
                        if (temp->type == this->type)
                        {
                           restorlife();
                        }
                        
                        std::cout << temp << " after help the life is "<< temp->healthPoints << std::endl; 
                    }
                }   
            }
        }
        allattack(board,source);
    }
    void restorlife() override{
        this->healthPoints = 200;
    }
    
            
    
};

