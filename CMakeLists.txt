cmake_minimum_required(VERSION 3.5)	 # Проверка версии CMake.
										# Если версия установленой программы
										# старее указаной, произайдёт аварийный выход.

project(cutils C)			# Название проекта

find_package(Lua REQUIRED)

add_library(vec SHARED src/vec.c)
target_link_libraries(vec PRIVATE lua)

add_library(createtable SHARED src/createtable.c)
target_link_libraries(createtable PRIVATE lua)

install(TARGETS createtable vec
		RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
		LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX})