all: dada2spec docs tidyup

.PHONY: docs

dada2spec: dada2spec.c
	@echo "Compiling psrdada tools"
	gcc -Wall dada2spec.c -o dada2spec -lfftw3 -lm -lrt -lpthread

docs:
	@echo "Creating documentation"
	@doxygen -g
	@sed -i~ 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "psrdada tools"/' Doxyfile
	@sed -i~ 's/GENERATE_HTML          = YES/GENERATE_HTML          = NO/' Doxyfile
	@doxygen ./Doxyfile
	@cd ./latex/ ; pdflatex refman.tex ; pdflatex refman.tex ; mv refman.pdf ../Readme.pdf
	@rm -rf ./latex
	@echo "Done documentation !"

tidyup:
	rm -f Doxyfile*
	rm -rf html
	rm -rf latex

clean: 
	rm -f dada2spec
	rm -f Doxyfile*
	rm -rf html
	rm -rf latex
