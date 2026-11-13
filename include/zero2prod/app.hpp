#pragma once
// A header (.hpp) only DECLARES things: it tells other files "this function exists".
// The bodies live in src/app.cpp. Both main.cpp and the tests include this header.
#include <drogon/drogon.h>

namespace zero2prod {

// In FastAPI a handler RETURNS its response. In Drogon the handler is handed a function
// (the "callback") and CALLS it with the response when the answer is ready. That is what
// lets a handler start slow work (a database query, a call to another service), return
// straight away, and answer later without holding up a thread (Chapters 14 and 21).
// This is just the type of that function, given a name once so the handlers stay short.
using Callback = std::function<void(const drogon::HttpResponsePtr &)>;

// The /health_check handler. It is a named function, not a lambda hidden inside
// registerRoutes(), so a test can call it directly: no server, no network.
void healthCheck(const drogon::HttpRequestPtr &request, Callback &&callback);

// Registers every HTTP route (a URL path such as "/health_check" plus the code that
// answers it) with Drogon's single global application object, drogon::app().
void registerRoutes();

}  // namespace zero2pro
