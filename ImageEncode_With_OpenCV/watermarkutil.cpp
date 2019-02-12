
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include <QtCore>
#include <QMessageBox>

#include "watermarkutil.h"

using namespace cv;

// return edge from images
cv::Mat watermark::edgeExtract(const cv::Mat &src)
{
    Mat dst;
    Mat B1 = Mat::zeros(src.rows, src.cols, CV_8U);
    Mat t_mat = Mat::zeros(2, 3, CV_32F);

    t_mat.at<float>(0, 0) = 1;
    t_mat.at<float>(0, 2) = 1;
    t_mat.at<float>(1, 1) = 1;
    t_mat.at<float>(1, 2) = 0;
    warpAffine(src, dst, t_mat, src.size());
    Mat AL = dst - src;
    Mat BL = (AL + abs(AL))/2;

    t_mat.at<float>(0, 0) = 1;
    t_mat.at<float>(0, 2) = -1;
    t_mat.at<float>(1, 1) = 1;
    t_mat.at<float>(1, 2) = 0;
    warpAffine(src, dst, t_mat, src.size());
    Mat AR = dst - src;
    Mat BR = (AR + abs(AR))/2;

    t_mat.at<float>(0, 0) = 1;
    t_mat.at<float>(0, 2) = 0;
    t_mat.at<float>(1, 1) = 1;
    t_mat.at<float>(1, 2) = 1;
    warpAffine(src, dst, t_mat, src.size());
    Mat AT = dst - src;
    Mat BT = (AT + abs(AT))/2;

    t_mat.at<float>(0, 0) = 1;
    t_mat.at<float>(0, 2) = 0;
    t_mat.at<float>(1, 1) = 1;
    t_mat.at<float>(1, 2) = 1;
    warpAffine(src, dst, t_mat, src.size());
    Mat AB = dst - src;
    Mat BB = (AB + abs(AB))/2;

    Mat BLR = BL + BR;
    Mat BTB = BT + BB;
    Mat B = BLR + BTB;

    for (int i = 1; i< src.rows-1; i++)
    {
        for (int j = 1; j< src.cols-1; j++)
        {
            if((B.at<uchar>(i, j) == 2 && BLR.at<uchar>(i, j) != 2 && BTB.at<uchar>(i, j) != 2)
                    || (B.at<uchar>(i, j) == 1))
            {
                B1.at<uchar>(i, j) = 1;
            }
        }
    }

    Mat B11 = B1;
    Mat meanB1, meanSrc;
    blur(B1 * 9, meanB1, Size(3, 3));
    blur(src * 9, meanSrc, Size(3, 3));
    for (int i = 1; i< src.rows-1; i++)
    {
        for (int j = 1; j< src.cols-1; j++)
        {
            if(B1.at<uchar>(i, j) == 1 && meanB1.at<uchar>(i, j) == meanSrc.at<uchar>(i, j))
            {
                B11.at<uchar>(i, j) = 0;
            }
        }
    }

    return B11;
}

// encode byteArray with keyArray
byteArray watermark::encode(byteArray src, byteArray key)
{
    byteArray res;
    if(src.length() != key.length())
    {
        qDebug()<< "The length of keyArray and srcArray doesn't match! ";
        return byteArray();
    }

    for(int i = 0; i < src.length(); i++)
    {
        res.append(src[i] ^ key[i]);
    }

    return res;
}

// generate keyArray
byteArray watermark::generateKey(int length)
{
    byteArray res;
    for(int i = 0; i<length; i++)
    {
        if(double(qrand())/RAND_MAX > 0.5)
        {
            res.append(true);
        }
        else
        {
            res.append(false);
        }
    }

    return res;
}

// data hide
Mat watermark::watermarkImg(Mat src, Mat edge, byteArray code)
{
    int count = 0;
    for (int i = 0; i< src.rows; i++)
    {
        for (int j = 0; j< src.cols; j++)
        {
            if(edge.at<uchar>(i, j) == 1)
            {
                src.at<uchar>(i, j) = code[count++];
                if(count == code.length())
                {
                    return src;
                }
            }
        }
    }
    return src;
}

byteArray watermark::decodeImg(Mat src, Mat dst, int length)
{
    Mat edge = edgeExtract(src);
    byteArray res;
    //int count = 0;
    for (int i = 0; i< src.rows; i++)
    {
        for (int j = 0; j< src.cols; j++)
        {
            if(edge.at<uchar>(i, j) == 1)
            {
                res.append(dst.at<uchar>(i, j));
                if(length == res.length())
                {
                    return res;
                }
            }
        }
    }
    return res;
}

int watermark::sum(Mat src)
{
    int count = 0;
    for (int i = 0; i< src.rows; i++)
    {
        for (int j = 0; j< src.cols; j++)
        {
            count += src.at<uchar>(i, j);
        }
    }
    return count;
}

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

byteArray watermark::byte2Array(QString &number)
{
    byteArray res;
    for(auto byte : number)
    {
        if(byte == '1')
        {
            res.append(true);
        }
        else if(byte == '0')
        {
            res.append(false);
        }
        else
        {
            QMessageBox::warning(nullptr, "Error", "Error in byte2Array: Charater else than 0 and 1!\nThe application will be forced to abort.");
            throw EXIT_FAILURE;
        }
    }
    return res;
}

byteArray watermark::str2Array(QString &str)
{
    QString num;
    for(auto character : str)
    {
        int i = character.unicode();
        QString ele = QString::number(i, 2);
        for(int j = 0;j<8-ele.length();j++)
        {
            num += '0';
        }
        num += QString::number(i, 2);
    }
    qDebug()<<num;
    return byte2Array(num);
}

byteArray watermark::img2Array(QString &dir)
{
    Q_UNUSED(dir);
    QString str = "01010101010101010101010101010101";
    //return byte2Array(QString("01010101010101010101010101010101"));
    return byte2Array(str);
}

QString watermark::array2byte(byteArray &array)
{
    QString res;
    for(auto ele:array)
    {
        if(ele)
        {
        res.append('1');
        }
        else
        {
        res.append('0');
        }
    }
    return res;
}

QString watermark::array2str(byteArray &array)
{
    QString res;
    for(int i = 0 ; i<array.length(); i+=8)
    {
        int num = array[i + 7] + array[i + 6]*2 + array[i + 5]*4 + array[i + 4]*8 +
                array[i + 3]*16 + array[i + 2]*32 + array[i + 1]*64 + array[i + 0]*128;
        res.append(char(num));
    }
    return res;
}
