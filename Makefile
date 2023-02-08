all: pipe_spec_plplot docs

.PHONY: docs

pipe_spec_plplot: pipe_spec_plplot.c
	@echo "Compiling piped plotting tools"
	gcc -Wall pipe_spec_plplot.c -o pipe_spec_plplot -lplplot -lX11 -lfftw3 -lm -lrt -lpthread

docs:
	@echo "Creating documentation"
	@doxygen -g
	@sed -i~ 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "RA disp"/' Doxyfile
	@sed -i~ 's/GENERATE_HTML          = YES/GENERATE_HTML          = NO/' Doxyfile
	@doxygen ./Doxyfile
	@cd ./latex/ ; pdflatex refman.tex ; pdflatex refman.tex ; mv refman.pdf ../Readme.pdf
	@rm -rf ./latex
	@echo "Done documentation !"

clean : 
	rm -f pipe_spec_plplot
	rm -f Doxyfile*
	rm -rf 
	rm -rf html
	rm -rf latex