#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include "common.h"

namespace AnimalEngine{
class Command{
	private:
        boost::asio::io_service io_service;
		boost::asio::ip::tcp::socket socket;
        std::string receive();
        void send(std::string const& msg);
	public:
        Command();
        Turn connect(boost::property_tree::ptree&);
        bool move(std::string const& src, std::string const& dst);
        std::string board();
        std::string board2();
        std::string initboard();
        Turn whoami();
        Turn turn();
};
};
