#include <exception>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "cv.hpp"

//#define DEBUG

void onTrackbarChange(int pos, void* userdata) {
    cv::Mat* img = static_cast<cv::Mat*>(userdata);
    cv::Mat copy;
    img->copyTo(copy);

    double radius = cv::getTrackbarPos("CIRCLE", "ADJUST") / 10000.0;
    double hoffset = cv::getTrackbarPos("HOFFSET", "ADJUST") / 10000.0;
    double voffset = cv::getTrackbarPos("VOFFSET", "ADJUST") / 10000.0;
    double hspacing = cv::getTrackbarPos("HSPACING", "ADJUST") / 10000.0;
    double vspacing = cv::getTrackbarPos("VSPACING", "ADJUST") / 10000.0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int x = static_cast<int>(copy.cols * (hoffset + i * hspacing));
            int y = static_cast<int>(copy.rows * (voffset + j * vspacing));
            cv::Point p(x, y);
            cv::circle(copy, p, cvRound(copy.cols * radius), cv::Scalar(255,0,0), cv::FILLED);
        }
    }

    cv::imshow("ADJUST", copy);
}

int main(int argc, char* argv[]) {
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (img.cols == 0 && img.rows == 0) {
        throw std::runtime_error("File cannot be read");
    }
    remo::Test testS = remo::extract_test(img);
    cv::Mat test = testS.testImg;

    int start = 0;
    cv::namedWindow("ADJUST");
    cv::createTrackbar("CIRCLE", "ADJUST", &start, 10000, onTrackbarChange, &test);
    cv::createTrackbar("HOFFSET", "ADJUST", &start, 10000, onTrackbarChange, &test);
    cv::createTrackbar("VOFFSET", "ADJUST", &start, 10000, onTrackbarChange, &test);
    cv::createTrackbar("VSPACING", "ADJUST", &start, 10000, onTrackbarChange, &test);
    cv::createTrackbar("HSPACING", "ADJUST", &start, 10000, onTrackbarChange, &test);

    onTrackbarChange(0, &test);
    cv::waitKey(0);

    int radius = cv::getTrackbarPos("CIRCLE", "ADJUST");
    int hoffset = cv::getTrackbarPos("HOFFSET", "ADJUST");
    int voffset = cv::getTrackbarPos("VOFFSET", "ADJUST");
    int hspacing = cv::getTrackbarPos("HSPACING", "ADJUST");
    int vspacing = cv::getTrackbarPos("VSPACING", "ADJUST");

    std::ofstream file("params.conf");
    file << radius / 10000.0 << std::endl;
    file << hoffset / 10000.0 << std::endl;
    file << voffset / 10000.0 << std::endl;
    file << hspacing / 10000.0 << std::endl;
    file << vspacing / 10000.0 << std::endl;

    return 0;
}