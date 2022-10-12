#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path> eg: /usr/local/home/bsr8w/code/Monocular-Visual-Odometry/data/vid2img_extra_small\n");
        return -1;
    }
    Mat image;
    image = imread( argv[1], 1 );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    std::cout << typeid(image).name() << std::endl;
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    cv::Mat greyMat;
    cv::cvtColor(image, greyMat, cv::COLOR_BGR2GRAY);
    namedWindow("Grey Image", WINDOW_AUTOSIZE );
    imshow("Grey Image", greyMat);

    cv::Mat blur_map = cv2::Laplacian(greyMat, cv2.CV_64F);

    waitKey(0);
    return 0;
}