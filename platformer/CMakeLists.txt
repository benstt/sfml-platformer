cmake_minimum_required(VERSION 3.21)
project(platformer)

set(CMAKE_CXX_STANDARD 20)

add_executable(platformer src/main.cpp src/Game.cpp src/Actor.cpp src/KeyboardManager.cpp src/Collider.cpp src/EntityTracker.cpp src/Entity.cpp src/TileMap.cpp src/AnimationPlayer.cpp)

include_directories(include h:/SFML/include)

set(SFML_ROOT h:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(platformer ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()