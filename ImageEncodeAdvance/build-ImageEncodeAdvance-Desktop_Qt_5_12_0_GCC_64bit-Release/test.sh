#########################################################################
# File Name: tesdt.sh
# Author: Xef Utah刁肥宅
# mail: u25th_engineer@163.com
# Created Time: 2019年02月10日 星期日 16时31分39秒
#########################################################################
#!/bin/bash
appname=`basename $0 | sed s,\.sh$,,`
 
dirname=`dirname $0`
tmp="${dirname#?}"
 
if [ "${dirname%$tmp}" != "/" ]; then
	dirname=$PWD/$dirname
fi
LD_LIBRARY_PATH=$dirname
export LD_LIBRARY_PATH
$dirname/$appname "$@"""""""]""
