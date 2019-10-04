#ifndef  HASH_HPP
#define  HASH_HPP
#include "position.hpp"
#include <functional>
namespace AnimalEngine {

std::mt19937_64 Position::rnd(0);
uint64_t Position::h_seed = 0;
uint64_t Position::board[5][2][OB] = {};
uint64_t Position::having[4][2][2] = {};
static bool is_initialized = false;
void Position::init(){
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
    if(!is_initialized) Position::init();
    uint64_t h = Position::h_seed;
    if(p.lion.a_pos < OB)
        h ^= board[1][p.lionA_owner][p.lion.a_pos];
    else
        h ^=  having[1][p.lionA_owner][0];
    if(p.lion.b_pos < OB)
        h ^= board[1][p.lionB_owner][p.lion.b_pos];
    else
        h ^=  having[1][p.lionB_owner][1];

    if(p.elephant.a_pos < OB)
        h ^= board[2][p.elephantA_owner][p.elephant.a_pos];
    else
        h ^=  having[2][p.elephantA_owner][0];
    if(p.elephant.b_pos < OB)
        h ^= board[2][p.elephantB_owner][p.elephant.b_pos];
    else
        h ^=  having[2][p.elephantB_owner][1];

    if(p.giraffe.a_pos < OB)
        h ^= board[3][p.giraffeA_owner][p.giraffe.a_pos];
    else
        h ^=  having[3][p.giraffeA_owner][0];

    if(p.giraffe.b_pos < OB)
        h ^= board[3][p.giraffeB_owner][p.giraffe.b_pos];
    else
        h ^=  having[3][p.giraffeB_owner][1];

    if(p.chickin.a_pos < OB)
        h ^= board[p.chickinA_promote * 4][p.chickinA_owner][p.chickin.a_pos];
    else
        h ^=  having[0][p.chickinA_owner][0];
    if(p.chickin.b_pos < OB)
        h ^= board[p.chickinB_promote * 4][p.chickinB_owner][p.chickin.b_pos];
    else
        h ^=  having[0][p.chickinB_owner][0];

    return h;
}

}
#endif // HASH_HPP
