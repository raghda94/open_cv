#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

void brightness() {
  Mat image = imread("./images/L2.jpg");
  Mat result = Mat::zeros(image.rows, image.cols, image.type());
  for( int i = 0; i < image.rows; i++) {
    for( int j = 0; j < image.cols; j++) {

      Vec3b I = image.at<cv::Vec3b>(Point(j, i));

      for( int k = 0 ; k < image.channels(); k++)
        result.at<Vec3b>(Point(j,i))[k] = I[k] + 50 > 255 ? 255 : I[k]+50;

    }
  }
  imwrite("./ex3.jpg", result);

}
