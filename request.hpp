#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include<iostream>
#include "uri.hpp"
#include "headers.hpp"
#include "body.hpp"

namespace http {
namespace server {

class Request :: public Common::Uncopyable {

  public:
    Request();

    std::string GetMethod();
    void SetMethod(const std::string method);

    Uri GetUri();
    void SetUri(const Uri uri);

    std::string GetProtocol();
    void SetProtocol(const std::string protocol);

    std::string GetVersion();
    void SetVersion(const std::string version);

    void SetHost(const std::string host);
    std::string GetHost();

    void SetPort(unsigned int port); 
    unsigned int GetPort();

    Headers GetHeader();
    void SetHeader(const std::string key, const std::string value);
    void GetHeader(const std::string key);

    void SetBody(const Body body);
    Body GetBody();

  private:
    std::string m_method;
    Uri         m_uri;
    std::string m_protocol;
    std::string m_version;
    Headers     m_headers;
    Body        m_body;
};

} // namespace server
} // namespace http

#endif