#ifndef HTTP_URI_HPP
#define HTTP_URI_HPP

#include <unordered_map>

namespace http {
namespace server {

typedef unordered_map<std::string, std::string> QueryString;

struct Uri :: public Common::Uncopyable {

  public: 
    void SetPath(const std::string path);
    std::string GetPath();

    void SetQueryString(const std::string key, const std::string value);
    std::string GetQueryString(std::string key);
  
  private:
    std::string m_path;
    QueryString m_query_strings;
};
} // namespace server
} // namespace http

#endif


