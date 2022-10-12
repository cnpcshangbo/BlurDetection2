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

    cv::Mat laplacianImage;
    cv::Laplacian(greyMat, laplacianImage, CV_64F);

    // Prepare to compute the mean and standard deviation of the laplacian:
    // https://stackoverflow.com/questions/60587428/how-to-detect-blur-rate-of-a-face-effectively-in-c
    cv::Scalar mean, stddev; 
    cv::meanStdDev( laplacianImage, mean, stddev, cv::Mat() );

    //Let’s compute the variance:
    double variance = stddev.val[0] * stddev.val[0];
    cout << "variance = " << variance << endl;

    double blurThreshold = 300;

    if ( variance <= blurThreshold ) {
        std::cout<<"Input image is blurry!"<<std::endl;
    } else {
        std::cout<<"Input image is sharp"<<std::endl;
    }
    waitKey(0);
    return 0;
}