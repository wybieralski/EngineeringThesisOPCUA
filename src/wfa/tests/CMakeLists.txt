cmake_minimum_required(VERSION 3.14)


message(STATUS "Tests will be build.")

set(TEST_NAMES
        test-transition-server
        )

# Enable testing with CTest
include(CTest)
include(GoogleTest)

foreach(test ${TEST_NAMES})
        message("Building test: " ${test})

        add_executable(${test})

        target_sources(${test} PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/${test}.cpp
                ${CMAKE_SOURCE_DIR}/src/wfa/WFA_client/ClientManager.cpp
                ${CMAKE_SOURCE_DIR}/src/wfa/WFA_server/EventManager.cpp
                ${CMAKE_SOURCE_DIR}/src/wfa/WFA_server/ServerFactory.cpp
                ${CMAKE_SOURCE_DIR}/src/wfa/WFA_server/OPCMessage.cpp
                )

        target_link_libraries(${test}
                PUBLIC
                umati-server-objects
                umati-client-objects
                $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
                gtest
                gmock_main
                )

        set_target_properties(${test} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/staging/tests")
        set_property(TARGET ${test} PROPERTY FOLDER "Tests")

        gtest_discover_tests(${test})
endforeach()
