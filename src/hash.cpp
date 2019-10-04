#ifndef  HASH_HPP
#define  HASH_HPP
#include "position.hpp"
#include <functional>
namespace AnimalEngine {

std::mt19937_64 Position::rnd(0);
uint64_t Position::h_seed = 0;
uint64_t Position::board[5][2][OB] = {};
uint64_t Position::having[4][2][2] = {};
void Position::init(){
    static bool is_initialized = false;
    if(is_initialized == false){
        h_seed = rnd();
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 2; j++){
                for(int k = 0; k < 12; k++){
                    board[i][j][k] = rnd();
                    board[i][j][k] = rnd();
                }
            }
        }
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 2; j++){
                having[i][j][0] = rnd();
                having[i][j][1] = rnd();
            }
        }
        is_initialized = true;
    }
}
uint64_t Position::hash(const Position& p){
    auto h = Position::h_seed;

    if(p.lion.a_pos >= OB)
        h ^= having[1][p.lionA_owner][p.lion.a_pos];
    else
        h ^=  board[1][p.lionA_owner][0];
    if(p.lion.b_pos >= OB)
        h ^= having[1][p.lionB_owner][p.lion.b_pos];
    else
        h ^=  board[1][p.lionB_owner][1];

    if(p.elephant.a_pos >= OB)
        h ^= having[2][p.elephantA_owner][p.lion.a_pos];
    else
        h ^=  board[2][p.elephantA_owner][0];
    if(p.elephant.b_pos >= OB)
        h ^= having[2][p.elephantB_owner][p.lion.b_pos];
    else
        h ^=  board[2][p.elephantB_owner][1];

    if(p.giraffe.a_pos >= OB)
        h ^= having[3][p.giraffeA_owner][p.lion.a_pos];
    else
        h ^=  board[3][p.giraffeA_owner][0];
    if(p.giraffe.b_pos >= OB)
        h ^= having[3][p.giraffeB_owner][p.lion.b_pos];
    else
        h ^=  board[3][p.giraffeB_owner][1];

    if(p.chickin.a_pos >= OB)
        h ^= having[p.chickinA_promote * 4][p.chickinA_owner][p.lion.a_pos];
    else
        h ^=  board[3][p.chickinA_owner][0];
    if(p.chickin.b_pos >= OB)
        h ^= having[p.chickinB_promote * 4][p.chickinB_owner][p.lion.b_pos];
    else
        h ^=  board[3][p.chickinB_owner][0];


    return h;
}

}
#endif // HASH_HPP
