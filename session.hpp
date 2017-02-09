#include <memory>

namespace http {
namespace server {

class Session { 

  public:
    std::string GetSessionId();
    void SetSessionId(const std::string& id);

    RequestPtr& GetRequest();
    void SetRequest(const RequestPtr& request);

  private:

   Session(const Session& other) = delete;
   Session& operator=(Session& rhs) = delete;
   
   std::string session_id;
   RequestPtr request_ptr;
};


} // namespace server
} // namespace http
