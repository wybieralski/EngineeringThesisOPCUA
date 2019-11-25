cmake_minimum_required(VERSION 3.14)
project(WFA_printer
        VERSION 1.0
        DESCRIPTION "WFA MACHINE 3D PRINTER SIMULATOR/CLIENT"
        LANGUAGES CXX)

option(BUILD_FREEOPCUA "Build FreeOpcUa library" OFF)
option(USE_FREEOPCUA "Build FreeOpcUa library" OFF)

include(ExternalProject) #loads cmake modules eg. ExternalProject_Add

add_executable(WFA_server)
add_executable(WFA_client)
target_sources(WFA_client PRIVATE
        src/wfa/WFA_client.cpp
        src/wfa/WFA_client/ClientManager.cpp
        src/wfa/WFA_client/DataRecorder.cpp
        src/wfa/WFA_client/SubscribtionManager.cpp
        )

target_sources(WFA_server  PRIVATE
        src/wfa/WFA_server.cpp
        src/wfa/WFA_server/ServerFactory.cpp
        src/wfa/WFA_server/OPCMessage.cpp
        src/wfa/WFA_server/EventManager.cpp
        )


find_package(Boost REQUIRED
        COMPONENTS
        system
        program_options
        filesystem
        thread)

#
#if(UNIX)
#    SET(SSL_SUPPORT_LINK_LIBRARIES mbedx509 mbedtls mbedcrypto)
#endif()

if(BUILD_FREEOPCUA)
    set(install_directory ${CMAKE_SOURCE_DIR}/dependencies-build)
    ExternalProject_Add(FreeOpcUa
            SOURCE_DIR
            ${CMAKE_SOURCE_DIR}/dependencies/FreeOpcUa
            LOG_UPDATE
            true
            USES_TERMINAL_BUILD
            true
            BUILD_IN_SOURCE
            false
            LOG_BUILD
            true
            UPDATE_DISCONNECTED
            true
            STEP_TARGETS
            update
            CMAKE_ARGS
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
            -DCMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}
            -DCMAKE_INSTALL_PREFIX=${install_directory}
            -DSSL_SUPPORT_MBEDTLS=off
            INSTALL_DIR
            ${install_directory}
            PREFIX
            ${CMAKE_BINARY_DIR}/Externals/FreeOpcUa)
elseif(USE_FREEOPCUA)

    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/dependencies-build/share/FreeOpcUa)
    find_package(OpcUaExport REQUIRED)

    target_link_libraries(WFA_client
            PUBLIC
            FreeOpcUa::opcua
            $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
            )

    target_link_libraries(WFA_server
            PUBLIC
            FreeOpcUa::opcua
            )

    add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/googletest)
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/wfa/tests)

else()


    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/dependencies/prebuilt_FreeOpcUa/share/FreeOpcUa)

    find_package(OpcUaExport REQUIRED)


    target_link_libraries(WFA_client
            PUBLIC
            FreeOpcUa::opcua
            $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
            )

    target_link_libraries(WFA_server
            PUBLIC
            FreeOpcUa::opcua
            )

    add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/googletest)
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/wfa/tests)

endif()


