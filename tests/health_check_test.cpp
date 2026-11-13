
#include <gtest/gtest.h>     // the test framework: TEST(), EXPECT_*, ASSERT_*
#include "test_helpers.hpp"  // starts a real server for the tests (see TestApp)

using namespace zero2prod::testing;

// TEST(SuiteName, TestName). ctest lists this one as "HealthCheck.Returns200WithEmptyBody".
TEST(HealthCheck, Returns200WithEmptyBody) {
    // Arrange: a client pointed at the test server. The first call to TestApp::instance()
    // starts that server: a real server on a real port, not a mock.
    auto client = newClient(TestApp::instance().baseUrl());
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setPath("/health_check");

    // Act: send a real HTTP request and wait up to 3 seconds for the answer.
    auto [result, response] = client->sendRequest(req, 3.0);

    // Assert. ASSERT_* stops the test when it fails (there is no response to inspect if the
    // request itself failed); EXPECT_* records the failure and carries on.
    ASSERT_EQ(result, drogon::ReqResult::Ok);
    EXPECT_EQ(response->statusCode(), drogon::k200OK);
    EXPECT_TRUE(response->body().empty());
}
