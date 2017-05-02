//
// Connection.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_CONNECTION_HPP
#define HTTP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "response.hpp"
#include "request.hpp"
#include "request_handler.hpp"
#include "request_parser.hpp"

namespace http {
namespace server {

class ConnectionManager;

/// Represents a single Connection from a client.
class Connection
  : public boost::enable_shared_from_this<Connection>,
    private boost::noncopyable
{
public:
  /// Construct a Connection with the given io_service.
  explicit Connection(boost::asio::io_service& io_service,
      ConnectionManager& manager, RequestHandler& handler);

  /// Get the socket associated with the Connection.
  boost::asio::ip::tcp::socket& Socket();

  /// Start the first asynchronous operation for the Connection.
  void Start();

  /// Stop all asynchronous operations associated with the Connection.
  void Stop();

private:
  /// Handle completion of a read operation.
  void HandleRead(const boost::system::error_code& e,
      std::size_t bytes_transferred);

  /// Handle completion of a write operation.
  void HandleWrite(const boost::system::error_code& e);

  /// Socket for the Connection.
  boost::asio::ip::tcp::socket socket_;

  /// The manager for this Connection.
  ConnectionManager& connection_manager_;

  /// The handler used to process the incoming request.
  RequestHandler& request_handler_;

  /// Buffer for incoming data.
  boost::array<char, 8192> buffer_;

  /// The incoming request.
  Request request_;

  /// The parser for the incoming request.
  RequestParser request_parser_;

  /// The reply to be sent back to the client.
  Response response_;
};

typedef boost::shared_ptr<Connection> ConnectionPtr;

} // namespace server
} // namespace http

#endif // HTTP_CONNECTION_HPP
