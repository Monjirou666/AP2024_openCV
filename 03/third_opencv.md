# 背景差分，色検出

## 背景差分

動画中，動いている物体をトラッキングするためには，動いている物体を検出する必要があります．
そのための多種多様な方法が提案されていますが，
その中の（おそらく一番）単純な方法の一つが背景差分です．

背景差分では，背景のみが映った画像をまず準備しておいて，現在の画像との引き算を行います．
移動物体（背景差分に映っていない物体）があれば，引き算したときの残りとなるので，移動物体を抽出できます．
背景画像が必要なので，移動ロボットに搭載されたカメラの画像に対しては，カメラの向きや位置が変わり続けるため利用は難しいですが，
固定カメラによる画像に対してはそれなりに使えます．

### 一番シンプルな方法

```cpp
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

VideoCapture cap;

void on_tracker(int p, void *) { cap.set(CAP_PROP_POS_FRAMES, p); }

int main() {
  cap.open("vtest.avi");

  if (!cap.isOpened()) {
    return -1;
  }

  Mat src, dst, gray, back;
  namedWindow("movie", WINDOW_AUTOSIZE);
  setWindowProperty("movie", WND_PROP_TOPMOST, 1);
  createTrackbar("pos", "movie", nullptr, (int)cap.get(CAP_PROP_FRAME_COUNT),
                 on_tracker);
  setTrackbarPos("pos", "movie", 0);

  bool playing = true;
  bool loopflag = true;

  cap.read(src);
  cvtColor(src, back, COLOR_BGR2GRAY);

  while (loopflag) {
    if (playing && cap.read(src)) {
      cvtColor(src, gray, COLOR_BGR2GRAY);
      absdiff(gray, back, dst);
      imshow("movie", dst);
    }
    char c = waitKey(30);
    switch (c) {
      case ' ':
        playing = !playing;
        break;
      case 'e':
        loopflag = false;
        break;
      case 's':
        cap.set(CAP_PROP_POS_FRAMES, 0);
      default:
        break;
    }
  }

  return 0;
}
```

この例では，whileループに入る前の，
```cpp
cap.read(src);
cvtColor(src, back, COLOR_BGR2GRAY);
```
にて，一度画像を取得し，それを背景画像としています．

whileループ内で，取得した画像をグレースケールに変換し，それ(`gray`）と背景画像（back)との差分を，[`absdiff()`](https://docs.opencv.org/4.5.0/d2/de8/group__core__array.html#ga6fef31bc8c4071cbc114a758a2b79c14)で計算し，結果を`dst`に入れています．



### 動的背景差分

上記の方法は，非常にシンプルですが，
- ノイズの影響
- 影（移動物体と一緒に移動する）
- 固定カメラでも照明の変化により背景部分の画像も変化
など，そのままでは，実環境では利用するのは難しいです．

そこで，前もって背景画像を準備するのではなく，逐次的に背景画像を複数枚の画像から生成するといった，動的な背景差分法がいろいろ提案されており，
OpenCVにもライブラリーとして，使えるものが準備されています．

- [https://docs.opencv.org/4.x/d7/df6/classcv_1_1BackgroundSubtractor.html](https://docs.opencv.org/4.x/d7/df6/classcv_1_1BackgroundSubtractor.html)
- [https://docs.opencv.org/4.5.0/d2/d55/group__bgsegm.html](https://docs.opencv.org/4.5.0/d2/d55/group__bgsegm.html)




## しきい値処理
    
## 色検出

### BGRでマスク

## 練習問題3

- HSVでmask
- trackbarで閾値を調整
