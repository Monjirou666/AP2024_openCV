#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

Mat src, dst;
int blurAmount, brightness, contrast;

void on_tracker_blur(int, void*) {
    medianBlur(src, dst, blurAmount * 2 + 1);
    imshow("Display", dst);
}

void updateImage() {
    src.convertTo(dst, -1, contrast/100.0, brightness - 50);
    imshow("Display", dst);
}

void on_tracker_brightness(int, void*) {
    updateImage();
}

void on_tracker_contrast(int, void*) {
    updateImage();
}

int main() {
    src = imread("lena.jpg");

    namedWindow("Display", WINDOW_AUTOSIZE);

    createTrackbar("blur", "Display", &blurAmount, 21, on_tracker_blur);
    createTrackbar("brightness", "Display", &brightness, 100, on_tracker_brightness);
    createTrackbar("contrast", "Display", &contrast, 100, on_tracker_contrast);

    setTrackbarPos("blur", "Display", 1);
    setTrackbarPos("brightness", "Display", 50);
    setTrackbarPos("contrast", "Display", 50);

    on_tracker_blur(blurAmount, 0);
    updateImage();

    while (waitKey(100) < 0) {
    }

    return 0;
}
