// б�Խ�
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>

#if 0




using namespace std;
using namespace cv;

void getContours(Mat& img, Mat& dst) {

    vector<vector<Point>> contours;
    vector<Vec4i>  hierarchy;
    findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    drawContours(dst, contours, -1, Scalar(12, 0, 22), 2);

    // ɾ��̫С�� shape
    for (int i = 0; i < contours.size(); ++i) {
        int area = contourArea(contours[i]);
        cout << i << ": " << area << endl;
    }
}

int main() {

    std::cout << "hello world" << std::endl;
    // ��ȡͼ��
     //std::string path = "head.png";
    //std::string path = "realHead.jpg";
    std::string path = "res/Texture/ͷ��.png";
    cv::Mat img = cv::imread(path);
    cv::resize(img, img, cv::Size(), 0.2, 0.2); // ���ձ�����С

    size_t sz = img.total() * img.elemSize();
    std::cout << "size: " << sz << std::endl;


    imshow("edges", img);

    waitKey(0);


    return 0;

}


#endif // 0