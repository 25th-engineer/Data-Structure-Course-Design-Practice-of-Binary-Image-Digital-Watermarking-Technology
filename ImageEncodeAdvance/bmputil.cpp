#include "bmputil.h"
//#include <windows.h>

/*
uchar* readBmp_1(const char *bmpName, int& bmpWidth, int& bmpHeight) //failed
{
    FILE *fp = fopen(bmpName, "rb");
    if(fp == Q_NULLPTR)
    {
        QMessageBox::warning(Q_NULLPTR, "Error", "Error in Open File!");
        return Q_NULLPTR;
    }

    // skip the fileheader
    fseek(fp, sizeof(BITMAPFILEHEADER), 0);

    // read the infoheader
    BITMAPINFOHEADER* head = new BITMAPINFOHEADER;
    fread(head, sizeof(BITMAPINFOHEADER), 1, fp);
    bmpWidth = head->biWidth;
    bmpHeight = head->biHeight;
    int bitCount = head->biBitCount;
    qDebug() << "bitCount = " << bitCount << endl;
    if (bitCount == 8)
    {
        RGBQUAD* pColorTable = new RGBQUAD[256];
        fread(pColorTable, sizeof(RGBQUAD), 256, fp);

        uchar* pBmpBuf = new uchar[ bmpWidth * bmpHeight ];
        fread(pBmpBuf, sizeof(uchar), bmpWidth * bmpHeight, fp);
        fclose(fp);

        uchar* buffer = new uchar[bmpWidth * bmpHeight];
        for(int i = 0; i < bmpHeight; i++)
        {
            for(int j = 0; j<bmpWidth; j++)
            {
                if(pBmpBuf[(bmpHeight- i - 1)*bmpWidth + j] != 255 && pBmpBuf[(bmpHeight- i - 1)*bmpWidth + j] != 0)
                {
                    QMessageBox::warning(Q_NULLPTR, "Error", "This is not a binary image!");
                    return Q_NULLPTR;
                }
                buffer[i*bmpWidth + j] = pBmpBuf[(bmpHeight- i - 1)*bmpWidth + j];
            }
        }
        return buffer;
    }
    else
    {
        QMessageBox::warning(Q_NULLPTR, "Error", "Our program can only deal with 8-bit image!");
        return Q_NULLPTR;
    }
}
*/

uchar* watermark::readBmp(const char *bmpName, int& bmpWidth, int& bmpHeight)
{
    FILE *fp = fopen(bmpName, "rb");
    if(fp == Q_NULLPTR)
    {
        QMessageBox::warning(Q_NULLPTR, "Error", "Error in Open File!");
        return Q_NULLPTR;
    }

    // skip the fileheader
    fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_CUR);

    // read the infoheader
    //BITMAPINFOHEADER* head = new BITMAPINFOHEADER;
    watermark WT;
    //infohead = &(WT.BMIH);
    BITMAPINFODEADER infohead = WT.BMIH;
    fread(&infohead,sizeof(BITMAPINFOHEADER),1,fp);
    //fread(infoHead, sizeof(BITMAPINFOHEADER), 1, fp);
    bmpWidth = infohead.biWidth;
    bmpHeight = infohead.biHeight;
    biBitCount = infohead.biBitCount;
    lineByte = (bmpWidth*biBitCount/8+3)/4*4;
    //qDebug() << infohead.biSize << endl;
    //qDebug() << infohead.biWidth << endl;
    //qDebug() << infohead.biHeight << endl;
    //qDebug() << infohead.biBitCount << endl;
    if (biBitCount == 8)
    {
        RGBQUAD* pColorTable = new RGBQUAD[256];
        fread(pColorTable, sizeof(RGBQUAD), 256, fp);

        uchar* pBmpBuf = new uchar[ bmpWidth * bmpHeight ];
        fread(pBmpBuf, sizeof(uchar), bmpWidth * bmpHeight, fp);
        fclose(fp);

        uchar* buffer = new uchar[bmpWidth * bmpHeight];
        for(int i = 0; i < bmpHeight; i++)
        {
            for(int j = 0; j<bmpWidth; j++)
            {
                if(pBmpBuf[(bmpHeight- i - 1)*bmpWidth + j] != 255 && pBmpBuf[(bmpHeight- i - 1)*bmpWidth + j] != 0)
                {
                    QMessageBox::warning(Q_NULLPTR, "Error", "This is not a binary image!");
                    return Q_NULLPTR;
                }
                buffer[i*bmpWidth + j] = pBmpBuf[(bmpHeight- i - 1)*bmpWidth + j];
            }
        }
        return buffer;
    }
    else
    {
        QMessageBox::warning(Q_NULLPTR, "Error", "Our program can only deal with 8-bit image!");
        return Q_NULLPTR;
    }
}

