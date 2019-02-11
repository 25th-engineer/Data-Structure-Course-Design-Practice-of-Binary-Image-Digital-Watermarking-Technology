#ifndef WATERMARKUTIL_H
#define WATERMARKUTIL_H

#include "opencv2/opencv.hpp"
//#include "/usr/share/opencv-4.0.1/include/opencv2/opencv.hpp"
#include "opencv2/core.hpp"
//#include "/usr/share/opencv-4.0.1/modules/core/include/opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "/usr/share/opencv-4.0.1/modules/imgproc/include/opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include "/usr/share/opencv-4.0.1/modules/highgui/include/opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
//#include "/usr/share/opencv-4.0.1/modules/imgcodecs/include/opencv2/imgcodecs/imgcodecs.hpp"
#include <QtCore>

using namespace cv;
using byteArray = QVector<bool>;

Mat edgeExtract(const Mat& src);
int sum(Mat src);
byteArray encode(byteArray src, byteArray key);
byteArray generateKey(int length);
Mat watermarkImg(Mat src, Mat edge, byteArray code);
byteArray decodeImg(Mat src, Mat dst, int length);
QVector<uchar> mat2Array(Mat& src);
byteArray byte2Array(QString& number);
byteArray str2Array(QString& str);
byteArray img2Array(QString& dir);
QString array2byte(byteArray& array);
QString array2str(byteArray& array);

#endif // WATERMARKUTIL_H
