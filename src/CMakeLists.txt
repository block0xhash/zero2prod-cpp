
add_library(zero2prod_lib STATIC
    app.cpp
    subscriptions.cpp
)
target_include_directories(zero2prod_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(zero2prod_lib PUBLIC Drogon::Drogon libpqxx::pqxx)

add_executable(zero2prod main.cpp)
target_link_libraries(zero2prod PRIVATE zero2prod_lib)
