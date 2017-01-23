
namespace Http {

struct Body : Common::Uncopyable {
  
  void SetBody(const std::string body);
  std::string GetBody();

  std::string m_body;

};
}; // Http
