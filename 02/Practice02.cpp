#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

VideoCapture cap;
Mat src, display;
int currentFrame, totalFrame;

void on_tracker(int p_, void *){
    cap.set(CAP_PROP_POS_FRAMES, p_);
    currentFrame = p_;
    cap.read(src);
}

int main(){
    cap.open("vtest.avi");

    if(!cap.isOpened()) {
        return -1;
    }

    namedWindow("movie", WINDOW_AUTOSIZE);
    totalFrame = (int)cap.get(CAP_PROP_FRAME_COUNT);
    
    createTrackbar("pos", "movie", &currentFrame, totalFrame - 1, on_tracker);

    bool loopflag = true;
    bool paused = false;
    bool gray = false;

    while (loopflag) {
        if (!paused) {
            if (cap.read(src)) {
                currentFrame++;
                setTrackbarPos("pos", "movie", currentFrame);
            } else {
                loopflag = false;
            }
        }

        if (gray) {
            cvtColor(src, display, COLOR_BGR2GRAY);
        } else {
            display = src.clone();
        }

        imshow("movie", display);

        int c = waitKey(10);
        switch (c) {
            case 'e':
                loopflag = false;
                break;
            case 'p':
                paused = !paused;
                break;
            case 'g':
                if (paused && currentFrame < totalFrame - 1) {
                    cap.set(CAP_PROP_POS_FRAMES, ++currentFrame);
                    cap.read(src);
                    setTrackbarPos("pos", "movie", currentFrame);
                }
                break;
            case 'b':
            if (paused && currentFrame > 0) {
                cap.set(CAP_PROP_POS_FRAMES, --currentFrame);
                cap.read(src);
                setTrackbarPos("pos", "movie", currentFrame);
            }
            break;
            case 'r':
                cap.set(CAP_PROP_POS_FRAMES, 0);
                currentFrame = 0;
                cap.read(src);
                setTrackbarPos("pos", "movie", currentFrame);
                break;
            case 'w':
                gray = !gray;
                break;
            default:
                break;
        }
    }

    return 0;
}