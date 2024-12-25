cmake_minimum_required(VERSION 3.18)

project(KrxkCompiler)

# 指定代码根目录
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/main)

# 查找 Bison 和 Flex
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# 指定 Bison 和 Flex 的输入文件
set(YYCC_PATH ${SOURCE_DIR}/yacc)
set(BISON_INPUT ${YYCC_PATH}/parser.y)
set(FLEX_INPUT ${YYCC_PATH}/tokenizer.l)

# 生成 Bison 和 Flex 的输出文件
BISON_TARGET(Parser ${BISON_INPUT} ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp 
                        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)
FLEX_TARGET(Scanner ${FLEX_INPUT} ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

add_flex_bison_dependency(Scanner Parser)

# LLVM
find_program(LLVM_CONFIG_EXECUTABLE llvm-config)

if(NOT LLVM_CONFIG_EXECUTABLE)
    message(FATAL_ERROR "llvm-config not found. Please install LLVM.")
endif()

# 获取 LLVM 头文件路径
execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --includedir
    OUTPUT_VARIABLE LLVM_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# 获取 LLVM 库文件路径
execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --libs
    OUTPUT_VARIABLE LLVM_LIB_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# 添加项目源文件
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

# 生成可执行文件
add_executable(${PROJECT_NAME} 
    # flex & bison 输出
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Scanner_OUTPUTS}
    # 项目源文件
    ${SOURCES}
)

# 链接 llvm 库
target_link_libraries(${PROJECT_NAME} 
    ${LLVM_LIB_DIR}
)


# 附加包含目录
# 包含 flex bison 生成的代码
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
# 引入 LLVM 头文件
target_include_directories(${PROJECT_NAME} PRIVATE ${LLVM_INCLUDE_DIR})
# 项目源文件主目录
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})