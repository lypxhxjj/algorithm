# 如何不使用awk，就将一行数据保存到多个变量。(``)机制。注意shell中的数组都是从1开始的
# 用于命令批量生成。将命令放在脚本中，通过命令行方式调用即可。
cat /tmp/222 | while read line; do arr=(`echo $line`); echo $arr[1]; sh /tmp/111 $arr[1] $arr[2]; done