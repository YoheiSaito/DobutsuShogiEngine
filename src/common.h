#ifndef COMMON_H
#define COMMON_H
#define EXTERNAL_STRING(x) #x
#define TEST_ASSERT(A) \
    if( !(A) ){ \
        std::cout  << u8"❎" << \
        " - file = " <<__FILE__ << \
        " - line = " <<__LINE__ << \
        " \ttest failed" << std::endl;\
    }else{ \
        std::cout << u8"✔" << \
        " - file = " <<__FILE__ << \
        " - line = " <<__LINE__ << \
        " \ttest success" << std::endl;\
    }

// original

// other thirdparty
#include <Eigen/Dense>

// boost
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

// stl
#include <iostream>
#include <random>
#include <memory>
#include <regex>
#include <algorithm>
#include <tuple>
#include <iterator>
#include <list>
#include <vector>
#include <array>
#include <string>
#include <map>
#include <unordered_map>
#include <limits>
/* #include <experimental/optional> */

namespace AnimalEngine {
    enum struct EngineMode:int{ Learn = 0, Teach, Play, Test };
    enum Turn : bool {
        BLACK=false,
        WHITE=true
    };
    using Owner = Turn;
    enum PositionIndex{
        A1 = 0, B1, C1,
        A2, B2, C2,
        A3, B3, C3,
        A4, B4, C4,
        OB = 12, OB_CHICKIN = 12,
        OB_LION, OB_ELEPHANT, OB_GIRAFFE
            
    };

    void learn(boost::property_tree::ptree&, std::string&);
    void teach(boost::property_tree::ptree&, std::string&);
    void play (boost::property_tree::ptree&, std::string&);
    void test (boost::property_tree::ptree&, std::string&);
}

#endif  //COMMON_H
