/**
 * @file dada2spec.c
 * @author Jishnu N. Thekkeppattu (j.thekkeppattu@curtin.edu.au)
 * @brief 
 * @version 0.1
 * @date 2023-02-08
 * @brief Reads a psrdada file and generates spectra out of them. The number of FFT bins and required time averaging can be specified.
 * 
 * 
 */

#include <stdio.h>
#include <stddef.h>
#include <assert.h>
// #include <sys/mman.h>
// #include <sys/stat.h>        
// #include <fcntl.h>           
#include <unistd.h>
#include <stdlib.h>
// #include <time.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
static volatile int run_acq = 1;

void intHandler_acq(int dummy) 
{
    run_acq = 0;
}

void print_acq_usage(char * const argv[]) 
{
    fprintf(stderr,"Usage:\n%s [options]\n",argv[0]);
    fprintf(stderr,"\t-f filename       \t filename has no defaults\n");
    fprintf(stderr,"\t-N NFFT           \t FFT channels. default: 512\n");
    fprintf(stderr,"\t-i integration(s) \t integration time in seconds. default: 1\n");
    fprintf(stderr,"\t-v                \t print verbose information\n");
    exit(0);
}


int main (int argc, char *argv[])
{

    int res, opt, NFFT=512, tsec=1;
    bool verb_flag=false;
    char *dada_filename = NULL;
    FILE *fd = NULL;

    if (argc<2) print_acq_usage(argv);
    while ((opt = getopt(argc, argv, "vf:N:i:")) != -1) 
    {
        switch (opt) 
        {
        case 'f':
            dada_filename = optarg;
            break;
        case 'i':
            tsec = atoi(optarg);
            break;
        case 'N':
            if      (1 < atoi(optarg) && atoi(optarg) < 65536) NFFT = atoi(optarg);
            else 
            {
                fprintf(stderr,"FFT bins should be 1<N<65536!\n");
                print_acq_usage(argv);
                exit(0);
            }
            break;
        case 'v':
            verb_flag = true;
            break;
        default: 
            fprintf(stderr,"unknown option %d\n",opt);
            print_acq_usage(argv);
            exit(0);
        }
    }
    fd = fopen(dada_filename, "r");
    if(fd == NULL)
    {
        printf("Looks like file does not exist. Quitting\n");   
        exit(1);             
    }
    printf ("Input file is %s\n", dada_filename);
    printf ("Performing %d point FFT with %d second(s) of integration.\n", NFFT, tsec);
    signal(SIGINT, intHandler_acq);
    while (run_acq)
    {
        
    }
    if (verb_flag) printf("\nClosing the file\n");
    fclose(fd);
    printf("Exiting \n");
    return 0;
}