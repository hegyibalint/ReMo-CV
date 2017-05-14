#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "cv.hpp"

typedef struct {
    double radius;
    double hoffset;
    double voffset;
    double hspacing;
    double vspacing;
} Calibration;

enum TestAnswer {
    UNANSWERED = '-',
    TRUE = 'i',
    FALSE = 'h',
    CORRECTED = 'x'
};

bool get_answer(cv::Mat answer, int diam, cv::Point2i center) {
    cv::Mat roi;
    cv::getRectSubPix(answer, cv::Size2i(diam, diam), center, roi);
    //DEBUG_MAT(roi);

    cv::Mat mask = cv::getStructuringElement(cv::MORPH_ELLIPSE, roi.size());
    //DEBUG_MAT(mask);

    cv::Mat masked = roi.mul(mask);
    DEBUG_MAT(masked);

    return cv::countNonZero(masked) > (cv::countNonZero(mask) * 0.05);
}

std::vector<TestAnswer> check_answers(cv::Mat test, Calibration calib) {
    cv::Mat gray;
    cv::cvtColor(test, gray, cv::COLOR_BGR2GRAY);
    DEBUG_MAT(gray);

    cv::Mat thresholded;
    cv::threshold(gray, thresholded, 200, 255, cv::THRESH_BINARY_INV);
    DEBUG_MAT(thresholded);

    const int diam = cvRound(test.cols * calib.radius) - 1;

    std::vector<TestAnswer> answers;
    for (int y = 0; y < 8 ; ++y) {
        for (int x = 0; x < 8; x+=2) {
            bool true_box = get_answer(thresholded, diam, cv::Point2i(
                    cvRound(test.cols * calib.hoffset + x * test.cols * calib.hspacing),
                    cvRound(test.rows * calib.voffset + y * test.rows * calib.vspacing)
            ));
            bool false_box = get_answer(thresholded, diam, cv::Point2i(
                    cvRound(test.cols * calib.hoffset + (x+1) * test.cols * calib.hspacing),
                    cvRound(test.rows * calib.voffset + y * test.rows * calib.vspacing)
            ));

            if (!true_box && !false_box) {
                answers.emplace_back(TestAnswer::UNANSWERED);
            } else if (true_box && !false_box) {
                answers.emplace_back(TestAnswer::TRUE);
            } else if (!true_box && false_box) {
                answers.emplace_back(TestAnswer::FALSE);
            } else if (true_box && false_box) {
                answers.emplace_back(TestAnswer::CORRECTED);
            }
        }
    }

    return answers;
}

int main(int argc, char *argv[]) {
    std::ifstream calibFile("params.conf");

    Calibration calib;
    calibFile >> calib.radius;
    calibFile >> calib.hoffset;
    calibFile >> calib.voffset;
    calibFile >> calib.hspacing;
    calibFile >> calib.vspacing;

    std::cout << "Horizontal offset:\t" << calib.hoffset << std::endl;
    std::cout << "Vertical offset:\t" << calib.voffset << std::endl;
    std::cout << "Horizontal spacing:\t" << calib.hspacing << std::endl;
    std::cout << "Vertical spacing:\t" << calib.vspacing << std::endl;
    std::cout << "------------------------" << std::endl;

    std::ofstream resultFile("results.csv");
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
        try {
            cv::Mat img = cv::imread(argv[i], cv::IMREAD_COLOR);
            if (img.cols == 0 && img.rows == 0) {
                throw std::runtime_error("File cannot be read");
            }

            remo::Test testS = remo::extract_test(img);
            std::vector<TestAnswer> answers = check_answers(testS.testImg, calib);

            resultFile << argv[i] << ";";
            resultFile << testS.testId << ";";
            std::cout << testS.testId << ";";

            for (auto answer : answers) {
                resultFile << char(answer) << ";";
                std::cout << char(answer) << ";";
            }
            resultFile << std::endl;
            std::cout << std::endl;

        } catch (std::runtime_error e) {
            std::cerr << e.what() << std::endl;
        }
    }
}