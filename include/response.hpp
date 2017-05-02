//
// Response.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REPLY_HPP
#define HTTP_REPLY_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "header.hpp"

namespace http {
namespace server {

/// A Response to be sent to a client.
struct Response
{
  /// The status of the Response.
  enum class Status
  {
    OK = 200,
    Created = 201,
    Accepted = 202,
    No_Content = 204,
    Multiple_Choices = 300,
    Moved_Permanently = 301,
    Moved_Temporarily = 302,
    Not_Modified = 304,
    Bad_Request = 400,
    Unauthorized = 401,
    Forbidden = 403,
    Not_Found = 404,
    Internal_Server_Error = 500,
    Not_Implemented = 501,
    Bad_Gateway = 502,
    Service_Unavailable = 503
  };

  Status status;
  /// The headers to be included in the Response.
  std::vector<Header> headers;

  /// The content to be sent in the Response.
  std::string content;

  /// Convert the Response into a vector of buffers. The buffers do not own the
  /// underlying memory blocks, therefore the Response object must remain valid and
  /// not be changed until the write operation has completed.
  std::vector<boost::asio::const_buffer> ToBuffers();

  /// Get a stock Response.
  static Response StockResponse(Response::Status status);
};

} // namespace server
} // namespace http

#endif // HTTP_REPLY_HPP
