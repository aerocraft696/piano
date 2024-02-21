#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>

using namespace cv;
using namespace std;

void resize_image(Mat& image) {
    int originalWidth = image.cols;
    int originalHeight = image.rows;
    int newWidth = originalWidth / 2;
    int newHeight = originalHeight / 2;
    Mat resizedImage;
    resize(image, resizedImage, Size(newWidth, newHeight));
    image = resizedImage;
}

void captureThread(VideoCapture& cap, Mat& image) {
    while (true) {
        cap.read(image);
        resize_image(image);
    }
}

int main() {
    VideoCapture cap1(41);
    VideoCapture cap2(43);
    VideoCapture cap3(45);

    if (!cap1.isOpened() || !cap2.isOpened() || !cap3.isOpened()) {
        cerr << "Error: Could not open camera." << endl;
        return -1;
    }

    Mat image1, image2, image3;

    // 启动三个线程，分别捕获图像
    thread t1(captureThread, std::ref(cap1), std::ref(image1));
    thread t2(captureThread, std::ref(cap2), std::ref(image2));
    thread t3(captureThread, std::ref(cap3), std::ref(image3));

    while (true) {
        // 合并三张图像
        Mat mergedImage = Mat::zeros(max(max(image1.rows, image2.rows), image3.rows),
                                     image1.cols + image2.cols + image3.cols, image1.type());

        image1.copyTo(mergedImage(Rect(0, 0, image1.cols, image1.rows)));
        image2.copyTo(mergedImage(Rect(image1.cols, 0, image2.cols, image2.rows)));
        image3.copyTo(mergedImage(Rect(image1.cols + image2.cols, 0, image3.cols, image3.rows)));

        // 显示合并后的图片
        imshow("Merged Image", mergedImage);

        // 按Esc键退出循环
        string userInput;
        cin >> userInput;
        if (userInput == "00") {
            break;
        }
    }

    // 等待线程结束
    t1.join();
    t2.join();
    t3.join();

    // 释放摄像头
    cap1.release();
    cap2.release();
    cap3.release();
    destroyWindow("Merged Image");
    return 0;
}
