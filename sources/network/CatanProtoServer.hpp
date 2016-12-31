//
// Created by ed on 08.12.16.
//

#ifndef NETWORK_CATANPROTOSERVER_H
#define NETWORK_CATANPROTOSERVER_H

#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "TcpServer.hpp"
#include "CatanRequest.hpp"

namespace Network {
	using namespace boost::property_tree;

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

		protected:
			virtual ptree onRequest(const CatanRequest& request) = 0;

		private:
			virtual void onConnect(connection_ptr connection) final;
	};
}

#endif //NETWORK_CATANPROTOSERVER_H
