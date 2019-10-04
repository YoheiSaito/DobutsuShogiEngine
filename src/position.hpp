struct Position;
#ifndef  POSITION_HPP
#define  POSITION_HPP
#include "common.h"
#include "move.hpp"
namespace AnimalEngine{
template <int N> using StArray=std::array<char, N>;
using BoardMap = std::tuple< StArray<12>, StArray<8>, StArray<8> >;
    
struct PositionSeperator{
    union {
        uint8_t all;
        struct{
            uint8_t a_pos:4;
            uint8_t b_pos:4;
        };
    };
};

struct Position {
    //6byte (42bit)
    // structure difinition
    union {
        uint8_t chickin_promote;
        struct{
            bool chickinA_promote:1;
            bool chickinB_promote:1;
        };
    };
    
    union {
        uint8_t owner;
        struct {
        union{
            struct{
            uint8_t  chickinA_owner:1;
            uint8_t elephantA_owner:1;
            uint8_t  giraffeA_owner:1;
            uint8_t     lionA_owner:1;
            };
            uint8_t A_owner:4;
        };
        union{
            struct {
            uint8_t  chickinB_owner:1;
            uint8_t elephantB_owner:1;
            uint8_t  giraffeB_owner:1;
            uint8_t     lionB_owner:1;
            };
            uint8_t B_owner:4;
        };
        };
    };


    PositionSeperator chickin;
    PositionSeperator lion;
    PositionSeperator giraffe;
    PositionSeperator elephant;

    // operator
    Position&   operator=  (const Position& p);
    bool        operator== (const Position& p);
    std::string operator() ();

    // setter
    void set_lionA_pos     (PositionIndex, Owner);
    void set_lionB_pos     (PositionIndex, Owner);
    void set_elephantA_pos (PositionIndex, Owner);
    void set_elephantB_pos (PositionIndex, Owner);
    void set_giraffeA_pos  (PositionIndex, Owner);
    void set_giraffeB_pos  (PositionIndex, Owner);
    void set_chickinA_pos  
        (PositionIndex, Owner, const boost::optional<bool> p = boost::none);
    void set_chickinB_pos  
        (PositionIndex, Owner, const boost::optional<bool> p = boost::none);

    // utility
    bool is_tsumi(Turn turn);
    BoardMap make_map();
    Position move(Move, Turn, boost::optional<BoardMap> mp = boost::none);
    std::vector<Position> gen_move(Turn turn);

    // static
    static void test();
    static Position initial_position();
    
    // hash (hash.cpp)
    static std::mt19937_64 rnd;
    static uint64_t h_seed;
    static uint64_t board[5][2][OB];
    static uint64_t having[4][2][2];
    static void init();
    static uint64_t hash(const Position&);
          
};
}
#endif //POSITION_HPP
