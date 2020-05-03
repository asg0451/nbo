cmake_minimum_required(VERSION 3.10)
project(nbo)

enable_language(CXX)

# TODO: this is not where this stuff is supposed to go
add_definitions("-std=c++17 -g -Wall -Werror -Wextra -Wpedantic")
# -g -Wall -Werror -Wextra -Wpedantic -std=c++17 -lpthread

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(${CMAKE_BINARY_DIR}/../cmake-scripts/sanitizers.cmake)


set(USE_ANALYZER
  ""
  CACHE
      STRING
      "Compile with --analyize'"
)

if(USE_ANALYZER)
  if(USE_ANALYZER MATCHES "([Tt]rue)")
    message(STATUS "Building with analyzer")
    append("-g --analyze -Xanalyzer -analyzer-output=text" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
  endif()
endif()


add_subdirectory(src)
# add_subdirectory(LibProject)

target_link_libraries(nbo ${CONAN_LIBS})

