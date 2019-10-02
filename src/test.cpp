#include "common.h"
#include "EngineCore.hpp"
namespace AnimalEngine{

template <EvalType Ta, EvalType Tb>
void SelfPlay(boost::property_tree::ptree& pt){
    std::string atr_black("SelfPlayBlack");
    std::string atr_white("SelfPlayWhtie");
    EngineCore<Ta> black(pt, Turn::BLACK, atr_black);
    EngineCore<Tb> white(pt, Turn::WHITE, atr_white);
    black.ponder = false;
    white.ponder = false;
    Position board = Position::initial_position();
    try{
        while(1){
            {
                board.print();
                auto mv = black.consider();
                board = board.move(mv);
            }{
                board.print();
                auto mv = white.consider();
                board = board.move(mv);
                throw Turn::BLACK;
            }

        }
    }catch (Turn t){
        std::cout 
            << (t==Turn::BLACK?(u8"先"):(u8"後") )
            << u8"手番が投了しました"<< std::endl;
    }
};

void test(boost::property_tree::ptree& pt, std::string& attr){
    // do module test

    // selfplay test
    SelfPlay<StaticKomawari, StaticKomawari>(pt);
    
}
}
