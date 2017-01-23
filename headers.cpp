
namespace Http {

typedef unordered_multimap<std::string, std::string> HeadersMap;

struct Headers : Common::Uncopyable {
  
  void SetHeader(const std::string key, const std::string value);
  HeadersMap GetHeaders();
  std::string GetHeader(const std::string key);
  std::string GetHost();
  unsigned int GetPort();

  HeadersMap m_headers;
};
