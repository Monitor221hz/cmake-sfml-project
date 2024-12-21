cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
include(cmake/headerlist.cmake)
include(cmake/sourcelist.cmake)
include_directories(AFTER include)
add_executable(${PROJECT_NAME} src/main.cpp ${headers} ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set(SRC_ASSETS_FOLDER "${CMAKE_SOURCE_DIR}/assets")

if (EXISTS "${SRC_ASSETS_FOLDER}")
        add_custom_command(
        TARGET "${PROJECT_NAME}"
        POST_BUILD 
        COMMAND "${CMAKE_COMMAND}" -E copy_directory_if_different "${SRC_ASSETS_FOLDER}" "${CMAKE_CURRENT_BINARY_DIR}/bin/assets"
        )

        add_custom_command(
            TARGET ${PROJECT_NAME}
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E tar cvf ${CMAKE_CURRENT_BINARY_DIR}/bin/assets.zip --format=zip -- .
            WORKING_DIRECTORY ${SRC_ASSETS_FOLDER}
        )
endif()


if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()
