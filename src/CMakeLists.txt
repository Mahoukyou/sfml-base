set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML REQUIRED COMPONENTS graphics window)

set(
	sfml_srcs
	main.cpp
	game.h
	game.cpp
	scene.h
	scene.cpp
	mainscene.h
	mainscene.cpp
)
add_executable(sfml ${sfml_srcs})
target_link_libraries(sfml PRIVATE sfml-graphics sfml-window)
set_target_properties(sfml PROPERTIES LINKER_LANGUAGE CXX)