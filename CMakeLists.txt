cmake_minimum_required(VERSION 3.23.0)
project(main VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(find-repo  find-repo.cpp)
add_executable(remove-cache  cache_remover.cpp)

set(LIBS nlohmann_json::nlohmann_json fmt::fmt unofficial::git2::libgit2package)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(unofficial-git2 CONFIG REQUIRED)
target_link_libraries(find-repo PRIVATE ${LIBS})
target_link_libraries(remove-cache PRIVATE ${LIBS})


enable_testing()
add_subdirectory(test)

add_subdirectory(benchmark)

install(TARGETS find-repo DESTINATION bin)
# install(TARGETS $<TARGET_RUNTIME_DLLS:main> DESTINATION bin)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_FILE_NAME update_server_package)
include(CPack)

include(GNUInstallDirs)
