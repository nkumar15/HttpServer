//
// Connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection.hpp"
#include <vector>
#include <boost/bind.hpp>
#include "connection_manager.hpp"
#include "request_handler.hpp"
#include <boost/log/trivial.hpp>

namespace http {
namespace server {

Connection::Connection(boost::asio::io_service& io_service,
    ConnectionManager& manager, RequestHandler& handler)
  : socket_(io_service),
    connection_manager_(manager),
    request_handler_(handler)
{


}

boost::asio::ip::tcp::socket& Connection::Socket()
{
  return socket_;
}

void Connection::Start()
{
  socket_.async_read_some(boost::asio::buffer(buffer_),
      boost::bind(&Connection::HandleRead, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Connection::Stop()
{
  socket_.close();
}

void Connection::HandleRead(const boost::system::error_code& e,
    std::size_t bytes_transferred)
{

  if (!e)
  {
    boost::tribool result;
    boost::tie(result, boost::tuples::ignore) = request_parser_.Parse(
        request_, buffer_.data(), buffer_.data() + bytes_transferred);

    if (result)
    {
      BOOST_LOG_TRIVIAL(info) << "Ready for response";
      request_handler_.HandleRequest(request_, response_);
      boost::asio::async_write(socket_, response_.ToBuffers(),
          boost::bind(&Connection::HandleWrite, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else if (!result)
    {
      BOOST_LOG_TRIVIAL(info) << "Responding to bad request";
      response_ = Response::StockResponse(Response::Status::Bad_Request);
      boost::asio::async_write(socket_, response_.ToBuffers(),
          boost::bind(&Connection::HandleWrite, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else
    {
      BOOST_LOG_TRIVIAL(info) << "Reading request....";
      socket_.async_read_some(boost::asio::buffer(buffer_),
          boost::bind(&Connection::HandleRead, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
  }
  else if (e != boost::asio::error::operation_aborted)
  {
    connection_manager_.Stop(shared_from_this());
  }
}

void Connection::HandleWrite(const boost::system::error_code& e)
{
  if (!e)
  {
    // Initiate graceful Connection closure.
    boost::system::error_code ignored_ec;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
  }

  if (e != boost::asio::error::operation_aborted)
  {
    connection_manager_.Stop(shared_from_this());
  }
}

} // namespace server
} // namespace http
