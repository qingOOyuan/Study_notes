#! /bin/bash

# is the directory exist

path=/home/work/shell_study/install_test

[ ! -d "${path}" ] && mkdir "${path}" -p


cat <<END

    1.[install QQ]
    2.[install WeChat]
    3.[exit!]
    please input the num you want:

END

read num

expr "${num}" + 1 &> /dev/null

[ $? -ne 0 ] && {
    echo "The num you input must be {1|2|3}"
    exit 1
}

[[ ! "${num}" =~ [1-3] ]] && {
    
    echo "The num you input must be {1|2|3}"
    echo "Big fool, follow the instructions!!!"

}


[ "${num}" -eq "1" ] && {

    echo "Starting installing QQ...waiting..."
    sleep 1

    [ -x "${path}/QQ.sh" ] || {
        echo "The file dose not exist or cat't be exec."
	exit 1
    }
    
    ${path}/QQ.sh

    exit $?

}


[ "${num}" -eq "2" ] && {

    echo "Starting installing WeChat...waiting..."
    sleep 1

    [ -x "${path}/WeChat.sh" ] || {
        echo "The file dose not exist or cat't be exec."
        exit 1
    }

    ${path}/WeChat.sh

    exit $?

}


[ "${num}" -eq "3" ] && {

    echo "Bye Bye..."
    exit 3

}

