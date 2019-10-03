#ifndef  POSITION_HPP
#define  POSITION_HPP
#include "common.h"
#include "move.hpp"
namespace AnimalEngine{
struct Position;
struct Position {
    //6byte (42bit)
    static Position initial_position(void){
        Position p ;
        p.chickinA_promote = false;
        p.chickinB_promote = false;

        p.chickinA_pos = PositionIndex::B3;
        p.lionA_pos    = PositionIndex::B4;
        p.elephantA_pos = PositionIndex::A4;
        p.giraffeA_pos  = PositionIndex::C4;

        p.chickinB_pos = PositionIndex::B2;
        p.lionB_pos    = PositionIndex::B1;
        p.elephantB_pos = PositionIndex::C1;
        p.giraffeB_pos  = PositionIndex::A1;
        p.A_owner = 0x0;
        p.B_owner = 0xf;
        return p;
    }
    union {
        uint8_t chickin_promote;
        struct{
            bool chickinA_promote:1;
            bool chickinB_promote:1;
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

    std::vector<Position> gen_move(Turn turn){
        std::vector<Position> pos;
        return pos;
    }

    Position move(Move mv){
        return *this;
    }
    void print(){ 
        std::string mochigoma[2]={"", ""};
        std::string bstr;
        bstr.resize(3*4, ' ');
        for(int i = 0; i < 3*4; i++){
            bstr[i] = ' ';
        }

        if(lionA_pos < 12)
            bstr[lionA_pos] = lionA_owner==Turn::BLACK?'l':'L';
        else 
            mochigoma[(unsigned int)(lionA_owner)].push_back('l');
        if(lionB_pos < 12)
            bstr[lionB_pos] = lionB_owner==Turn::BLACK?'l':'L';
        else 
            mochigoma[(unsigned int)(lionB_owner)].push_back('l');

        if(giraffeA_pos < 12)
            bstr[giraffeA_pos] = giraffeA_owner==Turn::BLACK?'g':'G';
        else 
            mochigoma[(unsigned int)(giraffeA_owner)].push_back('g');
        if(giraffeB_pos < 12)
            bstr[giraffeB_pos] = giraffeB_owner==Turn::BLACK?'g':'G';
        else
            mochigoma[(unsigned int)(giraffeB_owner)].push_back('g');


        if(elephantA_pos < 12)
            bstr[elephantA_pos] = elephantA_owner==Turn::BLACK?'e':'E';
        else 
            mochigoma[(unsigned int)(elephantA_owner)].push_back('e');
        if(elephantB_pos < 12)
            bstr[elephantB_pos] = elephantB_owner==Turn::BLACK?'e':'E';
        else
            mochigoma[(unsigned int)(elephantB_owner)].push_back('e');

        char cb = chickinA_promote ? 'h':'c';
        char cw = chickinA_promote ? 'H':'C';
        if(chickinA_pos < 12)
            bstr[chickinA_pos] = chickinA_owner==Turn::BLACK?cb:cw;
        else 
            mochigoma[(unsigned int)(chickinA_owner)].push_back(cb);
        if(chickinB_pos < 12)
            bstr[chickinB_pos] = chickinB_owner==Turn::BLACK?cb:cw;
        else
            mochigoma[(unsigned int)(chickinB_owner)].push_back(cb);

        
        printf("-------------\n");
        std::cout << mochigoma[1] << '\n';
        printf("-------------\n");
        for(int i = 0; i < 3*4; i+=3){
            printf("| %c | %c | %c |\n", bstr[i+0], bstr[i+1], bstr[i+2]);
            printf("-------------\n");
        }
        std::cout << mochigoma[0] << std::endl;
        printf("-------------\n");

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
