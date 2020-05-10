# Project: ICP 2020
# File: Makefile
# Title: Transport Map
# Authors: Vojtěch Jahoda (xjahod06)
#          Silvie Němcová (xnemco06)

make: qMakefile
	make -f qMakefile --directory=build/
	mv build/ICP_2020_proj ./

qMakefile:
	qmake -o build/qMakefile src/ICP_2020_proj.pro

doxygen:
	doxygen doxyfile

clean:
	rm -f *.zip
	rm -r build/
	rm -r doc/
	mkdir doc/
	mkdir build/
	
pack:
	zip -r xjahod06_xnemco06.zip src/ doc/ example/ build/ Makefile doxyfile