#!/bin/bash
win_tm_args="@*"
echo $win_tm_args
(echo $win_tm_args|sed -n 's/\/cygdrive\/(.)\/(.*)/\1:\/\2/p')
echo $win_tm_args
C:/ruby/bin/ruby.exe $win_tm_args