
#include "zero2prod/app.hpp"
#include <drogon/HttpAppFramework.h>

int main() {

    // 1. Register the routes ( see app.cpp) Nothing is listening yet
    zero2prod::registerRoutes();

    // 2. Listen on every network interface( "0.0.0.0"), port 8080
    drogon::app().addListener("0.0.0.0", 8000);

    // 3. Start serving. run() does not return
    // until the process is stopped
    //

    drogon::app().run();

    return 0;

}
