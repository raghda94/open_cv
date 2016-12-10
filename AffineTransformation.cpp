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
#define FIRST_POINT_X  12
#define FIRST_POINT_Y  7

#define SECOND_POINT_X  991
#define SECOND_POINT_Y  139

#define THIRD_POINT_X  912
#define THIRD_POINT_Y  690

#define FOURTH_POINT_X  66
#define FOURTH_POINT_Y  466

void affineTransform() {

  Mat image = imread("./images/L3.jpg");
  Mat result = Mat::zeros(image.rows, image.cols, image.type());

  Mat M = Mat::ones(3, 3, 5);
  M.at<float>(0, 0) = FIRST_POINT_X; M.at<float>(0, 1) = FIRST_POINT_Y;
  M.at<float>(1, 0) = SECOND_POINT_X; M.at<float>(1, 1) = SECOND_POINT_Y;
  M.at<float>(2, 0) = THIRD_POINT_X; M.at<float>(2, 1) = THIRD_POINT_Y;

  Mat inverse = M.inv();

  Mat x = Mat::zeros(3, 1, 5);
  Mat y = Mat::zeros(3, 1, 5);
  x.at<float>(1, 0) = image.cols - 1; x.at<float>(2, 0) = image.cols - 1;
  y.at<float>(2, 0) = image.rows - 1;

  Mat v[] = {inverse * x, inverse * y, inverse * Mat::ones(3, 1, 5)};
  Mat firstAffine = Mat::zeros(3 , 3, 5);

  for(int i = 0; i < firstAffine.rows; i++)
    for(int j = 0; j < firstAffine.cols; j++)
      firstAffine.at<float>(i, j) = v[i].at<float>(j, 0);

  Mat inverseFirstAffine = firstAffine.inv();

  Mat M2 = Mat::ones(3, 3, 5);
  M2.at<float>(0, 0) = FIRST_POINT_X; M2.at<float>(0, 1) = FIRST_POINT_Y;
  M2.at<float>(1, 0) = FOURTH_POINT_X; M2.at<float>(1, 1) = FOURTH_POINT_Y;
  M2.at<float>(2, 0) = THIRD_POINT_X; M2.at<float>(2, 1) = THIRD_POINT_Y;

  inverse = M2.inv();

  Mat x2 = Mat::zeros(3, 1, 5);
  Mat y2 = Mat::zeros(3, 1, 5);
  x2.at<float>(2, 0) = image.cols - 1;
  y2.at<float>(1, 0) = image.rows - 1; y2.at<float>(2, 0) = image.rows - 1;

  Mat v2[] = {inverse * x2, inverse * y2, inverse * Mat::ones(3, 1, 5)};
  Mat secondAffine = Mat::zeros(3 , 3, 5);

  for(int i = 0; i < secondAffine.rows; i++)
    for(int j = 0; j < secondAffine.cols; j++)
      secondAffine.at<float>(i, j) = v2[i].at<float>(j, 0);

  Mat inverseSecondAffine = secondAffine.inv();


  float slope = (image.rows * 1.0) / image.cols;

  for( int i = 0; i < result.rows; i++) {
    for( int j = 0; j < result.cols; j++ ) {

      Mat xy = Mat::ones(3, 1, 5);
      xy.at<float>(0, 0) = j;
      xy.at<float>(1, 0) = i;

      if( i - slope * j < 0 )
        result.at<Vec3b>(Point(j,i)) = billinearInterpolation(image, inverseFirstAffine * xy  );
      else
        result.at<Vec3b>(Point(j,i)) = billinearInterpolation(image, inverseSecondAffine * xy  );

    }
  }
  imwrite("./ex4.jpg", result);
}
