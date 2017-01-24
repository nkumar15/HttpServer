#ifndef HTTP_BODY_HPP
#define HTTP_BODY_HPP

namespace http {
namespace server {
	
struct Body : Common::Uncopyable {
  
  std::string m_body;

};

} // namespace server
} // namespace http

#endif