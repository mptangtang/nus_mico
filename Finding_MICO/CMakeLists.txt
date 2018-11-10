################################################
#	CMake Basic Setting
################################################
#	CMake minimu version required
cmake_minimum_required(VERSION 2.8.11)


################################################
#	QT Executable Setting
################################################

include_directories(${PROJECT_SOURCE_DIR}/include/)

#	Define Unicode
Add_Definitions(-DUNICODE -D_UNICODE)


#	通过Ui文件生成对应的头文件，一定要添加
FILE(GLOB UI_FILES "./*.ui")
qt5_wrap_ui(WRAP_FILES ${UI_FILES})

#	将ui文件和生成文件整理在一个文件夹中，非必须
source_group("Ui" FILES ${UI_FILES} ${WRAP_FILES})

#	添加资源文件
FILE(GLOB RCC_FILES "./*.ui")

#	Set the project name, type, source files
FILE(GLOB SRC_FILES "./*.cpp")
FILE(GLOB HEAD_FILES "./*.h")
add_executable(Finding_MICO ${SRC_FILES} ${HEAD_FILES} ${WRAP_FILES} ${RCC_FILES})

# Use the Widgets module from Qt 5.
target_link_libraries(Finding_MICO Qt5::Widgets Qt5::Core Qt5::Gui Qt5::OpenGL )


################################################
#	Project Output Setting
################################################

SET_TARGET_PROPERTIES(Finding_MICO PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/debug)
SET_TARGET_PROPERTIES(Finding_MICO PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/lib/debug)

SET_TARGET_PROPERTIES(Finding_MICO PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/release)
SET_TARGET_PROPERTIES(Finding_MICO PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/lib/release)
