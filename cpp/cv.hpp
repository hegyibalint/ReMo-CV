#ifndef REMOCV_CV_H
#define REMOCV_CV_H

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

#include <zbar.h>
#include <opencv2/opencv.hpp>

//#define DEBUG

#define DEBUGX_MAT(mat) cv::imshow("DEBUG", mat); cv::waitKey(0);

#ifdef DEBUG
#define  DEBUG_MAT(mat) DEBUGX_MAT(mat)
#else
#define  DEBUG_MAT(mat)
#endif

namespace remo {
    typedef struct {
        std::string testId;
        cv::Mat testImg;
    } Test;

    std::string read_barcode(cv::Mat img);
    remo::Test extract_test(cv::Mat img);
};

#endif //REMOCV_CV_H
