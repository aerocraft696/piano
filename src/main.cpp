#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_MOUSEMOVE) {
        Mat* image = static_cast<Mat*>(userdata);

        // 检查鼠标位置是否在图像范围内
        if (x >= 0 && x < image->cols && y >= 0 && y < image->rows) {
            Vec3b pixel = image->at<Vec3b>(y, x);  // 获取像素值
            printf("Pixel at (%d, %d): B=%d, G=%d, R=%d\n", x, y, pixel[0], pixel[1], pixel[2]);
        }
    }
}
void resize_image(Mat& image){
    // 获取原始图像的宽度和高度
    int originalWidth = image.cols;
    int originalHeight = image.rows;

    // 将图像的长和宽缩短为原来的一半
    int newWidth = originalWidth / 2;
    int newHeight = originalHeight / 2;
    Mat resizedImage;
    resize(image, resizedImage, Size(newWidth, newHeight));
    image = resizedImage;
}
int main() {
    VideoCapture cap1(41);
    VideoCapture cap2(43);
    VideoCapture cap3(45);
    // 摄像头编号: 41 42    43 44   45 46
    if (!cap1.isOpened() || !cap2.isOpened() || !cap3.isOpened()) {
        cerr << "Error: Could not open camera." << endl;
        return -1;
    }
    Mat image1, image2, image3;   
    int i = 0;
    while (i < 100) {
        // 从摄像头中读取图像
        cap1.read(image1);
        cap2.read(image2);
        cap3.read(image3);

        // 对每个图像进行处理（缩小）
        resize_image(image1);
        resize_image(image2);
        resize_image(image3);

        // 在这里添加其他对图像的处理，比如裁剪、旋转等

        // 合并三张图像
        Mat mergedImage = Mat::zeros(max(max(image1.rows, image2.rows), image3.rows),
                                     image1.cols + image2.cols + image3.cols, image1.type());

        image1.copyTo(mergedImage(Rect(0, 0, image1.cols, image1.rows)));
        image2.copyTo(mergedImage(Rect(image1.cols, 0, image2.cols, image2.rows)));
        image3.copyTo(mergedImage(Rect(image1.cols + image2.cols, 0, image3.cols, image3.rows)));
        string filename = "merged_image.png";
        imwrite(filename, mergedImage);
        // 显示合并后的图片
        imshow("Merged Image", mergedImage);

        // 设置鼠标回调
        // setMouseCallback("Merged Image", onMouse, &mergedImage);

        // // 按Esc键退出循环
        // string userInput;
        // cin >> userInput;
        // if (userInput == "00") {
        //     break;
        // }
        i++;
    }
    // 释放摄像头
    cap1.release();
    cap2.release();
    cap3.release();
    destroyAllWindows();
    return 0;
}
