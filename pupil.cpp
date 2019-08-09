#include "pupil.h"

//#define PICTURE_DEBUG_MODE_ON
//#define CONTOURS_DEBUG_MODE_ON
using namespace cv;

Pupil::Pupil(std::string path)
{
    this -> pupil_area = 0;
    this->img_info = this->img_preprocess(path);
}

Pupil::~Pupil()
{
}


void Pupil::draw_point(Mat img, Point center, int size, Scalar line_color) {
    int x_of_center = center.x;
    int y_of_center = center.y;

    Point horizontal_start, vertical_start, horizontal_end, vertical_end;
    horizontal_start.x = x_of_center - size, horizontal_start.y = y_of_center;
    horizontal_end.x = x_of_center + size, horizontal_end.y = y_of_center;
    vertical_start.x = x_of_center, vertical_start.y = y_of_center - size;
    vertical_end.x = x_of_center, vertical_end.y = y_of_center + size;
    line(img, horizontal_start, horizontal_end, line_color);
    line(img, vertical_start, vertical_end, line_color);
}

double Pupil::get_pupil_area_by_grayscale(Mat img_src, int threshold_value) {
    double pupil_area = 0;
    double diameter = 0;
    Mat img = img_src;
    Mat thresh_gray;
    if(img.empty()){
        qDebug() << "no pupil found!!";
        this->pupil_area = pupil_area;
        this->diameter = diameter;
        this->pupil_center = Point(0,0);
        this->img_result = img_src;
        return 0;
    }
    cvtColor(img_src, img, COLOR_BGR2GRAY);

    threshold(img, thresh_gray, threshold_value, 255, THRESH_BINARY);

    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    findContours(thresh_gray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    float img_src_height = img.rows;
    float img_src_width = img.cols;
#ifdef CONTOURS_DEBUG_MODE_ON
    for (int i = 0; i < contours.size(); i++) {
        drawContours(img_src, contours, i, Scalar(0, 255, 0), 1, 8, hierarchy, 0, Point(0, 0));
    }

#endif // CONTOURS_DEBUG_MODE_ON
//    Point contour_center = (0, 0);
    Point contour_center;
    contour_center.x = 0;
    contour_center.y = 0;
    for (int i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]);
        Rect rect = boundingRect(contours[i]);
        //RotatedRect ellip = fitEllipse(contours[i]);
        float rect_x_start = rect.x, rect_y_start = rect.y, rect_height = rect.height, rect_width = rect.width;
        bool area_condition = area >= 1500 && area <= 30000;
        bool diameter_condition = rect_width >= 60 && rect_width <= 150;
        bool symetry_condition = (abs(1 - rect_width / rect_height) <= 0.5);
        //bool x_coord_con = (float(img_src_height) / 4 <= rect_x_start + 60 <= float(img_src_height) * 3 / 4);
        //bool y_coord_con = (float(img_src_width) / 4 <= rect_y_start + 60 <= float(img_src_width) * 3 / 4);
        float contour_lenth = arcLength(contours[i], true);
        float min_radius = std::min(rect_width, rect_height);
        float max_radius = std::max(rect_height, rect_width);
        //bool arclen_radius_condition = (contour_lenth >= 2.9 * min_radius && contour_lenth <= 3.3 * max_radius && area / contour_lenth <= max_radius * 4);
        bool rect_cirle_area = (min_radius * max_radius / area <= 1.6);
#ifdef PICTURE_DEBUG_MODE_ON
        std::cout << "contour_Lenth : " << contour_lenth << std::endl;
        std::cout << "area_condition : " << area_condition << std::endl;
        std::cout << "symetry_conditon : " << symetry_condition << std::endl;
        //std::cout << "arclen_radius_condition : " << arclen_radius_condition << std::endl;
        std::cout << "rect_circle_area : " << rect_cirle_area << std::endl;
#endif // PICTURE_DEBUG_MODE_ON

        if (area_condition && rect_cirle_area && diameter_condition) {
            drawContours(img_src, contours, i, Scalar(0, 255, 0), 1, 8, hierarchy, 0, Point(0, 0));

            contour_center.x = rect_x_start + rect_width / 2;
            contour_center.y = rect_y_start + rect_height / 2;
            circle(img_src, Point(contour_center.x, contour_center.y), rect_width / 2, Scalar(0, 0, 255), 3);
            this -> draw_point(img_src, contour_center, 5, Scalar(255, 255, 255));
            pupil_area = area;
            diameter = rect_width;
        }
    }

    this->pupil_area = pupil_area;
    this->diameter = diameter;
    this->pupil_center = contour_center;
    this->img_result = img_src;
#ifdef PICTURE_DEBUG_MODE_ON
    std::cout << "The num of contours is :" << contours.size() << std::endl;
    std::cout << "The area of pupil_area is : " << pupil_area << std::endl;
    std::cout << "Ther center coordinate is : (" << contour_center.x << "," << contour_center.y << ")" << std::endl;
    std::cout << "" << std::endl;
    namedWindow("contours");
    imshow("contours", img_src);
    namedWindow("picture");
    imshow("picture", thresh_gray);
    waitKey(0);
#endif // PICTURE_DEBUG_MODE_ON
    return pupil_area;
}

double Pupil::search_pupil_by_step(Mat img_src, int threshold_value, int step, int step_nums) {
    double pupil_area = 0;

    for (int i = 0; i < step_nums; ++i) {
        if (pupil_area) break;
        else {
            pupil_area = this->get_pupil_area_by_grayscale(img_src, threshold_value - step*i);
            if (pupil_area) break;
            pupil_area = this->get_pupil_area_by_grayscale(img_src, threshold_value + step*i);
        }
    }
    return pupil_area;
}

// 该函数用于适应以后可能会涉及到的图片预处理操作，目前只是读取图片
Mat Pupil::img_preprocess(std::string path) {
    return imread(path);
}
