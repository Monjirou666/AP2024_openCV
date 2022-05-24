# 動画の表示

## namespace cv

[1 画像の表示，簡単な画像処理](../01/first_opencv.md)では，OpenCV由来であることがわかるよう`cv::Mat`や`cv::imshow`といったように，
明示的にスコープ解決演算子`::`を用いて，名前空間cvを指定していました．
以降は，コード冒頭に

```
using namespace cv;
```
を記載して，名前空間の指定を省略しています．注意してください．


## 動画の読み込み

[動画(vtest.avi)](vtest.avi)を読み込んで表示してみます．

```cpp
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{

    VideoCapture cap("vtest.avi");
  
    if(!cap.isOpened()){
        return -1;
    }
    
    Mat frame;
    namedWindow("movie", WINDOW_AUTOSIZE);
    
    while(cap.read(frame)){
        imshow("movie", frame);
        waitKey(30);
    }
    
    return 0;
}
```

[VideoCapture](https://docs.opencv.org/4.5.0/d8/dfe/classcv_1_1VideoCapture.html)が動画を扱うclassです．
`VideoCapture cap("vtest.avi");`で，そのインスタンス`cap`を生成し，vtest.aviを読み込んでいます．

whileループのところで
- メソッド`read()`で，1フレーム読み込み，引数であたえたMat型の変数frameに代入
- frameを`imshow()`で表示する
という処理を繰り返しています．

`read()`はフレームを読み込めたら`true`，読み込めなかったら`false`を返します． https://docs.opencv.org/4.5.0/d8/dfe/classcv_1_1VideoCapture.html#a473055e77dd7faa4d26d686226b292c1
それを使うことで，whileループにて動画の最後まで読み込むという処理を実現しています


## 動画への画像処理

```cpp
Mat frame;
cap.read(frame)
```
で，読み込まれたframeは，一枚の画像となるので，それに対して[1 画像の表示，簡単な画像処理](../01/first_opencv.md)にて扱った画像処理をすることができます．

動画にblurをかける例は以下の通りになります．

```cpp
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int b = 2;

void on_tracker(int b_, void *) { b = b_; }

int main() {
  VideoCapture cap("vtest.avi");

  if (!cap.isOpened()) {
    return -1;
  }

  Mat src, dst;
  namedWindow("movie", WINDOW_AUTOSIZE);
  createTrackbar("blur", "movie", nullptr, 10, on_tracker);
  setTrackbarPos("blur", "movie", b);

  while (cap.read(src)) {
    medianBlur(src, dst, b * 2 + 1);
    imshow("movie", dst);
    waitKey(30);
  }
  return 0;
}
```

whileループのところで，
- `read()`で読み込んだフレームを`src`にいれる．
- `src`を`medianBlur()`でblur処理し，結果を`dst`にいれる．
- `dst`を`imshow()`で表示
を繰り返しています．

同様にすれば，contrastやbrightnessの調整も可能です．やってみましょう．


## フレーム位置を指定

- 色変換 RGB to gray
- キー入力で途中終了．

## 練習問題2

キー入力でいろいろ操作
- grayかRGBか
- ポーズ
- 巻き戻し（先頭へ）
- キー入力で途中終了

など．
