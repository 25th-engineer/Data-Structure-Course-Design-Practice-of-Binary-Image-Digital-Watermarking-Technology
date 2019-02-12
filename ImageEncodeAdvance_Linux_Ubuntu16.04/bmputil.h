#ifndef BMPUTIL_H
#define BMPUTIL_H

#include "addditional_utility.h"

class watermark
{
public:
    QString array2byte(byteArray &array);
    QString array2str(byteArray &array);
    byteArray byte2Array(QString &number);
    byteArray decodeImg(uchar* buffer, uchar* dst, const int width, const int height, const int length);
    uchar* edgeExtract(uchar* buffer, const int width, const int height);
    byteArray encode(byteArray src, byteArray key);
    byteArray generateKey(const int length);
    byteArray img2Array(QString &dir);
    uchar* readBmp(const char *bmpName, int& bmpWidth, int& bmpHeight);
    byteArray str2Array(QString &str);
    uchar* substract(uchar* buffer1, uchar* buffer2, const int size);
    uchar* translation(uchar* buffer, const int width, const int height, int x_off, int y_off);
    uchar* watermarkImg(uchar* buffer, uchar* edge, const int size, byteArray code);
    bool savebmp(const char* filename, uchar* buffer, const u_int32_t height, const u_int32_t width);
private:
    BITMAPINFODEADER BMIH;
    BITMAPFILEHEADER BMFH;
    int biWidth;
    int biHeight;
    int biBitCount;
    int lineByte;
    RGBQUAD* pColorTable;
protected:


};

#endif // BMPUTIL_H
