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
    // 读取两张图片
    Mat image1 = imread("/home/csoft/luyao/projects/merging_picture/piano_picture/1.jpg");
    Mat image2 = imread("/home/csoft/luyao/projects/merging_picture/piano_picture/2.jpg");
    Mat image3 = imread("/home/csoft/luyao/projects/merging_picture/piano_picture/3.jpg");
    resize_image(image1);
    resize_image(image2);
    resize_image(image3);


    if (image1.empty() || image2.empty() || image3.empty()) {
        cerr << "Error: Could not load images." << endl;
        return -1;
    }
    
    // 合并两张图片  352   146 400   225
    // resize(image1, image1, Size(image1.cols, image1.rows));
    // resize(image, resizedImage, Size(newWidth, newHeight));
    // resize(image, resizedImage, Size(newWidth, newHeight));
    cout << "Image 1 size: " << image1.cols << " x " << image1.rows << endl;
    cout << "Image 2 size: " << image2.cols << " x " << image2.rows << endl;
    cout << "Image 3 size: " << image3.cols << " x " << image3.rows << endl;

    Mat croppedRegion1 = image1(Rect(0, 0, image1.cols, 352));
    Mat croppedRegion2 = image2(Rect(0, 146, image1.cols, 400-146));
    Mat croppedRegion3 = image3(Rect(0, 225, image3.cols, image3.rows-225));
    // image1 = croppedRegion1;
    // image2 = croppedRegion2;
    // image3 = croppedRegion3;
    rotate(croppedRegion1, image1, ROTATE_90_COUNTERCLOCKWISE);
    rotate(croppedRegion2, image2, ROTATE_90_COUNTERCLOCKWISE);
    rotate(croppedRegion3, image3, ROTATE_90_COUNTERCLOCKWISE);

    Mat mergedImage = Mat::zeros(max(max(image1.rows, image2.rows), image3.rows), image1.cols + image2.cols + image3.cols, image1.type());

    image1.copyTo(mergedImage(Rect(0, 0, image1.cols, image1.rows)));
    image2.copyTo(mergedImage(Rect(image1.cols, 0, image2.cols, image2.rows)));
    image3.copyTo(mergedImage(Rect(image1.cols + image2.cols, 0, image3.cols, image3.rows)));

    // 显示合并后的图片
    // imshow("Image1", image1);
    // imshow("Image2", image2);
    // imshow("Image3", image3);
    cout << "mergedImage size: " << mergedImage.cols << " x " << mergedImage.rows << endl;
    imshow("mergedImage", mergedImage);


    // setMouseCallback("Image", onMouse, &mergedImage);
    waitKey(0);

    // 处理按键重叠，这里简单地演示了图像融合，你可能需要更复杂的算法
    // addWeighted(image1, 0.5, image2, 0.5, 0, image1);

    // 显示处理后的图片
    // imshow("Processed Image", image1);
    // waitKey(0);

    return 0;
}
