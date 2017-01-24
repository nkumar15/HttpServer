#ifndef HTTP_HEADERS_HPP
#define HTTP_HEADERS_HPP


namespace http {
namespace server {
	
class Headers : Common::Uncopyable {

  public:
    void SetHeader(const std::string key, const std::string value);
    
    HeadersMap GetHeaders();
    std::string GetHeader(const std::string key);
    std::string GetHost();
    
    unsigned int GetPort();

  private:
    HeadersMap m_headers;
};

} // namespace server
} // namespace http

#endif