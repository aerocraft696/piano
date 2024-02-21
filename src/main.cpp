#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 打开默认摄像头（通常是编号为0的摄像头）
    VideoCapture cap(41);

    // 检查摄像头是否成功打开
    if (!cap.isOpened()) {
        cerr << "Error: Could not open camera." << endl;
        return -1;
    }
    int i = 0;
    while (i < 100) {
        // 从摄像头中读取图像帧
        Mat frame;
        cap.read(frame);

        // 检查图像是否为空
        if (frame.empty()) {
            cerr << "Error: Empty frame." << endl;
            break;
        }
        cerr << "start imshow" << i <<endl;
        // 显示图像帧
        imshow("Camera Test", frame);

        cerr << "end imshow" << i <<endl;
        // 按Esc键退出循环
        int key = waitKey(10);
        if (key == '0') {
            break;
        }
        i++;
    }

    // 释放摄像头
    cap.release();
    destroyAllWindows();

    return 0;
}
