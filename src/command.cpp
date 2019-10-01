#include <unistd.h>
#include <regex>
#include "command.hpp"

namespace asio = boost::asio;
using asio::ip::tcp;

namespace AnimalEngine{

	Command::Command():
		socket(io_service)
	{
	}
	Turn Command::connect(boost::property_tree::ptree& pt){

        auto ip_opt   = pt.get_optional<std::string>("Common.ip");
        auto port_opt = pt.get_optional<int>("Common.port");
        std::string ip(ip_opt?ip_opt.get():"127.0.0.1");
        int port((port_opt)? port_opt.get():4444);

		boost::system::error_code error;

		socket.connect(
            tcp::endpoint(asio::ip::address::from_string(ip.c_str()), port), 
			error
		);

		if (error) {
			throw error.message();
		} std::string t = receive();
		std::regex player1(".*Player1.*");
		std::regex player2(".*Player2.*");
		if( std::regex_search( t, player1)){
			return Turn::BLACK;
		}
		else if( std::regex_search( t, player2)){
			return Turn::WHITE;
		}
		std::cerr <<"undefined player" << std::endl;
        exit(-1);

	}
	std::string Command::receive(){
		boost::system::error_code error;
		asio::streambuf receive_buffer;

		asio::read(
			socket, receive_buffer, 
			asio::transfer_at_least(4), error
		);

		const char* data = 
			asio::buffer_cast<const char*>(receive_buffer.data());
		if (error && error != asio::error::eof) {
			std::cerr 
				<< "receive failed: " 
				<< error.message() 
				<< std::endl;
			throw error.message();
		}
		else {
			return std::string(data);
		}
	}
	void Command::send(std::string const& msg){
		boost::system::error_code error;
		asio::write(socket, asio::buffer(msg+"\n"), error);
		if (error) {
			throw error.message();
		}
	}
	bool Command::move(std::string const& src, std::string const& dst){
		std::regex moved(".*moved.*");
		send("mv "+src+" "+dst);
		usleep(1e5);
		std::string rec = receive();
		if( std::regex_search(rec, moved))
			return true;
		else{
			return false;
		}
	}

	std::string Command::board(){
		send("board");
		usleep(1e5);
		return receive();
	}
	std::string Command::board2(){
		send("board");
		usleep(1e5);
		return receive();
	}
	std::string Command::initboard(){
		send("initboard");
		usleep(1e5);
		return receive();

	}
	Turn Command::whoami(){
		std::regex player1(".*Player1.*");
		std::regex player2(".*Player2.*");
		send("whoami");
		usleep(1e5);
		std::string who = receive();
		if( std::regex_search( who, player1)){
			return Turn::BLACK;
		}
		else if( std::regex_search( who, player2)){
			return Turn::WHITE;
		}
        std::cerr << "undefined player" << std::endl;
        exit(-1);
	}

	Turn Command::turn(){
		std::regex player1(".*Player1.*");
		std::regex player2(".*Player2.*");
		send("turn");
		usleep(1e5);
		std::string t = receive();
		if( std::regex_search( t, player1)){
			return Turn::BLACK;
		}
		else if( std::regex_search( t, player2)){
			return Turn::WHITE;
		}
        std::cerr << "undefined player" << std::endl;
        exit(-1);
	}

} // teyo_shogi
