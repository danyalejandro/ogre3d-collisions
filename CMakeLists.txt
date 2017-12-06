cmake_minimum_required(VERSION 3.8)
project(ogre3d-collisions)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/config.h src/main.cpp src/app/App.cpp src/app/App.h src/app/CamGuy.cpp src/app/CamGuy.h src/mesh/Cuboid.cpp src/mesh/Cuboid.h src/collider/ColCuboid.cpp src/collider/ColCuboid.h src/collider/Quad.cpp src/collider/Quad.h src/collider/Collider.cpp src/collider/Collider.h src/collider/Manager.cpp src/collider/Manager.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

### OGRE
### Set these paths to your own system
set (OGRE_BUILD_PATH ~/Libraries/ogre/build)

find_package(OGRE 1.10 REQUIRED)
include_directories(${OGRE_INCLUDE_DIRS} ${OIS_INCLUDE_DIRS})
link_directories(${OGRE_LIBRARY_DIRS} ${OGRE_BUILD_PATH}/Dependencies/lib)
file(COPY resources.cfg ${OGRE_CONFIG_DIR}/plugins.cfg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY media DESTINATION ${CMAKE_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${OGRE_Overlay_LIBRARIES} ${CEGUI_LIBRARIES})
