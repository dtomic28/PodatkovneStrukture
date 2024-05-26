cmake_minimum_required(VERSION 3.27)
project(PodatkovneStrukture)

Include(FetchContent)


FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(Dev)

add_executable(Naloga1 Naloga1/Tomic_Danijel_1002619122_N1.cpp Naloga1/Naloga1.h)

add_executable(Naloga1Test Naloga1/Naloga1Test.cpp Naloga1/Tomic_Danijel_1002619122_N1.cpp Naloga1/Naloga1.h)
target_link_libraries(Naloga1Test PRIVATE Catch2::Catch2WithMain)
target_compile_definitions(Naloga1Test PRIVATE DTTESTING)


add_executable(Naloga2 Naloga2/Tomic_Danijel_1002619122_N2.cpp
        Naloga2/Naloga2.h)

add_executable(Naloga2Test Naloga2/Naloga2Test.cpp Naloga2/Tomic_Danijel_1002619122_N2.cpp Naloga2/Naloga2.h)
target_link_libraries(Naloga2Test PRIVATE Catch2::Catch2WithMain)
target_compile_definitions(Naloga2Test PRIVATE DTTESTING)

add_executable(Naloga3 Naloga3/Tomic_Danijel_1002619122_N3.cpp)

add_executable(Naloga4 Naloga4/Tomic_Danijel_1002619122_N4.cpp)
