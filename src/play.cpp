#include "common.h"
#include "move.hpp"
#include "score.hpp"
#include "command.hpp"
#include "EngineCore.hpp"

namespace AnimalEngine{
void play(boost::property_tree::ptree& pt, std::string& attr){
    Command cmd;
    Turn my_turn = WHITE;
    try{
        my_turn = cmd.connect(pt);
    }catch(...){
        std::cerr << "!!! Connection Error !!!"<< std::endl;
        exit(-1);
    }
    EngineCore<StaticKomawari> ai(pt, my_turn, attr);
    while(1) {
        while( cmd.turn() != my_turn){
            usleep(1e5);
        }
        std::cout << cmd.board() << std::endl;
        /* ai.consider(); */
    }
}

}
