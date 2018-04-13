#include "cv.hpp"

std::string remo::read_barcode(cv::Mat img) {
    cv::Mat roi;
    roi = img(cv::Rect(100, 100, img.cols - 200, img.rows - 200));

    cv::Mat gray;
    cv::cvtColor(roi, gray, cv::COLOR_BGR2GRAY);

    cv::Mat thresholded;
    cv::threshold(gray, thresholded, 120, 255, cv::THRESH_BINARY);

    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 0);
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_X_DENSITY, 0);
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_Y_DENSITY, 1);
    scanner.set_config(zbar::ZBAR_CODE128, zbar::ZBAR_CFG_ENABLE, 1);

    zbar::Image zimage(static_cast<unsigned int>(thresholded.cols),
                       static_cast<unsigned int>(thresholded.rows),
                       "Y800",
                       thresholded.data,
                       static_cast<unsigned int>(thresholded.cols * thresholded.rows));
    scanner.scan(zimage);

    auto symbolSet = scanner.get_results();
    if (symbolSet.get_size() != 1) {
        std::stringstream ss;
        ss << "The number of barcodes are not correct (" << symbolSet.get_size() << ")";
    }

    return symbolSet.symbol_begin()->get_data();
}

remo::Test remo::extract_test(cv::Mat img) {
    DEBUG_MAT(img)

    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    DEBUG_MAT(gray)

    cv::Mat closed;
    cv::morphologyEx(
            gray,
            closed,
            cv::MORPH_CLOSE,
            cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5))
    );
    DEBUG_MAT(closed)

    cv::Mat gradient;
    cv::morphologyEx(
            closed,
            gradient,
            cv::MORPH_GRADIENT,
            cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3))
    );
    DEBUG_MAT(gradient)

    cv::Mat thresholded;
    cv::threshold(gradient, thresholded, 25, 255, cv::THRESH_BINARY);
    DEBUG_MAT(thresholded);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresholded, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_TC89_L1);

#ifdef DEBUG
    cv::Mat contour_debug;
    img.copyTo(contour_debug);
    cv::drawContours(contour_debug, contours, -1, cv::Scalar(0, 255, 0));
    DEBUG_MAT(contour_debug);
#endif

    const int pageArea = gray.rows * gray.cols;
    for (auto &contour : contours) {
        cv::RotatedRect rect = cv::minAreaRect(contour);

#ifdef DEBUG
        if (rect.size.area() / pageArea > 0.1) {
            std::cout << fabs(rect.size.area() / pageArea) << std::endl;
            std::cout << fabs(rect.size.width / rect.size.height) << std::endl;
            std::cout << fabs(rect.angle) << std::endl;
            std::cout << fabs(fabs(rect.angle) - 0.54462) << std::endl;
            std::cout << "---" << std::endl;

        }
#endif

        const double area = rect.size.area() / pageArea;
        double angle;
        double aspect;
        cv::Size2f size;
        if (rect.size.width > rect.size.height) {
            angle = rect.angle;
            aspect = rect.size.width / rect.size.height;
            size = cv::Size2f(rect.size.width, rect.size.height);
        } else {
            angle = 90 + rect.angle;
            aspect = rect.size.height / rect.size.width;
            size = cv::Size2f(rect.size.height, rect.size.width);
        }

        if (angle > 2.0
            || area < 0.23
            || area > 0.25
            || aspect < 2.15
            || aspect > 2.35) {
            continue;
        }

#ifdef DEBUG
        drawContours(contour_debug, std::vector<std::vector<cv::Point>>(1, contour), -1, cv::Scalar(0, 0, 255), 3);
        DEBUG_MAT(contour_debug);

        cv::Mat rect_debug;
        img.copyTo(rect_debug);
        cv::Point2f points[4];
        rect.points(points);
        cv::line(rect_debug, points[0], points[1], cv::Scalar(255, 0, 0), 3);
        cv::line(rect_debug, points[1], points[2], cv::Scalar(255, 0, 0), 3);
        cv::line(rect_debug, points[2], points[3], cv::Scalar(255, 0, 0), 3);
        cv::line(rect_debug, points[3], points[0], cv::Scalar(255, 0, 0), 3);
        DEBUG_MAT(rect_debug);

        std::cout << "Area:     " << area << std::endl;
        std::cout << "Aspect:   " << aspect << std::endl;
        std::cout << "Rotation: " << angle << std::endl;
        std::cout << "----------------" << std::endl;
#endif

        cv::Mat rotm = cv::getRotationMatrix2D(rect.center, angle, 1.0);
        cv::Mat warped;
        cv::warpAffine(
                img,
                warped,
                rotm,
                img.size()
        );
        DEBUG_MAT(warped);

        cv::Mat test;

        cv::getRectSubPix(warped, size, rect.center, test);
        DEBUG_MAT(test);

        std::string barcode = ";;;";
        barcode = read_barcode(warped);

        return {barcode, test};
    }

    throw std::runtime_error("Cannot find test in the page");
}