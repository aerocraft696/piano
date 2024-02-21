#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <mutex>

using namespace cv;
using namespace std;

mutex mtx;
void resize_image(UMat& image) {
    int originalWidth = image.cols;
    int originalHeight = image.rows;
    int newWidth = originalWidth / 2;
    int newHeight = originalHeight / 2;
    resize(image, image, Size(newWidth, newHeight));
}

void captureThread(VideoCapture& cap, UMat& image) {
    while (true) {
        Mat tempImage;
        cap.read(tempImage);

        {
            lock_guard<mutex> lock(mtx);
            tempImage.copyTo(image);  // 使用 copyTo 复制图像
            resize_image(image);
        }
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

    UMat image1, image2, image3;

    // 启动三个线程，分别捕获图像
    thread t1(captureThread, std::ref(cap1), std::ref(image1));
    thread t2(captureThread, std::ref(cap2), std::ref(image2));
    thread t3(captureThread, std::ref(cap3), std::ref(image3));

    while (true) {
        // 合并三张图像
        UMat mergedImage = UMat::zeros(max(max(image1.rows, image2.rows), image3.rows),
                                      image1.cols + image2.cols + image3.cols, image1.type());

        {
            lock_guard<mutex> lock(mtx);
            image1.copyTo(mergedImage(Rect(0, 0, image1.cols, image1.rows)));
            image2.copyTo(mergedImage(Rect(image1.cols, 0, image2.cols, image2.rows)));
            image3.copyTo(mergedImage(Rect(image1.cols + image2.cols, 0, image3.cols, image3.rows)));
        }

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
    destroyAllWindows();

    return 0;
}
