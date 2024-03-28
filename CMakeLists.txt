cmake_minimum_required(VERSION 3.27)
project(PodatkovneStrukture)

Include(FetchContent)

#
#FetchContent_Declare(
#        Catch2
#        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#        GIT_TAG        v3.4.0
#)

#FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(Dev)

add_executable(Naloga1 Tomic_Danijel_1002619122_N1.cpp Naloga1.h)

#add_executable(Naloga1Test Naloga1Test.cpp Tomic_Danijel_1002619122_N1.cpp Naloga1.h)
#target_link_libraries(Naloga1Test PRIVATE Catch2::Catch2WithMain)
#target_compile_definitions(Naloga1Test PRIVATE DTTESTING)

#test


