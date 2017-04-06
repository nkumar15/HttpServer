#include "session.hpp"

namespace http {
namespace server {

void Session :: SetSessionId(const std::string &id) {
  session_id = id;
}

std::string Session :: GetSessionId() {
  return session_id;
}


void Session :: SetRequest(const RequestPtr& req) {
  request_ptr = req;
}

RequestPtr& Session::GetRequest() {
  return request_ptr;
}


} // server
} // http
