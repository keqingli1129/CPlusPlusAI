cmake_minimum_required(VERSION 3.10.0)
project(AIMagic VERSION 0.1.0 LANGUAGES C CXX)

# Set CUDA architecture for GTX 950M (compute capability 5.0)
set(CMAKE_CUDA_ARCHITECTURES 50)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "./libtorch117") # Adjust path as needed

find_package(Torch REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.1.1
)

FetchContent_MakeAvailable(fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt "${TORCH_LIBRARIES}")

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
