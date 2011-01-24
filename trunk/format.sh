#!/bin/sh

# remove trailing whitespace
# remove special comments and blocks. That is, removes everything between
# /*$ and $*/ including something of the form  /*$*/ ... /*$*/
# collapse >1 blank lines to one blank line
sed -e 's/\s\+$\| \+\ze\t//g' $1 \
	| sed -n '1h;1!H;${;g;s/\/\*\$[^$]*\n*\(^[^$]*\n\)*\$\*\///g;p;}' \
	| sed -n '1h;1!H;${;g;s/\n\n\n*/\n\n/g;p;}'


