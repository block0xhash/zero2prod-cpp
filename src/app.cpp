
#include "zero2prod/app.hpp"

namespace zero2prod {

// The handler. Drogon requires exactly these two parameter types (writing "auto" instead
// does not compile). The request is unused here, so it has no name. Call the callback
// exactly once to send the response.
void healthCheck(const drogon::HttpRequestPtr &, Callback &&callback) {
    // A new response is "200 OK" with an empty body unless you change it.
    callback(drogon::HttpResponse::newHttpResponse());
}

void registerRoutes() {
    drogon::app().registerHandler(
        "/health_check",  // 1. the URL path
        &healthCheck,     // 2. the function to run when a request arrives for it
        {drogon::Get});   // 3. only answer GET requests
}

}  // namespace zero2prod
