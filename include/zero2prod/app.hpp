#pragma once

// A header (.hpp) only DECLARES things: it tells other files " this function exists".
// The body lives in src/app.cpp Both main.cpp and the tests include this header,
// so both can call registerRoutes() without duplicating it.
#include <drogon/drogon.h>

namespace zero2prod {

    // Registers every HTTP route onto the global Drogon app instance
    // A free function, not a class, so tests can call it against a
    // disposable port without dragging in the rest of main()
    void registerRoutes();

} // namespace zero2prod
 
