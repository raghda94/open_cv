#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat scale(Mat, Mat);

void blend() {

  Mat image = imread("./images/L1.jpg");
  Mat logo = scale(image, imread("./images/logo.jpg"));

  Mat result = Mat::zeros(image.rows, image.cols, image.type());

  for( int i = 0; i < result.rows; i++) {
    for( int j = 0; j < result.cols; j++) {

      Vec3b I0 = image.at<Vec3b>(Point(j, i));
      Vec3b I1 = logo.at<Vec3b>(Point(j, i));

      for( int k = 0 ; k < image.channels(); k++)
        result.at<Vec3b>(Point(j,i))[k] = I0[k] * 0.8 + I1[k] * 0.2;

    }
  }

  imwrite("./ex2.jpg", result);
}


Mat scale(Mat image, Mat logo) {
  Mat result = Mat(image.rows, image.cols, image.type());

  Mat s = Mat::zeros(3, 3, 5);
  s.at<float>(0, 0) = (image.cols * 1.0) / logo.cols;
  s.at<float>(1, 1) = (image.rows * 1.0) / logo.rows;
  s.at<float>(2, 2) = 1.0;

  Mat inverse = s.inv();

  for( int i = 0; i < result.rows; i++ ) {
    for( int j = 0; j < result.cols; j++ ) {
      Mat xy = Mat::ones(3, 1, 5);
      xy.at<float>(0, 0) = j;
      xy.at<float>(1, 0) = i;
      result.at<Vec3b>(Point(j,i)) = billinearInterpolation(logo, inverse * xy  );
    }
  }

  return result;
}
