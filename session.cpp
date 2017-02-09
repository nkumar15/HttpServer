#include "session.hpp"

namespace http {
namespace server {

void Session :: SetRequestId(std::string &id) {
  session_id = id;
}

std::string Session :: GetSessionId() {
  return session_id;
}


void Session :: SetRequest(std::shared_ptr<Request>& req) {
  request = req;
}

RequestPtr& Session::GetRequest() {
  return request;
}


} // server
} // http