bool watermark::savebmp(const char* filename, uchar* buffer, const u_int32_t height, const u_int32_t width)
{
    RGBQUAD *pColorTable = new RGBQUAD;
    if(buffer == Q_NULLPTR)
    {
        QMessageBox::warning(Q_NULLPTR, "Error", "The Buffer is nullptr!");
        return false;
    }
    uchar* data = new uchar[height*width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            data[i*width + j] = buffer[(height- i - 1)*width + j];
        }
    }

    int colorTableSize = 1024;
    BITMAPFILEHEADER fileHeader;
    fileHeader.bfType = 0x4D42;
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTableSize + height*width;
    fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTableSize;

    BITMAPINFOHEADER bitmapHeader = { 0 };
    bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
    //qDebug() << "In bool watermark::savebmp(const char* filename, uchar* buffer, const u_int32_t height, const u_int32_t width), height = " << height << endl;
    //qDebug() << "In bool watermark::savebmp(const char* filename, uchar* buffer, const u_int32_t height, const u_int32_t width), width = " << width << endl;
    //qDebug() << sizeof(BITMAPINFOHEADER) << endl;
    bitmapHeader.biHeight = height;
    bitmapHeader.biWidth = width;
    bitmapHeader.biPlanes = 1;
    bitmapHeader.biBitCount = 8;
    bitmapHeader.biSizeImage = height*width;
    bitmapHeader.biCompression = 0;

    FILE *fp = fopen(filename, "wb");
    //qDebug() << "OK! line 154 " << endl;
    if(fp == Q_NULLPTR)
    {
        QMessageBox::warning(Q_NULLPTR, "Error", "Error in Save File!");
        //qDebug() << "OK! line 156 " << endl;
        return false;
    }
    else
    {
        fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
        //qDebug() << "OK! line 162 " << endl;
        fwrite(&bitmapHeader, sizeof(BITMAPINFOHEADER), 1, fp);
        //qDebug() << "OK! line 164 " << endl;
        //qDebug() << "pColorTable address = " << pColorTable << endl;
        fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
        delete pColorTable;
        //qDebug() << "OK! line 168 " << endl;
        fwrite(data, height*width, 1, fp);
        delete []data;
        //qDebug() << "OK! line 171 " << endl;
        fclose(fp);
        //qDebug() << "OK! line 173 " << endl;
        return true;
    }

    /*
    FILE *fp;
    if( (fp = fopen(filename,"wb") )== NULL)   //以二进制写入方式打开
    {
        //cout<<"打开失败!"<<endl;
        QMessageBox::warning(Q_NULLPTR, "Error", "The Buffer is nullptr!");
        //return -1;
        return false;
    }
    //设置BITMAPFILEHEADER参数
    BITMAPFILEHEADER fileHead;
    fileHead.bfType = 0x4D42;
    fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + lineByte * biHeight;
    fileHead.bfReserved1 = 0;
    fileHead.bfReserved2 = 0;
    fileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
    //设置BITMAPINFOHEADER参数
    BITMAPINFOHEADER infoHead;
    infoHead.biSize = 40;
    infoHead.biWidth = biWidth;
    infoHead.biHeight = biHeight;
    infoHead.biPlanes = 1;
    infoHead.biBitCount = biBitCount;
    infoHead.biCompression = 0;
    infoHead.biSizeImage = lineByte * biHeight;
    infoHead.biXPelsPerMeter = 0;
    infoHead.biYPelsPerMeter = 0;
    infoHead.biClrUsed = 0;
    infoHead.biClrImportant = 0;
    //写入
    fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);


    fwrite(pBmpBuf,sizeof(char),height*width,fp);
    fclose(fp);    //关闭文件
    //return 0;
    return true;
    */
}


// generate keyArray
byteArray watermark::generateKey(const int length)
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

uchar* watermark::translation(uchar* buffer, const int width, const int height, int x_off, int y_off)
{
    uchar* res = new uchar[width*height];
    for(int i = 0; i<height; i++)
    {
        for(int j = 0;j<width; j++)
        {
            if(i-x_off < 0 || j-y_off < 0)
            {
                res[i*width + j] = 0;
            }
            else
            {
                res[i*width + j] = buffer[(i - x_off)*width + (j - y_off)];
            }
        }
    }

    return res;
}

