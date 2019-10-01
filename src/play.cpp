#include "common.h"
#include "move.hpp"
#include "score.hpp"
#include "command.hpp"
#include "EngineCore.hpp"


namespace AnimalEngine{
Score evaluation(Position& pos){return static_cast<Score>(0);}

Score alpha_beta
        (
            Position& pos, Turn turn, int depth,
            Score a = Gote_win, 
            Score b = Sente_win
        )
{
    if(pos.is_tsumi(turn)){
        return static_cast<bool>(turn)? Sente_win:Gote_win;
    }
    if(depth == 0){
        return evaluation(pos);
    }
    std::vector<Position> poses = pos.gen_move(turn);
    Turn nturn = (turn==Turn::BLACK) ? Turn::WHITE: Turn::BLACK;
    for(auto&& p: poses){
        Score alpha = -alpha_beta( p, nturn, depth - 1, -b, -a);
        if( alpha >= a)
            a = alpha;
        if( a >= b)
            break;
    }
    return a;
}

void play(boost::property_tree::ptree& pt, std::string& attr){
    /* time_limit=30 */
    /* depth_limit=10 */
    /* thread=4 */
     
    auto  time_limit_opt = pt.get_optional<float>(attr+".time_limit" );
    auto depth_limit_opt = pt.get_optional<int>  (attr+".depth_limit");
    auto      thread_opt = pt.get_optional<int>  (attr+".thread"     );
    auto      ponder_opt = pt.get_optional<bool> (attr+".ponder"     );

    float  time_lim =  time_limit_opt ?  time_limit_opt.get() :    15;
    float depth_lim = depth_limit_opt ? depth_limit_opt.get() :     8;
    int  thread_num =      thread_opt ?      thread_opt.get() :     4;
    bool     ponder =      ponder_opt ?      ponder_opt.get() : false;

    Command cmd;
    Turn my_turn = cmd.connect(pt);
    /* EngineCore ai(pt, my_turn); */
    while(1) {
        while( cmd.turn() != my_turn){
            usleep(1e5);
        }
        std::cout << cmd.board() << std::endl;
        /* ai.consider(); */
    }
}

}
