CPPFILES=$(wildcard *.cpp)
OBJECTS=$(basename $(CPPFILES))

all: $(OBJECTS)

print:
	-mkdir print

#print/%: % print format.sh
#	./format.sh $< > $@

print/%: % print format.pl
	perl ./format.pl $< > $@

code.ps: $(addprefix print/, $(CPPFILES))
	a2ps --pretty-print=c -2 --file-align=fill --tabsize=2 --pro=color --margin=0 --medium=letterdj --left-footer="" --right-footer="" --footer="" --header="%s." --left-title="" --right-title="" -o $@ $^
	#a2ps --columns=2 --pro=color --left-footer="" --right-footer="" --footer="" --header="" --right-title="" -1 --tabsize=4 --portrait --margin=0 -M letterdj -o $@ $^

code2.ps: code.ps
	psnup -nup 2 -pletter -m2 -b-16 $^ $@

library.pdf: code.ps
	perl ./header.pl $^ $^
	ps2pdf $^ $@

clean:
	rm -rf $(OBJECTS)
	rm -rf print
	rm -rf *.ps library.pdf

.PHONY: clean all
