#ifndef HTTP_CONNECTION_HPP
#define HTTP_CONNECTION_HPP

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "response.hpp"
#include "request.hpp"
#include "request_handler.hpp"
#include "request_parser.hpp"

namespace http {
namespace server {

class Connection : Common::Uncopyable {

  public:
    explicit Connection(boost::asio::ip::tcp::socket socket,
        ConnectionManager& connection_mgr, request_handler& handler);

    void start();

    void stop();
  
  private:
    void do_read();
	void do_write();
	
	boost::asio::ip::tcp::socket m_socket;
	ConnectionManager&           m_connection_mgr;
	request_handler&             m_request_handler;
	std::array<char,8192>        m_buffer;
	request                      m_request;
	request_parser               m_request_parser;
	response                     m_response;
};

typedef std::shared_ptr<Connection> ConnectionPointer;

}  // namespace server
} // namespace http

#endif


