#ifndef WATERMARKUTIL_H
#define WATERMARKUTIL_H

#include "additional_utility.h"

class watermark
{
public:
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
private:

protected:

};
#endif // WATERMARKUTIL_H
