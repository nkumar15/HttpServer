#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <boost/noncopyable.hpp>
#include "connection.hpp"
#include "connection_manager.hpp"
#include "request_handler.hpp"

namespace http {
namespace server {

/// The top-level class of the HTTP Server.
class Server
  : private boost::noncopyable
{
public:
  /// Construct the Server to listen on the specified TCP address and port, and
  /// serve up files from the given directory.
  explicit Server(const std::string& address, const std::string& port);

  /// Run the Server's io_service loop.
  void Run();

private:
  /// Initiate an asynchronous accept operation.
  void StartAccept();

  /// Handle completion of an asynchronous accept operation.
  void HandleAccept(const boost::system::error_code& e);

  /// Handle a request to stop the Server.
  void HandleStop();

  /// The io_service used to perform asynchronous operations.
  boost::asio::io_service io_service_;

  /// The signal_set is used to register for process termination notifications.
  boost::asio::signal_set signals_;

  /// Acceptor used to listen for incoming connections.
  boost::asio::ip::tcp::acceptor acceptor_;

  /// The connection manager which owns all live connections.
  ConnectionManager connection_manager_;

  /// The next connection to be accepted.
  ConnectionPtr new_connection_;

  /// The handler for all incoming requests.
  RequestHandler request_handler_;
};

} // namespace Server
} // namespace http

#endif // HTTP_SERVER_HPP
