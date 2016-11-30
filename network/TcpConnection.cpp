//
// Created by ed on 30.11.16.
//

#include "TcpConnection.h"

Network::TcpConnection::TcpConnection(Network::socket_ptr socket) : socket(socket) {
	if (socket == nullptr) throw std::invalid_argument("Socket is nullptr.");
}

void Network::TcpConnection::send(const std::string& string) {
	auto data = string.c_str();

	socket->write_some(boost::asio::buffer(data, sizeof(*data) * (string.length() + 1)));
}

std::string Network::TcpConnection::receive() {
	streambuf buffer;
	boost::asio::read_until(*socket, buffer, '\0');

	return std::string(std::istreambuf_iterator<char>(&buffer), std::istreambuf_iterator<char>());
}
