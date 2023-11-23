#! /bin/bash

#用./check_web.sh 或者sh check_web执行脚本报错：“let:not found”,
#这是因为在ubuntu的sh解释器是软链接指向bin/dash解释器的,/bin/sh -> dash
#dash是阉割版的bash,其功能远没有bash强大和丰富.并且dash不支持let和i++等功能.
#解决办法，用#! /bin/bash 或者 bash check_web.sh执行

Check_Url()
{
	timeout=5
	fails=0
	success=0
	website=$1

	#循环检测一些命令
	while true

	    do
		wget --timeout=${timeout} --tries=1 ${website} -q -O /dev/null

		if [ $? -ne 0 ]; then
			let fails=fails+1
		else
			let success=success+1
		fi
	
		#当成功次数大于等于1时，可以得出网站是正确运行的，-ge 是大于等于的意思
		if [ ${success} -ge 1 ]; then
			echo "恭喜你，网站：${website} 正常运行！"
			exit 0
		fi

		#当错误次数大于2时，就告警，比如发邮件，我这里用打印
		if [ ${fails} -ge 2 ]; then
			echo "网站：${website} 可能挂了！"
			exit 2
		fi

	    done

}

if [ $# -ne 1 ]; then
	echo "请输入要检测的网址！"
	exit 1
fi

Check_Url "$1" 





