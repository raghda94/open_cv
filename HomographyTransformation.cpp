#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

/*
  1.....2
  4.....3
*/
// Matx31f xs(12, 991, 912);
// Matx31f ys(7, 139, 690);
#define FIRST_POINT_X_1  57
#define FIRST_POINT_Y_1  57

#define SECOND_POINT_X_1  191
#define SECOND_POINT_Y_1  24

#define THIRD_POINT_X_1  188
#define THIRD_POINT_Y_1  148

#define FOURTH_POINT_X_1  57
#define FOURTH_POINT_Y_1  186

void homographyTransformation(){
  Mat image = imread("./images/L4.jpg");

  vector<Point2f> src;
  src.push_back(Point2f(FIRST_POINT_X_1, FIRST_POINT_Y_1));
  src.push_back(Point2f(SECOND_POINT_X_1, SECOND_POINT_Y_1));
  src.push_back(Point2f(THIRD_POINT_X_1, THIRD_POINT_Y_1));
  src.push_back(Point2f(FOURTH_POINT_X_1, FOURTH_POINT_Y_1));

  // src.push_back(Point2f(57, 57));src.push_back(Point2f(191, 24));
  // src.push_back(Point2f(188, 148));src.push_back(Point2f(57, 186));


  vector<Point2f> dest;
  dest.push_back(Point2f(0, 0));
  dest.push_back(Point2f( image.cols - 1, 0));
  dest.push_back(Point2f(image.cols - 1, image.rows - 1));
  dest.push_back(Point2f(0, image.rows - 1));

  Mat M = findHomography(src, dest);
  Mat result;
  warpPerspective(image, result, M, image.size());

  imwrite("./ex5.jpg", result);
}
