#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
#include <cerrno>
#include "connection.h"
#include "constants.h"
#include "msg.pb.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

__asm__(".symver realpath,realpath@GLIBC_2.32.4");

class ConnectionManager{
	private:
		static const unsigned int MAX_CONNECTIONS = 40;
		unsigned int nConnections_;

		Connection connections_[ConnectionManager::MAX_CONNECTIONS];		
		
		int threadCount_;

	public:
		boost::thread_group threads_;
		ConnectionManager();
		~ConnectionManager();
		void Setup(unsigned short minPort, unsigned short numPorts);
		void CreateThreads();
		void New(int port);
		static void Accept(Connection & c);
		void Run();
		static void ReadFile(Connection & c);
		void CloseAll();
		static void Error(const char * msg);
};

#endif
