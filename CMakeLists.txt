cmake_minimum_required(VERSION 3.13)
project(StardustEmu CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp
        include/memory/memory.cpp
        include/cpu/cpu.cpp
        include/cpu/regs.cpp
        include/cpu/instructions.cpp
        include/cpu/regularinstructionswitch.cpp
        include/cpu/cbprefixinstructionswitch.cpp
        include/ppu/ppu.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
