cmake_minimum_required(VERSION 3.14)
project(lemin C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libft)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src LEMIN_SRC)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_executable(lem-in ${LEMIN_SRC})

target_include_directories(lem-in PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/libtf/includes)

target_link_directories(lem-in PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}../libtf)
target_link_libraries(lem-in ft)

