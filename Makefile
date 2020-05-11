# Project: ICP 2020
# File: Makefile
# Title: Transport Map
# Authors: Vojtěch Jahoda (xjahod06)
#          Silvie Němcová (xnemco06)

make: qMakefile
	make -f qMakefile --directory=build/
	mv build/ICP_2020_proj ./

qMakefile: clean_build
	qmake -o build/qMakefile src/ICP_2020_proj.pro

doxygen: clean_doc
	doxygen doxyfile

clean: clean_build clean_doc
	rm -f *.zip
	
clean_build:
	rm -f -r build/
	mkdir -p build/

clean_doc:
	rm -f -r doc/
	mkdir -p doc/

pack:
	zip -r xjahod06_xnemco06.zip src/ doc/ example/ build/ Makefile doxyfile README.md