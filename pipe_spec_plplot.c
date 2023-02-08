/**
 * @file pipe_spec_plplot.c
 * @author Jishnu N. Thekkeppattu (j.thekkeppattu@curtin.edu.au)
 * @version 0.1
 * @date 2023-02-03
 * @brief This is a sample consumer code to get data from a shared memory,  perform FFT using FFTW3 and plot using pgplot. 
 * 
 */


#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include <plplot/plplotP.h>
#include <fftw3.h>

#define NFFT 4096

void linspace(double *arra, double low_value, double high_value, int N_points)
{
	int i;
	double res;
	res = (high_value-low_value)/N_points;
	for (i=0; i<N_points; i++)
	{
		arra[i]=low_value+(i*res);
	}
}			

double array_min(double *in_array, int N_points)
{
    double min = in_array[0];
    int i;
    for(i=1; i<N_points; i++)
    {
        if(in_array[i] < min)
        {
            min = in_array[i];
        }
    }
    return min;
}

double array_max(double *in_array, int N_points)
{
	double max = in_array[0];
    int i;
    for(i=1; i<N_points; i++)
    {
        if(in_array[i] > max)
        {
            max = in_array[i];
        }
    }
    return max;
}

int main()
{
    int i, k, naver, r;

    fftw_plan p;
    double x_here[NFFT], power_spectrum[NFFT], avg_power_spec[NFFT];
    fftw_complex *inp_data, *out;
    unsigned char read_buffer[NFFT*2];

    inp_data = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NFFT);
    out      = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NFFT);

    p = fftw_plan_dft_1d((int)NFFT, inp_data, out, FFTW_FORWARD, FFTW_MEASURE);    
    
    linspace(x_here, -2.048000/2, 2.048000/2, NFFT);
    int fft_index=0;
    plinit(); 
    plstart("xwin", 1,1);
    // plenv(x_here[0], x_here[NFFT-1], 0, 1000, 0, 1); 

    while (1)
    {
        for (i=0; i<NFFT; i++)
        {
            avg_power_spec[i] = 0.0;
        }
        for (naver=0; naver<512; naver++)
        {
            r = read(STDIN_FILENO, read_buffer, NFFT*2);
            for (i=0; i<NFFT; i++)
            {
                inp_data[i][0] = (double)read_buffer[i*2 + 0];
                inp_data[i][1] = (double)read_buffer[i*2 + 1];
            }
            fftw_execute(p);

            for (k = 0; k < NFFT; ++k)
            {
                fft_index = (NFFT/2 + k) % NFFT;
                power_spectrum[k] = (out[fft_index][0]*out[fft_index][0] + out[fft_index][1]*out[fft_index][1]);
            }

            for (i=0; i<NFFT; i++)
            {
                avg_power_spec[i] += power_spectrum[i];
            }
        }
        // printf("%f\n", avg_power_spec[400]);
        plenv(x_here[0], x_here[NFFT-1], array_min(avg_power_spec, NFFT), array_max(avg_power_spec, NFFT), 0, 1); 

        plline(NFFT, x_here, avg_power_spec); 
        // sleep(1);
    }
    plend(); 
    fftw_destroy_plan(p);
    fftw_free(inp_data); 
    fftw_free(out);
    return 0;
}
