#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# define a macro that helps defining an option
macro(pang_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()


project(pang)

include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "pang")

SET(SOURCES
	src/pang.cpp
	src/Game.h
	src/Game.cpp
	src/SplashScreen.h
	src/SplashScreen.cpp
	src/MainMenu.h
	src/MainMenu.cpp
	src/Logger.h
	src/Logger.cpp
	src/VisibleGameObject.h
	src/VisibleGameObject.cpp
	src/PlayerPaddle.h
	src/PlayerPaddle.cpp
	src/GameObjectManager.h
	src/GameObjectManager.cpp
	src/GameBall.h
	src/GameBall.cpp
	src/SFMLSoundProvider.h
	src/SFMLSoundProvider.cpp
	src/SoundFileCache.h
	src/SoundFileCache.cpp
	src/AIPaddle.h
	src/AIPaddle.cpp
	src/ServiceLocator.h
	src/ServiceLocator.cpp
	src/PreferencesMenu.h
	src/PreferencesMenu.cpp
)

add_executable(${EXECUTABLE_NAME} ${SOURCES})


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Look for BOOST
find_package(Boost REQUIRED COMPONENTS system thread log log_setup)
if(Boost_FOUND)
	message(STATUS "BOOST found.")

	#https://stackoverflow.com/questions/17844085/boost-log-with-cmake-causing-undefined-reference-error
	#http://www.boost.org/doc/libs/1_54_0/libs/log/doc/html/log/rationale/namespace_mangling.html
	#this is needed to get things to link properly
	ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
endif()

# Detect and add SFML
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  message(STATUS "SFML found.")
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# add an option for building the documentation
pang_set_option(PANG_BUILD_DOC FALSE BOOL "TRUE to generate the documentation, FALSE to ignore it")


# Detect and add SFGUI
find_package(SFGUI REQUIRED)
if(SFGUI_FOUND)
  message(STATUS "SFGUI found.")
  include_directories(${SFGUI_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFGUI_LIBRARY})
endif()

# Detect and add sfeMovie
find_package(sfeMovie REQUIRED)
if(SFEMOVIE_FOUND)
  message(STATUS "sfeMovie found.")
  include_directories(${SFEMOVIE_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFEMOVIE_LIBRARY})
endif()

if(PANG_BUILD_DOC)
    add_subdirectory(doc)
endif()

# Check C++ 14 support
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

#TODO: why do we need to manually specify these?
target_link_libraries(${EXECUTABLE_NAME} -lstdc++ -lpthread -lm)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

#Copy over resources (images and such)
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
