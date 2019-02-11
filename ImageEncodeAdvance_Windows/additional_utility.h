#ifndef ADDITIONAL_UTILITY_H
#define ADDITIONAL_UTILITY_H

#include <windows.h>
#include <iostream>
#include <fstream>
#include <QtCore>
#include <QMessageBox>

using byteArray = QVector<bool>;

typedef int u_int16_t;
typedef long u_int32_t;

/*
typedef struct BITMAPFILEHEADER
{
    u_int16_t bfType;
    u_int32_t bfSize;
    u_int16_t bfReserved1;
    u_int16_t bfReserved2;
    u_int32_t bfOffBits;
}BITMAPFILEHEADER;
*/

/*
typedef struct BITMAPINFOHEADER
{
    u_int32_t biSize;
    u_int32_t biWidth;
    u_int32_t biHeight;
    u_int16_t biPlanes;
    u_int16_t biBitCount;
    u_int32_t biCompression;
    u_int32_t biSizeImage;
    u_int32_t biXPelsPerMeter;
    u_int32_t biYPelsPerMeter;
    u_int32_t biClrUsed;
    u_int32_t biClrImportant;
    struct BITMAPINFOHEADER &operator=( struct BITMAPINFOHEADER &BMIH )
    {
        biSize = BMIH.biSize;
        biWidth = BMIH.biWidth;
        biHeight = BMIH.biHeight;
        biPlanes = BMIH.biPlanes;
        biClrUsed = BMIH.biClrUsed;
        biSizeImage = BMIH.biSizeImage;
        biCompression = BMIH.biCompression;
        biClrImportant = BMIH.biClrImportant;
        biXPelsPerMeter = BMIH.biXPelsPerMeter;
        biYPelsPerMeter = BMIH.biYPelsPerMeter;
        //qDebug() << "214235423" << endl;
        return *this;
    }

}BITMAPINFODEADER;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

typedef struct tagRGBQUAD
{
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
}RGBQUAD;


typedef struct tagIMAGEDATA
{
    BYTE blue;
    //BYTE green;//cancel the annotation by DFZ
    //BYTE red;//cancel the annotation by DFZ
}IMAGEDATA;
*/

#endif // ADDITIONAL_UTILITY_H
