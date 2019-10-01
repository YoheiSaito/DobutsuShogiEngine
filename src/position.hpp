#ifndef  POSITION_HPP
#define  POSITION_HPP
#include "common.h"
namespace AnimalEngine{
struct Position;
struct Position {
    //6byte (42bit)
    union {
        uint8_t chickin_promote;
        struct{
            uint8_t  chickinA_promote:4;
            uint8_t  chickinB_promote:4;
        };
    };
    union{
        uint8_t chickin_pos;
        struct {
            uint8_t  chickinA_pos:4;
            uint8_t  chickinB_pos:4;
        };
    };

    union{
        uint8_t lion_pos;
        struct {
            uint8_t  lionA_pos:4;
            uint8_t  lionB_pos:4;
        };
    };

    union{
        uint8_t giraffe_pos;
        struct {
            uint8_t  giraffeA_pos:4;
            uint8_t  giraffeB_pos:4;
        };
    };

    union{
        uint8_t elephant_pos;
        struct {
            uint8_t  elephantA_pos:4;
            uint8_t  elephantB_pos:4;
        };
    };


    union {
        uint8_t owner;
        struct {
            uint8_t  chickinA_owner:1;
            uint8_t  chickinB_owner:1;
            uint8_t     lionA_owner:1;
            uint8_t     lionB_owner:1;
            uint8_t  giraffeA_owner:1;
            uint8_t  giraffeB_owner:1;
            uint8_t elephantA_owner:1;
            uint8_t elephantB_owner:1;
        };
    };

    std::vector<Position> gen_move(Turn turn){
        std::vector<Position> pos;
        return pos;
    }

    bool is_tsumi(Turn turn){
        if(static_cast<bool>(turn)){
            if(lionB_owner == 0)
                return true;
            if(lionA_pos == PositionIndex::B1)
                return true;
        }else{
            if(lionA_owner == 0)
                return true;
            if(lionB_pos == PositionIndex::B4)
                return true;
        }
        return false;
    }
        
        
};
}
#endif //POSITION_HPP
