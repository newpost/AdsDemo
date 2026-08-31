cmake_minimum_required(VERSION 3.12)
project(MyAdsApp CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 指定 AdsLib 的头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/AdsLib/include/ads)

# 2. 指定 AdsLib 的库文件路径
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/AdsLib/lib)

# 3. 添加你的可执行文件
add_executable(my_ads_app src/main.cpp)

# 4. 链接 AdsLib 静态库及 Windows 必需的系统库 (Winsock)
target_link_libraries(my_ads_app PRIVATE AdsLib ws2_32 wsock32)