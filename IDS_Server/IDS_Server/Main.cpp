#include <iostream>
#include <boost/asio.hpp> //Used for networking, make sure to have boost library properly installed and configuredfor this project!
#include <vector>
#include <string>

//using namespace std;

void updateScreen();
std::string generateMessage();

using boost::asio::ip::tcp;
static int PORT_NUMBER = 23456;

int main()
{
	try
	{
		boost::asio::io_service io_service;

		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), PORT_NUMBER));

		for (;;)
		{
			tcp::socket socket(io_service);
			acceptor.accept(socket);

			std::string message = generateMessage();

			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}