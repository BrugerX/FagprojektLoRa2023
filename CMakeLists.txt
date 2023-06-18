# !!! WARNING !!! AUTO-GENERATED FILE, PLEASE DO NOT MODIFY IT AND USE
# https://docs.platformio.org/page/projectconf/section_env_build.html#build-flags
#
# If you need to override existing CMake configuration or add extra,
# please create `CMakeListsUser.txt` in the root of project.
# The `CMakeListsUser.txt` will not be overwritten by PlatformIO.

cmake_minimum_required(VERSION 3.13)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project("FagprojektLoRa2023" C CXX)

include(CMakeListsPrivate.txt)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsUser.txt)
include(CMakeListsUser.txt)
endif()

add_custom_target(
    Production ALL
    COMMAND platformio -c clion run "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    Debug ALL
    COMMAND platformio -c clion debug "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


add_executable(Z_DUMMY_TARGET ${SRC_LIST} test/test_RegexUtility/UtilityRegexTest.cpp test/test_RSAPEMHandler/RSAPEMHandler_test.cpp test/test_RSAPEMHandler/RSAPEMHandler_test.h) lib/MVC/MVCSettings.h lib/MVC/NavigationData.cpp test/test_MVC/test_adding_and_deletion_of_members.hpp test/test_MVC/test_user_input_compass_state.hpp test/test_MVC/test_user_input_table_state.hpp test/test_MVC/test_embedded_main.cpp test/test_MVC/test_user_input_nav_overview_state.hpp test/test_MVC/test_user_input_nav_overview_state.hpp