#/bin/sh
if expr "$1" ":" ".*\.jpg" &> /dev/null; then
	echo "这是jpg的文件"
else
	echo "这不是jpg文件"
fi
