#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include <QtCore>
#include <QMessageBox>

#include "watermarkutil.h"

using namespace cv;

QVector<uchar> watermark::mat2Array(Mat& src)
{
    QVector<uchar> res;
    for (int i = 0; i< src.rows; i++)
    {
        for (int j = 0; j< src.cols; j++)
        {
            res.append(src.at<uchar>(i, j) * 255);
        }
    }
    return res;
}
