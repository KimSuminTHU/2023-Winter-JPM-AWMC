cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름
project(PortfolioOptimizer)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 소스 파일 경로
include_directories(src)
file(GLOB SOURCES "src/*.cpp")

# 실행 파일 생성
add_executable(PortfolioOptimizer ${SOURCES})

# 테스트 실행 파일 (선택적)
# add_executable(PortfolioOptimizerTest test/test.cpp)
# target_link_libraries(PortfolioOptimizerTest gtest gtest_main)
