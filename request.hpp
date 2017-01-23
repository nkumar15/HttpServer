
#include<iostream>

namespace Http {

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
}; // Http

