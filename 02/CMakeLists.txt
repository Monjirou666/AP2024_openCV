cmake_minimum_required(VERSION 3.16)
project(MyOpenCVProject CXX)

# C++17 標準を指定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ソースファイルをここで指定．ファイル分割したときも，ここに追記．
set(SOURCES
    # opencvTest_movie.cpp
    # opencvTest_movie_blur.cpp
    # opencvTest_gray.cpp
    # opencvTest_movie_pos.cpp
    # opencvTest_key.cpp
    Practice02.cpp

)

set(CMAKE_OSX_ARCHITECTURES "arm64")


# メインプロジェクトの作成
add_executable(main
    ${SOURCES}
)

# OpenCV 用の設定
find_package(OpenCV REQUIRED)
include_directories(/opt/homebrew/opt/opencv/include/opencv4)
link_directories(/opt/homebrew/opt/opencv/lib)
target_link_libraries(main PRIVATE 
    ${OpenCV_LIBS}
    opencv_core 
    opencv_imgcodecs 
    opencv_highgui 
    opencv_imgproc 
    opencv_videoio 
    opencv_video
)
