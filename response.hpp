
#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include<iostream>
#include "uri.hpp"
#include "headers.hpp"
#include "body.hpp"

namespace http {
namespace server {
	
class Response : public Common:Uncopyable {

  public:
    void SetProtocol(const std::string protocol);
    std::string GetProtocol();

    void SetVersion(const std::string version);
    std::string GetVersion();

    void SetStatusCode(const StatusCode status_code);
    StatusCode GetStatusCode();

    void SetReasonPhrase(const std::string reason_phrase);
    std::string GetReasonPhrase();

    Headers GetHeader();
    void SetHeader(const std::string key, const std::string value);
    void GetHeader(const std::string key);

    void SetBody(const Body body);
    Body GetBody();

  private:
    std::string m_protocol;
    Uri         m_version;
    StatusCode  m_status_code;
    std::string m_reason_phrase;
    Headers     m_headers;
    Body        m_body;
};

} // namespace server
} // namespace http

#endif