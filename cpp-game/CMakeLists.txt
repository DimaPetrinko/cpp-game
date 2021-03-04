 # cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -HG:\Work\cpp-game -BG:\Work\cpp-game\build -G "Visual Studio 16 2019" -Ax64
 # cmake --build build --config Debug --target install
 
set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install/)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)
set(EXTERNAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

if(CMAKE_SYSTEM_NAME STREQUAL Windows)
	set(CURRENT_LIB_DIR ${LIB_DIR}/Win64)
	if (MSVC)
		set(LIBS glfw3 libglew32 opengl32 legacy_stdio_definitions)
	elseif (MINGW)
		set(LIBS glfw3 glew32 opengl32)
	endif()
elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)
	set(CURRENT_LIB_DIR ${LIB_DIR}/Linux64)
	set(LIBS glfw3 GLEW GL)
endif()

foreach(I IN LISTS LIBS)
	unset(LIB_PATH)
	unset(LIB_PATH CACHE)
	find_library(LIB_PATH NAMES ${I} PATHS ${CURRENT_LIB_DIR})
	if (LIB_PATH MATCHES "NOTFOUND")
		set (LIB_PATH ${I})
	endif()
	list(APPEND LIBS_TO_LINK ${LIB_PATH})
endforeach()
message("paths " ${LIBS_TO_LINK})

file(GLOB_RECURSE SOURCES ${SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${SOURCES_DIR}/*.h)

message("")
message("System name:           " ${CMAKE_SYSTEM_NAME})
message("Install dir:           " ${INSTALL_DIR})
message("Sources dir:           " ${SOURCES_DIR})
message("Resources dir:         " ${RESOURCES_DIR})
message("Include dir:           " ${EXTERNAL_INCLUDE_DIR})
message("Lib dir:               " ${CURRENT_LIB_DIR})
message("Libs:                  " ${LIBS})
message("Libs paths:            " ${LIBS_TO_LINK})
message("Sources:               " ${SOURCES})
message("Headers:               " ${HEADERS})
message("")

add_executable(cpp-game ${SOURCES} ${HEADERS})

set_target_properties(
	cpp-game PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(cpp-game PRIVATE ${EXTERNAL_INCLUDE_DIR})
target_include_directories(cpp-game PRIVATE ${SOURCES_DIR})
target_link_libraries(cpp-game ${LIBS_TO_LINK})

install(TARGETS cpp-game DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RESOURCES_DIR} DESTINATION ${INSTALL_DIR})