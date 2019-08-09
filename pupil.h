#ifndef PUPIL_H
#define PUPIL_H

#include <iostream>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <algorithm>
#include <QString>
#include <QDebug>

#define IN_BLINK 1
#define NOT_IN_BLINK 0
#define DEFAULT_BLINK_RATE_THRESHOLD 0.4

using namespace std;

class Pupil
{
public:
    Pupil(std::string path);
    ~Pupil();

    double pupil_area;
    double diameter;

    cv::Point pupil_center;
    cv::Mat img_info;
    cv::Mat img_result;
    void draw_point(cv::Mat img, cv::Point center, int size, cv::Scalar line_color);
    double get_pupil_area_by_grayscale(cv::Mat img, int threshold);
    double search_pupil_by_step(cv::Mat img_src, int threshold_value, int step, int step_nums);
    cv::Mat img_preprocess(std::string path);
private:
};

#endif // PUPIL_H
