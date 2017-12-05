cmake_minimum_required(VERSION 3.9)
project(ogre3d-collisions)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/config.h src/main.cpp src/app/App.cpp src/app/App.h src/app/CamGuy.cpp src/app/CamGuy.h src/mesh/Cuboid.cpp src/mesh/Cuboid.h src/collider/ColCuboid.cpp src/collider/ColCuboid.h src/collider/Quad.cpp src/collider/Quad.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

### OGRE
### Set these paths to your own system
set (OGRE_BUILD_PATH /home/danyalejandro/Libraries/ogre/build)

find_package(OGRE 1.10 REQUIRED)
include_directories(${OGRE_INCLUDE_DIRS} ${OIS_INCLUDE_DIRS})
link_directories(${OGRE_LIBRARY_DIRS})
file(COPY media/resources.cfg ${OGRE_CONFIG_DIR}/plugins.cfg ${OGRE_BUILD_PATH}/Dependencies/lib/libzzip.so ${OGRE_BUILD_PATH}/Dependencies/lib/libfreetype.so.2.6 DESTINATION ${CMAKE_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${OGRE_Overlay_LIBRARIES} ${CEGUI_LIBRARIES})
