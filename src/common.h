#ifndef COMMON_H
#define COMMON_H

// original

// other thirdparty

// boost
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

// stl
#include <iostream>
#include <random>
#include <memory>
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

// c header

namespace AnimalEngine {
    void learn(boost::property_tree::ptree&, std::string);
    void teach(boost::property_tree::ptree&, std::string);
    void play (boost::property_tree::ptree&, std::string);
    void test (boost::property_tree::ptree&, std::string);
}

#endif  //COMMON_H
