clear all;
d=0;
e=0;
file_name='/home/u25th_engineer/brain.bmp';       %��ȡԭͼ��
cover_object=double(imread(file_name));
Mc=size(cover_object,1);     %ԭͼ������
Nc=size(cover_object,2);     %ԭͼ������
file_name='/home/u25th_engineer/brain_encode.bmp';
watermarked_image=double(imread(file_name));
%���������
for i=1:Mc
    for j=1:Nc
        a(i,j)=cover_object(i,j)^2;
        b(i,j)=cover_object(i,j)-watermarked_image(i,j);
        d=d+a(i,j);
        e=e+b(i,j)^2;
    end
end
psrn=10*log10(d/e);
display(psrn);