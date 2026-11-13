#include "zero2prod/app.hpp"
#include "zero2prod/subscriptions.hpp"

namespace zero2prod {

void healthCheck(const drogon::HttpRequestPtr &, Callback &&callback) {
    callback(drogon::HttpResponse::newHttpResponse());  // 200 OK, empty body
}

void registerRoutes(std::shared_ptr<pqxx::connection> db) {
    drogon::app().registerHandler("/health_check", &healthCheck, {drogon::Get});

    (void)db;  // subscription routes arrive in 3.9
    registerSubscriptionRoutes(std::move(db));
}

}  // namespace zero2prod
