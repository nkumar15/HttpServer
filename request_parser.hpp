//
// request_parser.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_PARSER_HPP
#define HTTP_REQUEST_PARSER_HPP

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

namespace http {
namespace server {

struct Request;

/// Parser for incoming requests.
class RequestParser
{
public:
  /// Construct ready to parse the request method.
  RequestParser();

  /// Reset to initial parser state.
  void Reset();

  /// Parse some data. The tribool return value is true when a complete request
  /// has been parsed, false if the data is invalid, indeterminate when more
  /// data is required. The InputIterator return value indicates how much of the
  /// input has been consumed.
  template <typename InputIterator>
  boost::tuple<boost::tribool, InputIterator> Parse(Request& req,
      InputIterator begin, InputIterator end)
  {
    while (begin != end)
    {
      boost::tribool result = Consume(req, *begin++);
      if (result || !result)
        return boost::make_tuple(result, begin);
    }
    boost::tribool result = boost::indeterminate;
    return boost::make_tuple(result, begin);
  }

private:
  /// Handle the next character of input.
  boost::tribool Consume(Request& req, char input);

  /// Check if a byte is an HTTP character.
  static bool IsChar(int c);

  /// Check if a byte is an HTTP control character.
  static bool IsCtl(int c);

  /// Check if a byte is defined as an HTTP tspecial character.
  static bool IsTSpecial(int c);

  /// Check if a byte is a digit.
  static bool IsDigit(int c);

  /// The current state of the parser.
  enum class ParserState
  {
    Method_Start,
    Method,
    URI,
    Http_Version_H,
    Http_Version_T_1,
    Http_Version_T_2,
    Http_Version_P,
    Http_Version_Slash,
    Http_Version_Major_Start,
    Http_Version_Major,
    Http_Version_Minor_Start,
    Http_Version_Minor,
    Expecting_Newline_1,
    Header_Line_Start,
    Header_LWS,
    Header_Name,
    Space_Before_Header_Value,
    Header_Value,
    Expecting_Newline_2,
    Expecting_Newline_3
  } state_;
};

} // namespace server
} // namespace http

#endif // HTTP_REQUEST_PARSER_HPP
