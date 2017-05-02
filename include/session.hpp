#include <memory>
#include "request.hpp"

namespace http {
namespace server {

using RequestPtr = std::shared_ptr<Request>;

class Session { 

  public:
    std::string GetSessionId();
    void SetSessionId(const std::string& id);

    RequestPtr& GetRequest();
    void SetRequest(const RequestPtr& request);

    Session(const Session& other) = delete;
    Session& operator=(const Session& rhs) = delete;

  private:
   std::string session_id;
   RequestPtr request_ptr;
};


} // namespace server
} // namespace http
