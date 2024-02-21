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

// 函数：缩小图像（手动实现）
void resize_image(Mat& image) {
    int originalWidth = image.cols;
    int originalHeight = image.rows;
    int newWidth = originalWidth / 2;
    int newHeight = originalHeight / 2;

    Mat resizedImage(newHeight, newWidth, image.type());

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            for (int c = 0; c < image.channels(); ++c) {
                int sum = 0;
                // 取周围四个像素的平均值
                sum += image.at<Vec3b>(2 * y, 2 * x)[c];
                sum += image.at<Vec3b>(2 * y, 2 * x + 1)[c];
                sum += image.at<Vec3b>(2 * y + 1, 2 * x)[c];
                sum += image.at<Vec3b>(2 * y + 1, 2 * x + 1)[c];
                resizedImage.at<Vec3b>(y, x)[c] = static_cast<uchar>(sum / 4);
            }
        }
    }

    image = resizedImage.clone();  // 使用 clone() 来保留图像类型和尺寸
}

// 函数：合并图像（手动实现）
void merge_images(Mat& mergedImage, const Mat& image1, const Mat& image2, const Mat& image3) {
    int mergedWidth = image1.cols + image2.cols + image3.cols;
    int mergedHeight = max(max(image1.rows, image2.rows), image3.rows);

    mergedImage = Mat::zeros(mergedHeight, mergedWidth, image1.type());

    // 拷贝图像数据，如果越界则填充0
    for (int y = 0; y < mergedHeight; ++y) {
        for (int x = 0; x < mergedWidth; ++x) {
            if (x < image1.cols && y < image1.rows) {
                mergedImage.at<Vec3b>(y, x) = image1.at<Vec3b>(y, x);
            } else if (x >= image1.cols && x < image1.cols + image2.cols && y < image2.rows) {
                mergedImage.at<Vec3b>(y, x) = image2.at<Vec3b>(y, x - image1.cols);
            } else if (x >= image1.cols + image2.cols && y < image3.rows) {
                mergedImage.at<Vec3b>(y, x) = image3.at<Vec3b>(y, x - image1.cols - image2.cols);
            }
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

    Mat image1, image2, image3;
    int i = 0;
    while (i < 1000) {
        cap1.read(image1);
        cap2.read(image2);
        cap3.read(image3);

        resize_image(image1);
        resize_image(image2);
        resize_image(image3);

        Mat mergedImage;
        merge_images(mergedImage, image1, image2, image3);
        imshow("Merged Image1", image1);
        // imshow("Merged Image2", mergedImage);

        cout << "Enter '00' to exit: ";
        string userInput;
        cin >> userInput;
        if (userInput == "00") {
            break;
        }
        // i++;
    }

    cap1.release();
    cap2.release();
    cap3.release();

    destroyAllWindows();

    return 0;
}
