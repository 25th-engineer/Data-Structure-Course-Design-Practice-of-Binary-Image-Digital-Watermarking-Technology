close all
clear
clc
%figure('Number','off');
f = imread('/home/u25th_engineer/桌面/lena256.bmp');
subplot(231);imshow(f);title('lena彩色原图');

%g = rgb2gray(f);

g1 = filter2( fspecial('sobel'), f );
g = mat2gray(g1)

subplot(234);imshow(g),title('lena灰度原图');
n = imnoise(g,'salt & pepper',0.01);
%n = imnoise(g,'gaussian',0,0.01);
%n = imnoise(g,'poisson');
subplot(232);imshow(n),title('噪声图像');
m1 = medfilt2(n,[5 5]);
subplot(235);imshow(m1),title('5*5中值滤波');
m2 = medfilt2(n,[5 1]);
subplot(233);imshow(m2);title('5*1中值滤波');
m3 = medfilt2(n,[1 5]);
subplot(236);imshow(m3);title('组合滤波器');
[imPSNR(n,g),imPSNR(m1,g),imPSNR(m3,g),imPSNR(g,g); imKBlur(n,g),imKBlur(m1,g),imKBlur(m3,g),imKBlur(g,g)]

function [ PSNR ] = imPSNR( J , I )
%imPSNR Summary of this function goes here
%   I is a image with high quality
%   J is a image with noise
%   the function will return the PSNR of the noise image
width = size(I,2);
heigh = size(I,1);
if( width ~= size(J,2) || heigh ~= size(J,1) )
    disp('Please check the input image have the same size');
    return
end
K = (I-J).*(I-J);
PSNR = sum(sum(K,1));
PSNR = PSNR / (width * heigh);
PSNR=10*log10(255*255/PSNR);
end
