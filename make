#!/bin/bash

ROOT=$(pwd)

function clean()
{
    rm -rf build
}

function build()
{
    clean

    source $ROOT/../zephyr-env.sh
    cmake -B build $1 .
}

function run()
{
    echo 'run now'
    cd build
    make run
}

function usage()
{
    USAGE=$(cat <<- EOF
	  usage: cmd options

	-b | build  [-DLIB=xxx]:
	  build fpc, link to xxx located at secure/lib.
	-r | run:
	  run fpc
	-c | clean:
	  clean fpc
	EOF
    )
    echo "$USAGE"
}

if [ $# == 0 ]; then
    usage
else
    while [ $# -gt 0 ]
    do
        case $1 in
        -b | build)
            shift
            if [ $# -gt 0 ]; then
                if [[ $1 == '-r' || $1 == 'run' ]]; then
                    build
                else
                    build $1
                    shift
                fi
            else
                build
            fi
            ;;
        -r | run)
            shift
            run
            ;;
        -c | clean)
            shift
            clean
            ;;
        esac
    done
fi
