#ifndef  ENGINE_CORE_HPP
#define  ENGINE_CORE_HPP

#include "common.h"
#include "score.hpp"
#include "position.hpp"
#include "move.hpp"
#include "evaluation.hpp"

namespace AnimalEngine{
template<EvalType EvalT>
struct EngineCore{
    Turn my_turn;
    float time_lim;
    int  depth_lim;
    int thread_lim;
    bool    ponder;
    Evaluation<EvalT> evaluation;
    EngineCore (boost::property_tree::ptree& pt, Turn mytrn,std::string& attr)
        : my_turn(mytrn)
        , evaluation(pt)
    {

        float  time_default = pt.get<float>("Common.time_limit"  );
        int   depth_default = pt.get< int >("Common.depth_limit" );
        int  thread_default = pt.get< int >("Common.thread_limit");
        bool ponder_default = pt.get<bool >("Common.ponder"      );

        auto  time_limit_opt = pt.get_optional<float>(attr+".time_limit"  );
        auto depth_limit_opt = pt.get_optional< int >(attr+".depth_limit" );
        auto      thread_opt = pt.get_optional< int >(attr+".thread_limit");
        auto      ponder_opt = pt.get_optional<bool >(attr+".ponder"      );

        time_lim   =  time_limit_opt ?  time_limit_opt.get() :   time_default;
        depth_lim  = depth_limit_opt ? depth_limit_opt.get() :  depth_default;
        thread_lim =      thread_opt ?      thread_opt.get() : thread_default;
        ponder     =      ponder_opt ?      ponder_opt.get() : ponder_default;
    }
    Move consider(){
        Move s;
        s.src = A1;
        s.dst = A1;
        return s;
    }
    Score alpha_beta (Position&,Turn,int,Score a=Gote_win,Score b=Sente_win);

};
}
#endif //ENGINE_CORE_HPP
