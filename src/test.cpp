#include "common.h"
#include "EngineCore.hpp"
namespace AnimalEngine{

template <EvalType Ta, EvalType Tb>
void SelfPlay(boost::property_tree::ptree& pt, bool view){
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
                if(view)
                    std::cout << board() << std::endl;
                auto mv = black.consider();
                board = board.move(mv, BLACK);
            }{
                if(view)
                    std::cout << board() << std::endl;
                auto mv = white.consider();
                board = board.move(mv, WHITE);
                throw Turn::WHITE;
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
    auto modtest = pt.get_optional<bool>(attr+".module_test");
    if(modtest && modtest.get()){
        Position::test();
    }
    // selfplay test
    auto selfplay_test  = pt.get_optional<bool>(attr+".selfplay_test");
    auto play_view = pt.get_optional<bool>(attr+".view");
    bool view = play_view ? play_view.get(): false;
    
    if( selfplay_test && selfplay_test.get() ) {
        auto eval = pt.get_optional<std::string>(attr+".eval");
        std::string eval_str = eval ? eval.get() : "StaticKomawari";
        std::map <std::string, int>case_match = {
            {"StaticKomawari", 0}, {"DynamicKomawari", 1},
            {"Neural", 2}, {"Settai", 3},
        };
        switch(case_match[eval_str]){
            case 1:
            /* SelfPlay<StaticKomawari, StaticKomawari>(pt, view); */
            /* break; */
            case 2:
            /* SelfPlay<StaticKomawari, StaticKomawari>(pt, view); */
            /* break; */
            case 3:
            /* SelfPlay<StaticKomawari, StaticKomawari>(pt, view); */
            /* break; */
            case 0:
            default:
            SelfPlay<StaticKomawari, StaticKomawari>(pt, view);
            break;
        }
    }
}
}
