clc
clear all
close all
I = imread( '/home/u25th_engineer/document/code/matlab/eso1242a_3.tif') ;
% subplot( 221) , imshow( I) ;
% I = double( I) /255;
% subplot( 222) , imhist( I) ;
% 调用灰度图像转换成二进制图像的程序
% I = graybw( 'logo. tif',0. 5) ;
% subplot( 223) , imshow( I) ;
a =I(1,1) % ( 为了查看起始游程)
% 调用把 0 游程和 1 游程分开存放的函数,如果起始位是 1 则 bqi代表 1 游程数,如果是 0, bqi 代表 0 游程数
% 这里没有浪费空间去存储二值图像起始游程,是因可以直接查看到二值图像的矩阵,它的第一个数就是第一个游程
[bqi, cou, bqi_num, cou_num]= countyoucheng( I) ;
qi_length = length( bqi) ;
ou_length = length( cou) ;
% 调用十进制转化成二进制的函数
data1 = int_bw( bqi, bqi_num) ;
data2 = int_bw( cou, cou_num) ;
% % 查看编码后数据量
% % [ m, n]= size( data1) ;
% % [ m1, n1]= size( data2) ;
% 调用 randlsbhide. m 文件完成随机选择 LSB 的信息隐秘
figure,[ ste_cover1, qilen_total] = randlsbhide( ' pout. tif', data1, ' qim-
age. tif',
823) ;
figure,[ ste _ cover2, oulen _ total] = randlsbhide ( ' cameraman. tif', da-ta2, 'oimage. tif',106) ;
% 调用提取图像函数 get_image. m 提取秘密图像
survive_image = get_image( 'qimage. tif', 'oimage. tif',5467,3472,497,496,11,7, 'survive. tif',823,106,0,107,122)
