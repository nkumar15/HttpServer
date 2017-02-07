//
// RequestHandler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "mime_types.hpp"
#include "response.hpp"
#include "request.hpp"
#include "iostream"
#include <boost/log/trivial.hpp>

namespace http {
namespace server {

RequestHandler::RequestHandler()
  : doc_root_(".")
{
}

void RequestHandler::HandleRequest(const Request& req, Response& resp)
{
  // Decode url to path.
  std::string request_path;
  if (!UrlDecode(req.uri, request_path))
  {
    BOOST_LOG_TRIVIAL(info) << "No request path found";
    resp = Response::StockResponse(Response::Status::Bad_Request);
    return;
  }

  BOOST_LOG_TRIVIAL(info) << "Request path found " << request_path;
  // Request path must be absolute and not contain "..".
  if (request_path.empty() || request_path[0] != '/'
      || request_path.find("..") != std::string::npos)
  {
    resp = Response::StockResponse(Response::Status::Bad_Request);
    return;
  }

  // If path ends in slash (i.e. is a directory) then add "index.html".
  if (request_path[request_path.size() - 1] == '/')
  {
    request_path += "index.html";
  }

  BOOST_LOG_TRIVIAL(info) << "Resource for request path " << request_path;
  // Determine the file extension.
  std::size_t last_slash_pos = request_path.find_last_of("/");
  std::size_t last_dot_pos = request_path.find_last_of(".");
  std::string extension;
  if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
  {
    extension = request_path.substr(last_dot_pos + 1);
  }

  // Open the file to send back.
  std::string full_path = doc_root_ + request_path;
  BOOST_LOG_TRIVIAL(info) << "Full path of resource to read " << full_path;
  std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
  if (!is)
  {
    resp = Response::StockResponse(Response::Status::Not_Found);
    return;
  }

  // Fill out the Response to be sent to the client.
  resp.status = Response::Status::OK;
  char buf[512];
  while (is.read(buf, sizeof(buf)).gcount() > 0)
    resp.content.append(buf, is.gcount());
  resp.headers.resize(2);
  resp.headers[0].name = "Content-Length";
  resp.headers[0].value = boost::lexical_cast<std::string>(resp.content.size());
  resp.headers[1].name = "Content-Type";
  resp.headers[1].value = mime_types::extension_to_type(extension);
}

bool RequestHandler::UrlDecode(const std::string& in, std::string& out)
{
  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value = 0;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  return true;
}

} // namespace server
} // namespace http
