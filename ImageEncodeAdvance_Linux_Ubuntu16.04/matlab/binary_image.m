clc
A=imread('/home/u25th_engineer/document/code/matlab/gratisography-staircase-break.jpg');   %读取到一张图片   
thresh = graythresh(A);     %自动确定二值化阈值
I2 = im2bw(A,thresh);       %对图像二值化

imwrite(I2, '/home/u25th_engineer/document/code/matlab/gratisography-staircase-break.bmp');

figure(1)
imshow(A)     %显示二值化之前的图片
figure(2)
imshow(I2)    %显示二值化之后的图片