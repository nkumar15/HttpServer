#include <set>

namespace http {
namespace server {

using SessionPtr = std::shared_ptr<Session>;

class SessionManager {

 public:
   void OpenSession();
   void CloseSession();


 private:
   std::set<SessionPtr> sessions;
};


