# include_directories(${nbo_SOURCE_DIR}/MainProject/inc)
# # I assume you want to use LibProject as a library in MainProject.
# include_directories(${nbo_SOURCE_DIR}/LibProject/inc)

link_directories(${nbo_SOURCE_DIR}/src)
# unfortunately it seems like you do have to add each file to here
add_executable(nbo main.cpp planet.cpp  render_thread.cpp  simulate_thread.cpp  space.cpp  space_printer.cpp)

# pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(nbo Threads::Threads)

# target_link_libraries(MainProject LibProject)
