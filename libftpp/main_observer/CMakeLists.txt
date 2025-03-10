project(main_observer)
cmake_policy(SET CMP0072 NEW)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}   -D_CRT_SECURE_NO_WARNINGS")
    if (MSVC)
        if(CMAKE_BUILD_TYPE MATCHES Debug)
            add_compile_options(/RTC1 /Od /Zi)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fsanitize=address")
        endif()     
    endif()

endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_compile_options(
    -Wall 
   -Wextra
   -Werror
)


file(GLOB SOURCES "src/*.cpp")
add_executable(main_observer   ${SOURCES})


target_include_directories(libftpp PUBLIC  include src)



if(CMAKE_BUILD_TYPE MATCHES Debug)

if (UNIX)
target_compile_options(main_observer PRIVATE -fsanitize=address -fsanitize=undefined -fsanitize=leak -g  -D_DEBUG -DVERBOSE)
target_link_options(main_observer PRIVATE -fsanitize=address -fsanitize=undefined -fsanitize=leak -g  -D_DEBUG) 
endif()


elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(main_observer PRIVATE -O3   -DNDEBUG )
    target_link_options(main_observer PRIVATE -O3   -DNDEBUG )
endif()

target_link_libraries(main_observer libftpp )

if (WIN32)
    target_link_libraries(main_observer Winmm.lib)
endif()


if (UNIX)
    target_link_libraries(main_observer  m )
endif()
