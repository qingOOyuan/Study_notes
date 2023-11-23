#! /bin/sh

#shell的if格式为 if [ condition ] ; then statement 这里判断的结果为true和false。
#而true和false是在这个地方是不能直接用0或1代替的，因为对任意数字，shell返回的都是#true。
#[ condition ]部分如果是一个函数或者指令，而函数有return语句(指令有执行状态$?)，此时返回值0会被当做#true，而其他数字则会被当做false。


is_directory()

{

      DIR_NAME=$1

       if [ ! -d $DIR_NAME ]; then

		echo "${DIR_NAME} return 1"
                return 1

        else

		echo "${DIR_NAME} return 0"
                return 0

         fi

}

for DIR in "$@"; do

      if is_directory "$DIR"; then
	
	     echo "$DIR exist."

      else

             echo "$DIR doesn't exist. Creating it now..."

             mkdir $DIR

             if [ $? -ne 0 ]; then

             	echo "Cannot create directory $DIR"

                exit 1

             fi

      fi

done

