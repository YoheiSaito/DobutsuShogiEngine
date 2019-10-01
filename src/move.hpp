#ifndef  MOVE_HPP
#define  MOVE_HPP
#include "common.h"
#include "position.hpp"
namespace AnimalEngine{

static const std::string move_to_str[16] = {
    "A1", "B1", "C1",
    "A2", "B2", "C2",
    "A3", "B3", "C3",
    "A4", "B4", "C4",
    "Mc", "Ml", "Me", "Mg" 
};
using MoveString = std::tuple<std::string, std::string>;
struct Move{
    union {
        uint8_t as_byte;
        struct {
            uint8_t src:4;
            uint8_t dst:4;
        };
    };
     MoveString mv_str( std::string& raw_board, Turn t) {
        std::string source      (move_to_str[src]);
        std::string destination (move_to_str[dst]);
        if(src >= 12){
            std::string r;
            if(t == Turn::BLACK)
                r = "D";
            else
                r = "E";

            const std::regex m_to("M");
            source = std::regex_replace( source, m_to, r);
            // Dc, Dl, De, Dg  || Ec, El, Ed, Eg
            const std::regex f_row(r+"\\d*"+source[1]);
            std::smatch m;
            std::regex_search(raw_board, m,f_row);
            exit(-1);
            /* std::static_assert(false, "not implemented"); */
            std::vector<char> c;
            
        }
        return std::make_tuple(source, destination);
    }
};
using Moves = std::vector<Move>;
}
#endif //MOVE_HPP
