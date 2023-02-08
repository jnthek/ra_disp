all: pipe_spec_plplot

pipe_spec_plplot: pipe_spec_plplot.c
	@echo "Compiling piped plotting tools"
	gcc -Wall pipe_spec_plplot.c -o pipe_spec_plplot -lplplot -lX11 -lfftw3 -lm -lrt -lpthread

clean : 
	rm pipe_spec_plplot