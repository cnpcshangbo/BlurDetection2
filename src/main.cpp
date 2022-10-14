#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <cstring>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <iomanip>
#include <nlohmann/json.hpp>
#include <chrono>

using json = nlohmann::json;

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

double blur_detection(const string& filename){
    Mat image;
    image = imread( filename, 1 );
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
    return variance;
}

std::string ver_string(int a, int b, int c) {
  std::ostringstream ss;
  ss << a << '.' << b << '.' << c;
  return ss.str();
}

int main(int argc, char** argv )
{
    std::string true_cxx =
    #ifdef __clang__
    "clang++";
    #else
    "g++";
    #endif

    std::string true_cxx_ver =
    #ifdef __clang__
        ver_string(__clang_major__, __clang_minor__, __clang_patchlevel__);
    #else
        ver_string(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    #endif

    cout << true_cxx << endl;
    cout << true_cxx_ver << endl;

    string foldername = "/usr/local/home/bsr8w/code/Monocular-Visual-Odometry/data/vid2img_extra_small/";
    string filename;
    json j;
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path> eg: /usr/local/home/bsr8w/code/Monocular-Visual-Odometry/data/vid2img_extra_small/rgb_00001.jpg\n");
        printf("using default path /usr/local/home/bsr8w/code/Monocular-Visual-Odometry/data/vid2img_extra_small/rgb_00001.jpg");
        filename = "/usr/local/home/bsr8w/code/Monocular-Visual-Odometry/data/vid2img_extra_small/rgb_00001.jpg";
        // return -1;
        
        // // Iterate over the `std::filesystem::directory_entry` elements explicitly
        // for (const fs::directory_entry& dir_entry : 
        //     fs::recursive_directory_iterator(foldername))
        // {
        //     std::cout << dir_entry << '\n';
        // }
        std::cout << "-----------------------------\n";
        
        // Iterate over the `std::filesystem::directory_entry` elements using `auto`
        for (auto const& dir_entry : fs::recursive_directory_iterator(foldername))
        {
            string filename = dir_entry.path();
            std::cout << filename << '\n';
            double score = blur_detection(filename);
            cout << score << endl;
            double blurThreshold = 300;
            bool blurry;
            if ( score <= blurThreshold ) {
                std::cout<<"Input image is blurry!"<<std::endl;
                blurry = true;
            } else {
                std::cout<<"Input image is sharp"<<std::endl;
                blurry = false;
            }
            const auto p1 = std::chrono::system_clock::now();
            const auto time = std::chrono::duration_cast<std::chrono::seconds>(
                   p1.time_since_epoch()).count();
            // j["results"]["input_path"] = filename;
            // j["results"]["score"] = score;
            // j["results"]["time"] = time;
            j["results"].push_back({{"input_path", filename}, {"score", score}, {"blurry", blurry}, {"time", time}});

        }
    
    }

    
    // pretty print with indent of 4 spaces
    std::cout << std::setw(4) << j << '\n';
    // write prettified JSON to another file
    std::ofstream o("pretty.json");
    o << std::setw(4) << j << std::endl;
    waitKey(0);
    return 0;
}