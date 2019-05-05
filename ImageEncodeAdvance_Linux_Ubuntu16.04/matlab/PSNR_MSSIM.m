clc;
close all;

path1 = '/home/u25th_engineer/lena256.bmp';
path2 = '/home/u25th_engineer/lena256_encode.bmp';
path3 = '/home/u25th_engineer/lena256_encode_noise.bmp';


X = imread(path1);

Y = imread(path2);

%KKK = filter2( fspecial('sobel'), Y );
%X1 = mat2gray(Y)
%Z=X1;
Z = imnoise(Y, 'salt & pepper');%添加椒盐噪声，也可以改成其他噪声
%Z = imnoise(Y,'gaussian',0.1,0.004);
imwrite( Z, path3 );
%A = fspecial('average',3); %生成系统预定义的3X3滤波器  



figure;
subplot(1, 3, 1); imshow(X); title('a.Lena256原图像');
subplot(1, 3, 2); imshow(Y); title('b.加水印图像');
subplot(1, 3, 3); imshow(Z); title('c.水印图像加噪声');


X = double(X); 
Y = double(Y); 

D = Y - X;
MSE = sum(D(:).*D(:)) / numel(Y);%均方根误差MSE


d = 0;
e = 0;
file_name = path1;       
cover_object = double(imread(file_name));
Mc = size(cover_object, 1);     %原图像行数
Nc = size(cover_object, 2);     %原图像列数
file_name = path2;
watermarked_image = double(imread(file_name));
%计算信噪比
for i = 1 : Mc
    for j = 1 : Nc
        a(i, j) = cover_object(i, j) ^ 2;
        b(i, j) = cover_object(i, j) - watermarked_image(i, j);
        d = d + a(i, j);
        e = e + b(i, j) ^ 2;
    end
end
PSNR = 10 * log10(d / e);

MAE = mean(mean(abs(D)));%平均绝对误差

w = fspecial('gaussian', 11, 1.5); %window 加窗  
K(1) = 0.01; 
K(2) = 0.03; 
L = 255; 
Y = double(Y); 
X = double(X); 
C1 = (K(1)*L) ^ 2;
C2 = (K(2)*L) ^ 2; 
w = w/sum(sum(w)); 
ua = filter2(w, Y, 'valid');%对窗口内并没有进行平均处理，而是与高斯卷积，  
ub = filter2(w, X, 'valid'); % 类似加权平均  
ua_sq = ua.*ua;
ub_sq = ub.*ub;
ua_ub = ua.*ub; 
siga_sq = filter2(w, Y.*Y, 'valid') - ua_sq; 
sigb_sq = filter2(w, X.*X, 'valid') - ub_sq; 
sigab = filter2(w, Y.*X, 'valid') - ua_ub;
ssim_map = ((2*ua_ub + C1).*(2*sigab + C2))./((ua_sq + ub_sq + C1).*(siga_sq + sigb_sq + C2)); 
MSSIM = mean2(ssim_map); 

display(MSE);%均方根误差MSE
display(PSNR);%峰值信噪比
display(MAE);%平均绝对误差
display(MSSIM);%结构相似性SSIM

%display(d);
%display(e);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
X = double(X); 
Y = double(Z); 

D = Y - X;
MSE1 = sum(D(:).*D(:)) / numel(Y);%均方根误差MSE


d = 0;
e = 0;
file_name = path1;       
cover_object = double(imread(file_name));
Mc = size(cover_object, 1);     %原图像行数
Nc = size(cover_object, 2);     %原图像列数
file_name = path3;
watermarked_image = double(imread(file_name));
%计算信噪比
for i = 1 : Mc
    for j = 1 : Nc
        a(i, j) = cover_object(i, j) ^ 2;
        b(i, j) = cover_object(i, j) - watermarked_image(i, j);
        d = d + a(i, j);
        e = e + b(i, j) ^ 2;
    end
end
PSNR1 = 10 * log10(d / e);

MAE1 = mean(mean(abs(D)));%平均绝对误差

w = fspecial('gaussian', 11, 1.5); %window 加窗  
K(1) = 0.01; 
K(2) = 0.03; 
L = 255; 
Y = double(Y); 
X = double(X); 
C1 = (K(1)*L) ^ 2;
C2 = (K(2)*L) ^ 2; 
w = w/sum(sum(w)); 
ua = filter2(w, Y, 'valid');%对窗口内并没有进行平均处理，而是与高斯卷积，  
ub = filter2(w, X, 'valid'); % 类似加权平均  
ua_sq = ua.*ua;
ub_sq = ub.*ub;
ua_ub = ua.*ub; 
siga_sq = filter2(w, Y.*Y, 'valid') - ua_sq; 
sigb_sq = filter2(w, X.*X, 'valid') - ub_sq; 
sigab = filter2(w, Y.*X, 'valid') - ua_ub;
ssim_map = ((2*ua_ub + C1).*(2*sigab + C2))./((ua_sq + ub_sq + C1).*(siga_sq + sigb_sq + C2)); 
MSSIM1 = mean2(ssim_map); 

display(MSE1);%均方根误差MSE
display(PSNR1);%峰值信噪比
display(MAE1);%平均绝对误差
display(MSSIM1);%结构相似性SSIM

%display(d);
%display(e);