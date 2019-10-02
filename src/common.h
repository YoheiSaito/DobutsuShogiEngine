#ifndef COMMON_H
#define COMMON_H

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
#include <optional>

namespace AnimalEngine {
    enum Turn : bool {
        BLACK=false,
        WHITE=true
    };
    enum PositionIndex{
        A1 = 0, B1, C1,
        A2, B2, C2,
        A3, B3, C3,
        A4, B4, C4,
        Mc, Ml, Me, Mg
    };

    void learn(boost::property_tree::ptree&, std::string&);
    void teach(boost::property_tree::ptree&, std::string&);
    void play (boost::property_tree::ptree&, std::string&);
    void test (boost::property_tree::ptree&, std::string&);
}

#endif  //COMMON_H
