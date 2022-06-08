cmake_minimum_required(VERSION 3.0.0)
project(subnet)

option(SANITIZERS "Adding sanitizers" OFF)

IF(SANITIZERS)
    message(STATUS "Adding Sanitizers")
    add_compile_options(-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error)
    add_link_options(-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error)
ENDIF()

add_subdirectory(subnet_lib)

add_executable(${PROJECT_NAME} src/main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

target_include_directories(${PROJECT_NAME} PUBLIC ${SUBNET_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SUBNET_LIB_LIBRARIES})

add_subdirectory(tests)