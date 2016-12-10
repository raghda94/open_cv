#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "./Helper.cpp"
#include "./Binary.cpp"
#include "./Blend.cpp"
#include "./Brightness.cpp"
#include "./AffineTransformation.cpp"
#include "./HomographyTransformation.cpp"

#include <iostream>
#include <string>
#include <math.h>
using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
    convert();
    blend();
    brightness();
    affineTransform();
    homographyTransformation();

    waitKey();
    return 0;
}
