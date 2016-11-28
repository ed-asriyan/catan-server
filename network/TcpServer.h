//
// Created by ed on 29.11.16.
//

#ifndef NETWORK_TCPSERVER_H
#define NETWORK_TCPSERVER_H

#include <stdexcept>

#include <boost/shared_ptr.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/asio.hpp>

namespace Network {
	using namespace boost::asio;

	typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

	/**
	 * @brief Simple TCP server.
	 */
	class TcpServer {
		private:
			unsigned short port;

		public:
			/**
			 * @brief The event that occurs when new connection is established.
			 */
			boost::signals2::signal<void(socket_ptr)> OnConnect;

			/**
			 * @brief TcpServer constructor.
			 * @param port Port for listening.
			 */
			TcpServer(unsigned short port);

			/**
			 * @brief Returns listening port.
			 * @return Listening port.
			 */
			unsigned short get_port() const;

	};
}

#endif //NETWORK_TCPSERVER_H
