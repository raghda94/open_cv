#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

void convert() {
  Mat image = imread( "./images/L1.jpg", 0);
  for(int i = 0 ; i < image.rows ; i++)
    for(int j = 0 ;  j < image.cols ; j++)
      if(image.at<uchar>(i,j) >= 127)
          image.at<uchar>(i,j) = 0;
      else
        image.at<uchar>(i,j) = 255;
  imwrite("./ex1.jpg", image);
}
