cmake_minimum_required(VERSION 3.10)
project(smart-pointer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(shared_pointer INTERFACE)
target_include_directories(shared_pointer INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_executable(prog
	src/main.cpp
)
target_link_libraries(prog PRIVATE shared_pointer)

include(FetchContent)
FetchContent_Declare(
	googletest
    	URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(shared_pointer_test
	tests/shared_pointer_test.cpp
)

target_link_libraries(shared_pointer_test
	PRIVATE
		shared_pointer
		GTest::gtest
		GTest::gtest_main
)
add_test(NAME shared_pointer_test COMMAND shared_pointer_test)
