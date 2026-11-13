
#include "zero2prod/subscriptions.hpp"
#include "zero2prod/app.hpp"  // for the Callback type

#include <drogon/drogon.h>

namespace zero2prod {

namespace {
// Answers with an empty body and the given status code. Every reply below is one of these.
void reply(const Callback &callback, drogon::HttpStatusCode status) {
    callback(drogon::HttpResponse::newHttpResponse(status, drogon::CT_TEXT_PLAIN));
}
}  // namespace

void registerSubscriptionRoutes(std::shared_ptr<pqxx::connection> db) {
    drogon::app().registerHandler(
        "/subscriptions",
        // [db] copies the database connection into the lambda, so the handler can use it.
        [db](const drogon::HttpRequestPtr &req, Callback &&callback) {
            // Parse the body as JSON. getJsonObject() is null when it is not valid JSON.
            // If the caller sent something we cannot use, answer 400 Bad Request and return
            // early (the "guard" style used throughout the book).
            auto json = req->getJsonObject();
            if (!json || !json->isMember("email") || !json->isMember("name")) {
                reply(callback, drogon::k400BadRequest);
                return;
            }
            try {
                // A transaction groups SQL statements so they succeed or fail together.
                // Nothing is saved until commit(); if an exception is thrown first, the
                // transaction is rolled back when `txn` goes out of scope.
                pqxx::work txn(*db);
                txn.exec("INSERT INTO subscriptions (email, name) VALUES ($1, $2)",
                         pqxx::params{(*json)["email"].asString(), (*json)["name"].asString()});
                txn.commit();
                reply(callback, drogon::k200OK);
            } catch (const pqxx::unique_violation &) {
                // The email column is UNIQUE, so the same address twice breaks that rule.
                // That is the caller's conflict, not our fault: 409 Conflict.
                reply(callback, drogon::k409Conflict);
            } catch (const std::exception &e) {
                LOG_ERROR << "failed to insert subscriber: " << e.what();
                reply(callback, drogon::k500InternalServerError);
            }
        },
        {drogon::Post});
}

}  // namespace zero2prod
