# 1. 画像の表示，簡単な画像処理

## 画像の表示

まずは，画像を読み込んで表示してみます．

### ソースの準備

```opencvTest_first.cpp
// opencvTest_first.cpp
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  cv::Mat image = cv::imread("lena.jpg");

  cv::imshow("Display", image);

  cv::waitKey(0);

  return 0;
}
```

コンパイルはcmakeを使うと楽です．[公式のチュートリアル](https://docs.opencv.org/4.2.0/db/df5/tutorial_linux_gcc_cmake.html)だと，
以下のようなCMakeLists.txt

```cmake
cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( DisplayImage DisplayImage.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )
```
を準備して，となっていますが，

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(MyOpenCVProject CXX)

# ソールファイルをここで指定．ファイル分割したときも，ここに追記．
set(SOURCES
    opencvTest_first.cpp
)

# Create Main project
add_executable(main
    ${SOURCES}
)

# For OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBS})
```
としておくと，後ほど楽です．set(SOURCES... のところで，作成したソースファイル名を指定してください．mainという実行ファイルが生成されます．

### コンパイル，実行

上で準備した，[opencvTest_first.cpp](opencvTest_first.cpp)と[CMakeLists.txt](CMakeLists.txt)，および[lena.jpg](lena.jpg)を同じフォルダーにいれて，コンパイル及び実行してみる．

```
cmake .
make
./main
```

よく見かける画像が表示されるはずです．何かキーを押せば終了します．

## 簡単な画像処理1（画像の平滑化)

画像を平滑化（ざっくりいえば，画像をぼかす）をやってみます．[cv::medianBlur（）](https://docs.opencv.org/4.2.0/d4/d86/group__imgproc__filter.html#ga564869aa33e58769b4469101aac458f9)という関数が使えます．

```cpp
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  cv::Mat src = cv::imread("lena.jpg");
  cv::Mat dst;

  int blur = 100;  // 変化の度合い 

  cv::medianBlur(src, dst, blur * 2 + 1);
  cv::imshow("Display", dst);

  cv::waitKey(0);

  return 0;
}
```

変数`blur`で平滑化度合いを変えられます．いろいろ変えてみて，どうなるか確認してください．


## 簡単な画像処理2（contrast, brightness)

次に，コントラストや明るさを変えてみます．[cv::convertTo()](https://docs.opencv.org/4.2.0/d3/d63/classcv_1_1Mat.html#adf88c60c5b4980e05bb556080916978b)が使えます．

```cpp
#include <iostream>
#include <opencv2/opencv.hpp>


int main()
{
    cv::Mat src = cv::imread("lena.jpg");
    cv::Mat dst;
  
    double alpha = 0.1; // contrast 
    double beta = 1.0; // brightness
     
    src.convertTo(dst, -1, alpha, beta);  
    cv::imshow("Display", dst);
    
    cv::waitKey(0);
    return 0;
}
```

`alpha`, `beta`を変えることで，変化の度合いを変えられます．

## トラックバー

上記の画像処理では，変化の度合いはコンパイル時に決め打ちでした．トラックバーをつけて実行時に変更できるようにしてみます．
[cv::createTrackbar](https://docs.opencv.org/4.2.0/d7/dfc/group__highgui.html#gaf78d2155d30b728fc413803745b67a9b)を使います．

```
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  cv::Mat src, dst;
  int blur = 5;

  src = cv::imread("lena.jpg");

  cv::namedWindow("Display", cv::WINDOW_AUTOSIZE);
  cv::createTrackbar("blur", "Display", &blur, 10);

  while (cv::waitKey(100) < 0) {
    cv::medianBlur(src, dst, blur * 2 + 1);
    cv::imshow("Display", dst);
  }

  return 0;
}
```

- `cv::namedWindow()`で画像を表示するWindow（"Display"）を生成し， cv::createTrackbar(）でトラックバーをWindow（"Display"）に作成します．
- `cv::createTrackbar(）`の一つ目の引数は，生成するトラックバーの名前， 二つ目はトラックバーを生成するWindowの名前，三つ目は，トラックバーの位置の値を入れる変数，四つ目はトラックバーの取りうる最大値．
