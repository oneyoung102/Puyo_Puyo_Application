cmake_minimum_required(VERSION 3.16)
project(puyo_project)

# =========================
# C++ 표준
# =========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================
# 실행 파일 이름
# =========================
set(EXECUTABLE_NAME puyo_puyo)

# =========================
# 소스 파일 자동 수집
# =========================
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# =========================
# 실행 파일 생성
# =========================
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# =========================
# 헤더 경로
# =========================
target_include_directories(${EXECUTABLE_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

# =========================
# SFML 찾기
# =========================
find_package(SFML COMPONENTS Graphics Window System Audio REQUIRED)

# =========================
# 링크
# =========================
target_link_libraries(puyo_puyo
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

# =========================
# macOS 실행 경로 설정 (리소스용)
# =========================
set_target_properties(${EXECUTABLE_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)