#!/bin/sh

print_usage()
{
	printf "请输入一个正确的整数！\n"
	exit 1
}

read -p "请输入第一个整数: " first_number
#sed的作用就是把可能错误的字符串如“qwe123”进行替换，把所有的数字都替换成空，那么剩下的都是非数字的部分了
#注意“`之间不能有空格，因为空格也是字符，会认为一直条件非空成立
if [ -n "` echo $first_number | sed 's/[0-9]//g' `"  ]; then
	print_usage

fi


read -p "请输入运算符: " operator

#运算符我们只支持+ - * /
if [ "${operator}" != "+" ] && [ "${operator}" != "-" ] && [ "${operator}" != "*" ] && [ "${operator}" != "/" ]; then
	
	echo "只支持+ - * /"
	exit 2
fi  


read -p "请输入第二个整数: " second_number
#sed的作用就是把可能错误的字符串如“qwe123”进行替换，把所有的数字都替换成空，那么剩下的都是非数字的部分了
if [ -n "` echo $second_number | sed 's/[0-9]//g' `"  ]; then

	print_usage

fi


#进行最后的运算
echo "${first_number} ${operator} ${second_number} = $((${first_number}${operator}${second_number}))"



	
	
