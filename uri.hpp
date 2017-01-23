

namespace Http {

typedef unordered_map<std::string, std::string> QueryString;

struct Uri :: public Common::Uncopyable {
  
    void SetPath(const std::string path);
    std::string GetPath();

    void SetQueryString(const std::string key, const std::string value);
    std::string GetQueryString(std::string key);
  
    std::string m_path;
    QueryStrings m_query_strings;
};
}; // Http


