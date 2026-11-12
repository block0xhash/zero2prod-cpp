
# A library holding everything except main(). The server and the tests both link it
# Every .cpp file must be listed here

add_library(zero2prod_lib STATIC
    app.cpp
)

# PUBLIC: anything that links this library also gets this include folder, which is why
# #include "zero2prod/app.hpp" works in main.cpp and in the tests too.

target_include_directories(zero2prod_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(zero2prod_lib PUBLIC Drogon::Drogon)

# The server program: main.cpp plus the library

add_executable(zero2prod main.cpp)
target_link_libraries(zero2prod PRIVATE zero2prod_lib)
