#!/bin/sh

mkdir print > /dev/null 2>&1
rm print/* > /dev/null 2>&1

for x in `ls *.cpp`
do 
rm $x.temp > /dev/null 2>&1 
# remove trailing whitespace
# remove special comments and blocks. That is, removes everything between
# /*$ and $*/ including something of the form  /*$*/ ... /*$*/
# collapse >1 blank lines to one blank line
sed -e 's/\s\+$\| \+\ze\t//g' $x \
	| sed -n '1h;1!H;${;g;s/\/\*\$[^$]*\n*\(^[^$]*\n\)*\$\*\///g;p;}' \
	| sed -n '1h;1!H;${;g;s/\n\n\n*/\n\n/g;p;}' > print/$x.temp
cp print/$x.temp print/$x
rm print/$x.temp
done

cd print

a2ps --pro=color --left-footer="" --right-footer="" --footer="" --header="" --right-title="" -1 --tabsize=4 --portrait --margin=0 -M letterdj -o foo.ps *.cpp
psnup -nup 2 -pletter -m2 -b-16 foo.ps foo2.ps
ps2pdf foo2.ps ../library.pdf

cd ../
rm -r print


