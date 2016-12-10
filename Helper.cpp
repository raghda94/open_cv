#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;


Vec3b billinearInterpolation(Mat image, Mat m) {

  float x = m.at<float>(0, 0);
  float y = m.at<float>(1, 0);

  Vec3b I1 = image.at<Vec3b>(Point(floor(x), floor(y)));
  Vec3b I2 = image.at<Vec3b>(Point(floor(x), ceil(y)));
  Vec3b I3 = image.at<Vec3b>(Point(ceil(x), floor(y)));
  Vec3b I4 = image.at<Vec3b>(Point(ceil(x), (ceil(y))));

  Vec3b result = I4;

  for( int i = 0 ; i < 3 ; i++) {
    int p1 = I1[i] * (ceil(x) - x) + I3[i] * (x - floor(x));
    int p2 = I2[i] * (ceil(x) - x) + I4[i] * (x - floor(x));
    result[i] = p1 * (ceil(y) - y) + p2 * (y - floor(y));
  }

  return result;
}
