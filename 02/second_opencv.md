# 動画の表示

## 動画の読み込み

動画を読み込んで表示してみます．

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
    
    while(true){
        cap.read(frame);
        imshow("movie", frame);
        waitKey(30);
    }
    return 0;
}
```



    - カメラ(optional)
- blurを書けて表示
- トラックバーでフレーム位置を指定
- 色変換 RGB to gray
- キー入力で途中終了．

## 練習問題2

キー入力でいろいろ操作
- grayかRGBか
- ポーズ
- 巻き戻し（先頭へ）
- キー入力で途中終了

など．
