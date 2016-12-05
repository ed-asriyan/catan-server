//
// Created by ed on 30.11.16.
//

#ifndef NETWORK_TCPCONNECTION_H
#define NETWORK_TCPCONNECTION_H

#include <stdexcept>
#include <boost/asio.hpp>
#include <boost/asio/read_until.hpp>

namespace Network {
	using namespace boost::asio;

	class TcpConnection;

	typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

	typedef boost::shared_ptr<TcpConnection> connection_ptr;

	/**
	 * @brief TCP connection to the client.
	 *
	 * Simple TCP connection to the client. Provides methods to send/receive strings.
	 */
	class TcpConnection {
		private:
			socket_ptr socket;

		public:
			/**
			 * @brief Constructor.
			 * @param socket Socket connected to the client.
			 */
			TcpConnection(socket_ptr socket);

			/**
			 * @brief Synchronously send string to the client.
			 * @param string String to send.
			 */
			void send(const std::string& string);

			/**
			 * @brief Synchronously receives string from the connected client.
			 * @return Received string.
			 */
			std::string receive();

			/**
			 * @brief Returns remote ip address.
			 * @return Remote ip address.
			 */
			std::string get_remote_ip() const;

			/**
			 * @brief Returns local ip address.
			 * @returns Local ip address.
			 */
			std::string get_local_ip() const;
	};
}

#endif //NETWORK_TCPCONNECTION_H
