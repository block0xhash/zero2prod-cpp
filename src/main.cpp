
#include "zero2prod/app.hpp"

#include <cstdlib>
#include <iostream>

int main() {
    const char *url = std::getenv("DATABASE_URL");
    if (!url) {
        std::cerr << "DATABASE_URL is not set\n";
        return 1;
    }
    auto db = std::make_shared<pqxx::connection>(url);
    zero2prod::registerRoutes(db);
    drogon::app().addListener("0.0.0.0", 8000);
    drogon::app().run();
    return 0;
}
