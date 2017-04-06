//
// Response.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "response.hpp"
#include <string>
#include <boost/lexical_cast.hpp>

namespace http {
namespace server {

namespace status_strings {

const std::string ok =
  "HTTP/1.0 200 OK\r\n";
const std::string created =
  "HTTP/1.0 201 Created\r\n";
const std::string accepted =
  "HTTP/1.0 202 Accepted\r\n";
const std::string no_content =
  "HTTP/1.0 204 No Content\r\n";
const std::string multiple_choices =
  "HTTP/1.0 300 Multiple Choices\r\n";
const std::string moved_permanently =
  "HTTP/1.0 301 Moved Permanently\r\n";
const std::string moved_temporarily =
  "HTTP/1.0 302 Moved Temporarily\r\n";
const std::string not_modified =
  "HTTP/1.0 304 Not Modified\r\n";
const std::string bad_request =
  "HTTP/1.0 400 Bad Request\r\n";
const std::string unauthorized =
  "HTTP/1.0 401 Unauthorized\r\n";
const std::string forbidden =
  "HTTP/1.0 403 Forbidden\r\n";
const std::string not_found =
  "HTTP/1.0 404 Not Found\r\n";
const std::string internal_server_error =
  "HTTP/1.0 500 Internal Server Error\r\n";
const std::string not_implemented =
  "HTTP/1.0 501 Not Implemented\r\n";
const std::string bad_gateway =
  "HTTP/1.0 502 Bad Gateway\r\n";
const std::string service_unavailable =
  "HTTP/1.0 503 Service Unavailable\r\n";

boost::asio::const_buffer to_buffer(Response::Status status)
{
  switch (status)
  {
  case Response::Status::OK:
    return boost::asio::buffer(ok);
  case Response::Status::Created:
    return boost::asio::buffer(created);
  case Response::Status::Accepted:
    return boost::asio::buffer(accepted);
  case Response::Status::No_Content:
    return boost::asio::buffer(no_content);
  case Response::Status::Multiple_Choices:
    return boost::asio::buffer(multiple_choices);
  case Response::Status::Moved_Permanently:
    return boost::asio::buffer(moved_permanently);
  case Response::Status::Moved_Temporarily:
    return boost::asio::buffer(moved_temporarily);
  case Response::Status::Not_Modified:
    return boost::asio::buffer(not_modified);
  case Response::Status::Bad_Request:
    return boost::asio::buffer(bad_request);
  case Response::Status::Unauthorized:
    return boost::asio::buffer(unauthorized);
  case Response::Status::Forbidden:
    return boost::asio::buffer(forbidden);
  case Response::Status::Not_Found:
    return boost::asio::buffer(not_found);
  case Response::Status::Internal_Server_Error:
    return boost::asio::buffer(internal_server_error);
  case Response::Status::Not_Implemented:
    return boost::asio::buffer(not_implemented);
  case Response::Status::Bad_Gateway:
    return boost::asio::buffer(bad_gateway);
  case Response::Status::Service_Unavailable:
    return boost::asio::buffer(service_unavailable);
  default:
    return boost::asio::buffer(internal_server_error);
  }
}

} // namespace status_strings

namespace misc_strings {

const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

} // namespace misc_strings

std::vector<boost::asio::const_buffer> Response::ToBuffers()
{
  std::vector<boost::asio::const_buffer> buffers;
  buffers.push_back(status_strings::to_buffer(status));
  for (std::size_t i = 0; i < headers.size(); ++i)
  {
    Header& h = headers[i];
    buffers.push_back(boost::asio::buffer(h.name));
    buffers.push_back(boost::asio::buffer(misc_strings::name_value_separator));
    buffers.push_back(boost::asio::buffer(h.value));
    buffers.push_back(boost::asio::buffer(misc_strings::crlf));
  }
  buffers.push_back(boost::asio::buffer(misc_strings::crlf));
  buffers.push_back(boost::asio::buffer(content));
  return buffers;
}

namespace stock_replies {

const char ok[] = "";
const char created[] =
  "<html>"
  "<head><title>Created</title></head>"
  "<body><h1>201 Created</h1></body>"
  "</html>";
const char accepted[] =
  "<html>"
  "<head><title>Accepted</title></head>"
  "<body><h1>202 Accepted</h1></body>"
  "</html>";
const char no_content[] =
  "<html>"
  "<head><title>No Content</title></head>"
  "<body><h1>204 Content</h1></body>"
  "</html>";
const char multiple_choices[] =
  "<html>"
  "<head><title>Multiple Choices</title></head>"
  "<body><h1>300 Multiple Choices</h1></body>"
  "</html>";
const char moved_permanently[] =
  "<html>"
  "<head><title>Moved Permanently</title></head>"
  "<body><h1>301 Moved Permanently</h1></body>"
  "</html>";
const char moved_temporarily[] =
  "<html>"
  "<head><title>Moved Temporarily</title></head>"
  "<body><h1>302 Moved Temporarily</h1></body>"
  "</html>";
const char not_modified[] =
  "<html>"
  "<head><title>Not Modified</title></head>"
  "<body><h1>304 Not Modified</h1></body>"
  "</html>";
const char bad_request[] =
  "<html>"
  "<head><title>Bad Request</title></head>"
  "<body><h1>400 Bad Request</h1></body>"
  "</html>";
const char unauthorized[] =
  "<html>"
  "<head><title>Unauthorized</title></head>"
  "<body><h1>401 Unauthorized</h1></body>"
  "</html>";
const char forbidden[] =
  "<html>"
  "<head><title>Forbidden</title></head>"
  "<body><h1>403 Forbidden</h1></body>"
  "</html>";
const char not_found[] =
  "<html>"
  "<head><title>Not Found</title></head>"
  "<body><h1>404 Not Found</h1></body>"
  "</html>";
const char internal_server_error[] =
  "<html>"
  "<head><title>Internal Server Error</title></head>"
  "<body><h1>500 Internal Server Error</h1></body>"
  "</html>";
const char not_implemented[] =
  "<html>"
  "<head><title>Not Implemented</title></head>"
  "<body><h1>501 Not Implemented</h1></body>"
  "</html>";
const char bad_gateway[] =
  "<html>"
  "<head><title>Bad Gateway</title></head>"
  "<body><h1>502 Bad Gateway</h1></body>"
  "</html>";
const char service_unavailable[] =
  "<html>"
  "<head><title>Service Unavailable</title></head>"
  "<body><h1>503 Service Unavailable</h1></body>"
  "</html>";

std::string to_string(Response::Status status)
{
  switch (status)
  {
  case Response::Status::OK:
    return ok;
  case Response::Status::Created:
    return created;
  case Response::Status::Accepted:
    return accepted;
  case Response::Status::No_Content:
    return no_content;
  case Response::Status::Multiple_Choices:
    return multiple_choices;
  case Response::Status::Moved_Permanently:
    return moved_permanently;
  case Response::Status::Moved_Temporarily:
    return moved_temporarily;
  case Response::Status::Not_Modified:
    return not_modified;
  case Response::Status::Bad_Request:
    return bad_request;
  case Response::Status::Unauthorized:
    return unauthorized;
  case Response::Status::Forbidden:
    return forbidden;
  case Response::Status::Not_Found:
    return not_found;
  case Response::Status::Internal_Server_Error:
    return internal_server_error;
  case Response::Status::Not_Implemented:
    return not_implemented;
  case Response::Status::Bad_Gateway:
    return bad_gateway;
  case Response::Status::Service_Unavailable:
    return service_unavailable;
  default:
    return internal_server_error;
  }
}

} // namespace stock_replies

Response Response::StockResponse(Response::Status status)
{
  Response rep;
  rep.status = status;
  rep.content = stock_replies::to_string(status);
  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "text/html";
  return rep;
}

} // namespace server
} // namespace http
