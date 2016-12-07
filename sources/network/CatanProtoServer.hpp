//
// Created by ed on 08.12.16.
//

#ifndef NETWORK_CATANPROTOSERVER_H
#define NETWORK_CATANPROTOSERVER_H

#include "TcpServer.hpp"

namespace Network {
	/**
	 * @brief Server which works on Catan-Protocol.
	 */
	class CatanProtoServer : public TcpServer {
		public:
			/**
			 * @brief CatanProtoServer constructor.
			 * @param port Port for listening.
			 */
			CatanProtoServer(unsigned short port);

		private:
			virtual void onConnect(connection_ptr connection);
	};
}

#endif //NETWORK_CATANPROTOSERVER_H
