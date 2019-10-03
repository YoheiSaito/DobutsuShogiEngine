#ifndef EVALUATION_HPP
#define EVALUATION_HPP
#include "score.hpp"
#include "position.hpp"

namespace AnimalEngine {

enum EvalType{ 
    StaticKomawari, 
    DynamicKomawari , 
    Naural, 
    StaticSettai, 
    DynamicSettai,
    NauralSettai
};

template<EvalType E>
struct Evaluation {
    /* static_assert(false, "Evaluation operator is not implemented."); */
};

template<>
struct Evaluation<StaticKomawari> {
    Eigen::Matrix <float, 5, 1> stc_komawari;
    Evaluation(boost::property_tree::ptree& pt){
        static float ck = pt.get<float>("Common.default_chick");
        static float ci = pt.get<float>("Common.default_chickin");
        static float el = pt.get<float>("Common.default_elephant");
        static float gr = pt.get<float>("Common.default_giraffe");
        static float kn = 2.5 * (ck + ci + el + gr);
        stc_komawari << ck, ci, el, gr, kn;
    }
 
    Score operator()(Position& p, Turn t){
        Eigen::Matrix<float, 5, 1> b;
    }

};

}

#endif
