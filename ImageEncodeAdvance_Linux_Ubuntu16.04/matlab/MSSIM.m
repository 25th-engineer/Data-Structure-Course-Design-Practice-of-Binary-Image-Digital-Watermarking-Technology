I1=imread('/home/u25th_engineer/lena256.bmp');
I2=imread('/home/u25th_engineer/encode.bmp');
I1_bw=I1;
I2_bw=I2;
[h,w]=size(I1_bw);%%获取图的宽高h/w
sum=0;
for i=1:h
for j=1:w
if I1_bw(i,j)==I2_bw(i,j)%%逐点比较相似
sum=sum+1;
end
end
end
pio=double(sum)/(h*w);
display(pio);