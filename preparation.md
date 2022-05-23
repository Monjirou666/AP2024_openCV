# 準備

## Windows 

wsl2を起動し，OpenCVをインストールしてください．

```
sudo apt update
sudo apt install libopencv-dev libopencv-contrib-dev
```

次に，wslのGUIアプリを起動するためのGWSLをインストールします．

1. Microsoft store で「GWSL」と検索してインストール．
2. インストールが完了したら「GWSL」を起動

参考：　https://qiita.com/1024xx4/items/45a5cce13eafa17ca6f1

## Mac

ターミナルにて，homebrewを使ってインストール．

```
brew update 
brew install opencv
```

## 共通

インストール作業後，ターミナルにて

```
opencv_verson
```
としたときに，version番号が表示されば，問題なくインストールされています． （2022/05/24現在），Windows(wsl)だと4.2.0，Macだと4.5.5あたりになります．

