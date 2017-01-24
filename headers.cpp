
namespace Http {

typedef unordered_multimap<std::string, std::string> HeadersMap;

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
