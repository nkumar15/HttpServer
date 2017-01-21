

class RequestLine  {
  public:
    std::string GetMethod();
    std::string GetUriPath();
    std::string GetHttpProtocolVersion();
    std::string GetHost();
};

