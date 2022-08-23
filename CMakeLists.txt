cmake_minimum_required(VERSION 3.12)

project(opengltut VERSION 0.1.0)



FIND_PROGRAM( CG_COMPILER cgc
      /usr/bin
      /usr/local/bin
      DOC "The Cg Compiler"
      )
    GET_FILENAME_COMPONENT(CG_COMPILER_DIR "${CG_COMPILER}" PATH)
    GET_FILENAME_COMPONENT(CG_COMPILER_SUPER_DIR "${CG_COMPILER_DIR}" PATH)
    FIND_PATH( CG_INCLUDE_DIR Cg/cg.h
      /usr/include
      /usr/local/include
      ${CG_COMPILER_SUPER_DIR}/include
      DOC "The directory where Cg/cg.h resides"
      )
    FIND_LIBRARY( CG_LIBRARY Cg
      PATHS
      /usr/lib64
      /usr/lib
      /usr/local/lib64
      /usr/local/lib
      ${CG_COMPILER_SUPER_DIR}/lib64
      ${CG_COMPILER_SUPER_DIR}/lib
      DOC "The Cg runtime library"
      )
	SET(CG_LIBRARY ${CG_LIBRARY} -lpthread)
    FIND_LIBRARY( CG_GL_LIBRARY CgGL
      PATHS
      /usr/lib64
      /usr/lib
      /usr/local/lib64
      /usr/local/lib
      ${CG_COMPILER_SUPER_DIR}/lib64
      ${CG_COMPILER_SUPER_DIR}/lib
      DOC "The Cg runtime library"
      )

add_definitions( -DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"  )
IF(CG_FOUND)
    SET(CG_INCLUDE_DIRS "${CG_INCLUDE_DIR}")
    SET(CG_LIBRARIES ${CG_LIBRARY} ${CG_GL_LIBRARY})
    message("found cg, ${CG_INCLUDE_DIR}")
ENDIF()
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED FATAL_ERROR) # error
find_package(glfw3 REQUIRED FATAL_ERROR) # error
find_package(glm REQUIRED FATAL_ERROR) # 
include(CTest)
enable_testing()
file(GLOB all_files CONFIGURE_DEPENDS
    "main.cpp"
     "*/*.h"
     "*/*.cpp"
     "*/*shader.*"
)
add_executable(${PROJECT_NAME} ${all_files})
target_link_libraries(${PROJECT_NAME} GLEW)
target_link_libraries(${PROJECT_NAME} OpenGL)
target_link_libraries(${PROJECT_NAME} glfw)
add_dependencies(${PROJECT_NAME} OpenGL::OpenGL)
target_include_directories(${PROJECT_NAME} PUBLIC main.cpp Shaders ${INTERNAL_INCLUDES} OpenGL::OpenGL ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIRS})
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)