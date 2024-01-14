set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pipe -fPIC -g")

add_executable(app_optional app_optional.cpp)
add_executable(app_lazy app_lazy.cpp)
add_executable(app_any app_any.cpp)
add_executable(app_function_traits app_function_traits.cpp)
add_executable(app_decay app_decay.cpp)
add_executable(app_is_same app_is_same.cpp)