uchar* watermark::substract(uchar* buffer1, uchar* buffer2, const int size)
{
    uchar* res = new uchar[size];
    for(int i = 0; i<size; i++)
    {
        res[i] = buffer1[i] > buffer2[i] ? buffer1[i] - buffer2[i] : 0;
    }
    return res;
}

uchar* watermark::edgeExtract(uchar* buffer, const int width, const int height)
{
    uchar* BL = substract(translation(buffer, width, height, 1, 0), buffer, width*height);
    uchar* BR = substract(translation(buffer, width, height, -1, 0), buffer, width*height);
    uchar* BT = substract(translation(buffer, width, height, 0, 1), buffer, width*height);
    uchar* BB = substract(translation(buffer, width, height, 0, -1), buffer, width*height);

    uchar* B1 = new uchar[height*width];
    for(int i = 0; i<height*width; i++)
    {
        BL[i] = BL[i]/255;
        BR[i] = BR[i]/255;
        BT[i] = BT[i]/255;
        BB[i] = BB[i]/255;

        int lr = BL[i] + BR[i];
        int tb = BT[i] + BB[i];
        int b = lr + tb;

        B1[i] = 0;
        if((b == 1) ||(b == 2 && lr != 2 && tb != 2))
        {
            B1[i] = 1;
        }
    }

    uchar* res = new uchar[height*width];
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            res[i*width + j] = B1[i*width + j] * 255;
            if(B1[i*width + j])
            {
                int sum1 = 0, sum2 = 0;
                for(int a = -1; a<2; a++)
                {
                    if(a + i <0 || a+ i >= height)
                    {
                        continue;
                    }
                    for(int b = -1; b<2; b++)
                    {
                        if(b +j <0 || b+j>=width)
                        {
                            continue;
                        }
                        sum1 += buffer[(a + i) *width + (b + j)]/255;
                        sum2 += B1[(a + i) *width + (b + j)];
                    }
                }
                if(sum1 == sum2)
                {
                    res[i*width + j] = 0;
                }
            }
        }
    }

    return res;
}

uchar* watermark::watermarkImg(uchar* buffer, uchar* edge, const int size, byteArray code)
{
    uchar* res = new uchar[size];
    for(int i = 0; i<size; i++)
    {
        res[i] = buffer[i];
    }
    int count = 0;
    for(int i = 0; i<size; i++)
    {
        if(edge[i]==255)
        {
            res[i] = 255*code[count++];
            if(count == code.length())
            {
                return res;
            }
        }
    }
    QMessageBox::warning(Q_NULLPTR, "Error", "The image is too small to contain such a code!");
    return Q_NULLPTR;
}

byteArray watermark::decodeImg(uchar* buffer, uchar* dst, const int width, const int height, const int length)
{
    uchar* edge = edgeExtract(buffer, width, height);
    byteArray res;
    for(int i = 0; i<width*height; i++)
    {
        if(edge[i] == 255)
        {
            res.append(dst[i]);
            if(length == res.length())
            {
                return res;
            }
        }
    }
    QMessageBox::warning(Q_NULLPTR, "Error", "The image is too small to contain such a code!");
    return byteArray();
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
            QMessageBox::warning(nullptr, "Error", "Error in byte2Array: Charater else than 0 and 1!");
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

/*
BITMAPINFODEADER &watermark::operator=(BITMAPINFODEADER& BMIH)
{
    if( &((*this).BMIH) == &BMIH )
        return (*this).BMIH;
    BMIH.biSize = (*this).BMIH.biSize;
    BMIH.biWidth = (*this).BMIH.biWidth;
    BMIH.biHeight = (*this).BMIH.biHeight;
    BMIH.biPlanes = (*this).BMIH.biPlanes;
    BMIH.biClrUsed = (*this).BMIH.biClrUsed;
    BMIH.biSizeImage = (*this).BMIH.biSizeImage;
    BMIH.biCompression = (*this).BMIH.biCompression;
    BMIH.biClrImportant = (*this).BMIH.biClrImportant;
    BMIH.biXPelsPerMeter = (*this).BMIH.biXPelsPerMeter;
    BMIH.biYPelsPerMeter = (*this).BMIH.biYPelsPerMeter;
    qDebug() << "214235423" << endl;
    //return (*this).BMIH;
    return BMIH;
}
*/
