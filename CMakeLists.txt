cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(SIEngine)

include(cmake/CheckCompiler.cmake)
include(cmake/CompileOptions.cmake)
include(cmake/IncludeEngineSources.cmake)
include(cmake/LinkLibraries.cmake)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
