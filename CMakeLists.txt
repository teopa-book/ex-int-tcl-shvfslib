cmake_minimum_required(VERSION 3.18)
project(tclshvfslib)

set(TARGET_BASE_NAME "${PROJECT_NAME}")
set(APP_NAME "${TARGET_BASE_NAME}")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
include(BuildTclStatic)

add_executable(${APP_NAME}
  src/app.c
)

target_include_directories(${APP_NAME} PRIVATE
  "${TCL_INCLUDE_PATH}"
  "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${APP_NAME}
  ${TCL_LIBRARY}
)

target_compile_definitions(${APP_NAME} PUBLIC
  STATIC_BUILD
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${APP_NAME} PRIVATE -Wall)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_link_options(${APP_NAME} PRIVATE "$<$<CONFIG:Release>:/LTCG>")
  set_property(TARGET ${APP_NAME} PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
  )
endif()

add_dependencies(${APP_NAME} tclvfs)
add_custom_target(tclvfs
  ALL
  COMMAND cp ${TCLVFS_ARCHIVE} tclvfs.zip
  COMMAND xxd -i tclvfs.zip tclvfs.h
  COMMAND mv tclvfs.h ${CMAKE_BINARY_DIR}/tclvfs.h
  COMMAND rm tclvfs.zip
  WORKING_DIRECTORY $<IF:$<BOOL:${UNIX}>,${TCLVFS_UNIX_DIR},${TCLVFS_WIN32_DIR}>
  COMMENT "Generating Tcl VFS archive..."
)
