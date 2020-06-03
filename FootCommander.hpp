#pragma once
//
// Created by amichai hadad on 19/05/2020.
//
#include "Soldier.hpp"
#include <map>
#include <unordered_map>
#include <sstream> //for std::stringstream 
#include <string>  //for std::string


class FootCommander: public Soldier {
public:
    FootCommander(int t) : Soldier(150,20,t,1,true){}
   Soldier* getSold(std::vector<std::vector<Soldier*>> &board, std::pair<int,int> source,std::map<std::string,int> &m){
        if (source.first>=0 && source.first < board.size() && source.second >= 0 && source.second < board[0].size())
        {
            Soldier* temp = board[source.first][source.second];
            if (temp == nullptr )
            {
                return nullptr;
            }
            
            if(temp->team != this->team){ // not in my team
                return temp;
            }
            std::stringstream ss;
            ss << temp;  
            std::string name = ss.str();
            std::cout << name << std::endl; 
            if (temp->team == this->team && temp->type == this->type && m[name] == 0)
            {
                std::cout << m[name] << std::endl;
                m[name] = 1;
                std::cout << m[name] << std::endl;
                temp->attack(board,source);
            }
            
        }
        return nullptr;
        
    }
    virtual void attack(std::vector<std::vector<Soldier*>> &board, std::pair<int,int> source) override{
        int x  = source.first;
        int y = source.second;
        int startX = x-1, endX = x+1 ,startY = y-1,endY = y+1;
        std::map<std::string,int> m;

        while (!(startX<0 && endX > board.size() && startY < 0 && endY > board[0].size()))
        {
        /*
        *  [1][1][1]
        *  [1][0][1]
        *  [1][1][1]
        * 
        *  ...not found...
        *  [2][2][2][2][2]
        *  [2][1][1][1][2]
        *  [2][1][0][1][2]
        *  [2][1][1][1][2]
        *  [2][2][2][2][2]
        */
       
        
            for(int i = startX; i <= endX; i++){
                for(int k = startY ; k<= endY; k++){
                    if (!(i==x && k==y))
                    {
                        Soldier* temp = getSold(board,{i,k},m);
                        if(temp != nullptr){ // attack him he is closest
                            std::cout << temp << " is hert and his life is: " << temp->healthPoints <<std::endl;

                            temp->healthPoints = temp->healthPoints - this->dpa;

                            std::cout << temp << " after attac the life is "<< temp->healthPoints << std::endl;
                            print_board(board,source);
                            if (temp->healthPoints <=0) // got killed
                            {
                                std::cout << temp << " is killed" << std::endl;
                                board[i][k] = nullptr;
                            }
                            return; // attack is over
                            
                        }
                    }

                    
                }
            }// expand the circle
            startX--;
            startY--;
            endX++;
            endY++;
        }
        

    }
    void restorlife() override{
        this->healthPoints = 150;
    }
    
    
            
    
};
