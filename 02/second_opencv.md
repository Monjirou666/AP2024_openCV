# 動画の表示

## namespace cv

[1 画像の表示，簡単な画像処理](../01/first_opencv.md)では，

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

メソッド`read()`で，1フレーム読み込み，引数であたえたMat型の変数frameに代入し，それを`imshow()`で表示する，という処理をwhileループで繰り返しています．
また，`read()`はフレームを読み込めたら`true`，読み込めなかったら`false`を返します． https://docs.opencv.org/4.5.0/d8/dfe/classcv_1_1VideoCapture.html#a473055e77dd7faa4d26d686226b292c1
それを使うことで，wileループにて動画の最後まで読み込みを行います．


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
