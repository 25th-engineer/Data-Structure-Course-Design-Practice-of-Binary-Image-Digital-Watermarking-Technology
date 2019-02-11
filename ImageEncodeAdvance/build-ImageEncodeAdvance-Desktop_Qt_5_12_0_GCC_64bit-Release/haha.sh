#########################################################################
# File Name: haha.sh
# Author: Xef Utah刁肥宅
# mail: u25th_engineer@163.com
# Created Time: 2019年02月10日 星期日 16时23分11秒
#########################################################################
#!/bin/bash

exe="test" #发布的程序名称
des="/home/u25th_engineer/document/code/Qt/ImageEncodeAdvance/build-ImageEncodeAdvance-Desktop_Qt_5_12_0_GCC_64bit-Release/" #你的路径

deplist=$(ldd $exe | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')
cp $deplist $des
