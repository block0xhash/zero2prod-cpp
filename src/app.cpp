
#include "zero2prod/app.hpp"

namespace zero2prod {

// In FastAPI a handler RETURNS its response. In Drogon the handler is handed a function
// (the "callback") and CALLS it with the response when the answer is ready. That is what
// lets a handler start slow work (a database query, a call to another service), return
// straight away, and answer later without holding up a thread (Chapters 14 and 21).
// This is just the type of that function, given a name once so the handlers below stay short.
using Callback = std::function<void(const drogon::HttpResponsePtr &)>;

void registerRoutes() {
    drogon::app().registerHandler(

        "/health_check",  // 1. the URL path

        // 2. the handler: a lambda, which is C++'s anonymous function. Drogon requires exactly
        //    these two parameter types (writing "auto" instead does not compile).
        //      - the incoming request: unused here, so it has no name
        //      - the callback: call it exactly once to send the response
        
        [](const drogon::HttpRequestPtr &, Callback &&callback) {

            // A new response is "200 OK" with an empty body unless you change it.
            callback(drogon::HttpResponse::newHttpResponse());
        },

        {drogon::Get});  // 3. only answer GET requests
}

}  // namespace zero2prod
