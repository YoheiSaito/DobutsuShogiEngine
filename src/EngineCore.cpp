#include "EngineCore.hpp"

namespace AnimalEngine{

template<EvalType T>
Score EngineCore<T>::alpha_beta
        (
            Position& pos, Turn turn, int depth,
            Score a, Score b
        )
{
    if(pos.is_tsumi(turn)){
        return static_cast<bool>(turn)? Sente_win:Gote_win;
    }
    if(depth == 0){
        return this->evaluation(pos);
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

}
