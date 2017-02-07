//
// RequestParser.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_parser.hpp"
#include "request.hpp"

namespace http {
namespace server {

RequestParser::RequestParser()
  : state_(ParserState::Method_Start)
{
}

void RequestParser::Reset()
{
  state_ = ParserState::Method_Start;
}

boost::tribool RequestParser::Consume(Request& req, char input)
{
  switch (state_)
  {
  case ParserState::Method_Start:
    if (!IsChar(input) || IsCtl(input) || IsTSpecial(input))
    {
      return false;
    }
    else
    {
      state_ = ParserState::Method;
      req.method.push_back(input);
      return boost::indeterminate;
    }
  case ParserState::Method:
    if (input == ' ')
    {
      state_ = ParserState::URI;
      return boost::indeterminate;
    }
    else if (!IsChar(input) || IsCtl(input) || IsTSpecial(input))
    {
      return false;
    }
    else
    {
      req.method.push_back(input);
      return boost::indeterminate;
    }
  case ParserState::URI:
    if (input == ' ')
    {
      state_ = ParserState::Http_Version_H;
      return boost::indeterminate;
    }
    else if (IsCtl(input))
    {
      return false;
    }
    else
    {
      req.uri.push_back(input);
      return boost::indeterminate;
    }
  case ParserState::Http_Version_H:
    if (input == 'H')
    {
      state_ = ParserState::Http_Version_T_1;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Http_Version_T_1:
    if (input == 'T')
    {
      state_ = ParserState::Http_Version_T_2;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Http_Version_T_2:
    if (input == 'T')
    {
      state_ = ParserState::Http_Version_P;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Http_Version_P:
    if (input == 'P')
    {
      state_ = ParserState::Http_Version_Slash;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Http_Version_Slash:
    if (input == '/')
    {
      req.http_version_major = 0;
      req.http_version_minor = 0;
      state_ = ParserState::Http_Version_Major_Start;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Http_Version_Major_Start:
    if (IsDigit(input))
    {
      req.http_version_major = req.http_version_major * 10 + input - '0';
      state_ = ParserState::Http_Version_Major;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Http_Version_Major:
    if (input == '.')
    {
      state_ = ParserState::Http_Version_Minor_Start;
      return boost::indeterminate;
    }
    else if (IsDigit(input))
    {
      req.http_version_major = req.http_version_major * 10 + input - '0';
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Http_Version_Minor_Start:
    if (IsDigit(input))
    {
      req.http_version_minor = req.http_version_minor * 10 + input - '0';
      state_ = ParserState::Http_Version_Minor;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Http_Version_Minor:
    if (input == '\r')
    {
      state_ = ParserState::Expecting_Newline_1;
      return boost::indeterminate;
    }
    else if (IsDigit(input))
    {
      req.http_version_minor = req.http_version_minor * 10 + input - '0';
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Expecting_Newline_1:
    if (input == '\n')
    {
      state_ = ParserState::Header_Line_Start;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Header_Line_Start:
    if (input == '\r')
    {
      state_ = ParserState::Expecting_Newline_3;
      return boost::indeterminate;
    }
    else if (!req.headers.empty() && (input == ' ' || input == '\t'))
    {
      state_ = ParserState::Header_LWS;
      return boost::indeterminate;
    }
    else if (!IsChar(input) || IsCtl(input) || IsTSpecial(input))
    {
      return false;
    }
    else
    {
      req.headers.push_back(Header());
      req.headers.back().name.push_back(input);
      state_ = ParserState::Header_Name;
      return boost::indeterminate;
    }
  case ParserState::Header_LWS:
    if (input == '\r')
    {
      state_ = ParserState::Expecting_Newline_2;
      return boost::indeterminate;
    }
    else if (input == ' ' || input == '\t')
    {
      return boost::indeterminate;
    }
    else if (IsCtl(input))
    {
      return false;
    }
    else
    {
      state_ = ParserState::Header_Value;
      req.headers.back().value.push_back(input);
      return boost::indeterminate;
    }
  case ParserState::Header_Name:
    if (input == ':')
    {
      state_ = ParserState::Space_Before_Header_Value;
      return boost::indeterminate;
    }
    else if (!IsChar(input) || IsCtl(input) || IsTSpecial(input))
    {
      return false;
    }
    else
    {
      req.headers.back().name.push_back(input);
      return boost::indeterminate;
    }
  case ParserState::Space_Before_Header_Value:
    if (input == ' ')
    {
      state_ = ParserState::Header_Value;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Header_Value:
    if (input == '\r')
    {
      state_ = ParserState::Expecting_Newline_2;
      return boost::indeterminate;
    }
    else if (IsCtl(input))
    {
      return false;
    }
    else
    {
      req.headers.back().value.push_back(input);
      return boost::indeterminate;
    }
  case ParserState::Expecting_Newline_2:
    if (input == '\n')
    {
      state_ = ParserState::Header_Line_Start;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case ParserState::Expecting_Newline_3:
    return (input == '\n');
  default:
    return false;
  }
}

bool RequestParser::IsChar(int c)
{
  return c >= 0 && c <= 127;
}

bool RequestParser::IsCtl(int c)
{
  return (c >= 0 && c <= 31) || (c == 127);
}

bool RequestParser::IsTSpecial(int c)
{
  switch (c)
  {
  case '(': case ')': case '<': case '>': case '@':
  case ',': case ';': case ':': case '\\': case '"':
  case '/': case '[': case ']': case '?': case '=':
  case '{': case '}': case ' ': case '\t':
    return true;
  default:
    return false;
  }
}

bool RequestParser::IsDigit(int c)
{
  return c >= '0' && c <= '9';
}

} // namespace server
} // namespace http
