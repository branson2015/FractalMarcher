# Here and below: Cmake version and out-of-source build setup
# minmimum version check
cmake_minimum_required(VERSION 3.24)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# no in-source builds check
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed! Create a build directory and run CMake from there. " )
endif()
# set(CMAKE_FIND_DEBUG_MODE 1)

# set paths to find required libraries (leave blank for default)
set(opengl_path "")
set(glfw_path ${CMAKE_SOURCE_DIR}/vendor/glfw)
set(glm_path ${CMAKE_SOURCE_DIR}/vendor/glm)
set(openvkl_path ${CMAKE_SOURCE_DIR}/vendor/openvkl)
set(glad_path ${CMAKE_SOURCE_DIR}/vendor/glad)

# Here and below: cmake setup
# set system to win32
set(SYSTEM WIN32)
# define entrypoint to use main and not WinMain
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE") # /SUBSYSTEM:WINDOWS

# specify output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# here and below: project creation
# create project
project(
  FractalMarcher
  VERSION 1.0
  LANGUAGES CXX
)

# create (empty) target
add_executable(FractalMarcher ${SYSTEM} "")

# here and below: c++ setup
# set CXX version
target_compile_features(FractalMarcher PUBLIC cxx_std_20)
set_target_properties(FractalMarcher PROPERTIES CXX_EXTENSIONS OFF)

# Here and below: library location setup
# find packages
# opengl
set(OpenGL_GL_PREFERENCE "GLVND") # Request new ABI, but this is only a hint.
find_package(OpenGL REQUIRED ${opengl_path})



# openvkl
find_package(openvkl REQUIRED PATHS ${openvkl_path})
target_link_libraries(FractalMarcher PUBLIC openvkl::openvkl)
# target_link_libraries(FractalMarcher PUBLIC openvkl::openvkl_module_cpu_device)

# build glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${glfw_path})
target_link_libraries(FractalMarcher PUBLIC glfw)

#glm
find_package(glm REQUIRED PATHS ${glm_path}/cmake)
target_include_directories(FractalMarcher PRIVATE ${glm_path})

# glad
target_include_directories(FractalMarcher PRIVATE ${glad_path}/include)
target_sources(FractalMarcher PRIVATE ${glad_path}/src/glad.c)

# target_link_libraries(FractalMarcher imgui)

# here and below: source file setup

# set include dir
target_include_directories(FractalMarcher PRIVATE ${FractalMarcher_SOURCE_DIR}/include)

# add subdirectories
add_subdirectory(${FractalMarcher_SOURCE_DIR}/src)





# copy DLLs 
set(DLLFiles "embree3;openvkl_module_cpu_device;openvkl_module_cpu_device_4;openvkl_module_cpu_device_8;openvkl_module_cpu_device_16;openvkl;rkcommon;tbb12;tbbmalloc")
add_custom_target(DLLCopy)
foreach(DLLFile ${DLLFiles})
  add_custom_command(TARGET FractalMarcher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${openvkl_path}/bin/${DLLFile}.dll $<TARGET_FILE_DIR:FractalMarcher>
  )
endforeach()
#copy resources
add_custom_command(TARGET FractalMarcher PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${FractalMarcher_SOURCE_DIR}/resources $<TARGET_FILE_DIR:FractalMarcher>/resources
)
