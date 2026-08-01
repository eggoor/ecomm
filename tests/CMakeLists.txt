cmake_minimum_required(VERSION 3.16)

include(FetchContent)

# Fetch Unity from GitHub
FetchContent_Declare(
	unity
	GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
	GIT_TAG v2.6.0
	EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(unity)

# Add test executables for each test module
add_executable(test_file_ops
	test_file_ops.c
	test_file_ops_runner.c
	${unity_SOURCE_DIR}/src/unity.c
)

add_executable(test_string_utils
	test_string_utils.c
	test_string_utils_runner.c
	${unity_SOURCE_DIR}/src/unity.c
)

# Link against the main library
target_link_libraries(test_file_ops PRIVATE ecomm::ecomm)
target_link_libraries(test_string_utils PRIVATE ecomm::ecomm)

# Include directories for all tests
target_include_directories(test_file_ops PRIVATE ${unity_SOURCE_DIR}/src)
target_include_directories(test_string_utils PRIVATE ${unity_SOURCE_DIR}/src)

# Set C standard for tests
set_target_properties(test_file_ops PROPERTIES
	C_STANDARD 11
	C_STANDARD_REQUIRED ON
)
set_target_properties(test_string_utils PROPERTIES
	C_STANDARD 11
	C_STANDARD_REQUIRED ON
)

# Register tests with CTest
add_test(NAME file_ops_tests COMMAND test_file_ops)
add_test(NAME string_utils_tests COMMAND test_string_utils)
