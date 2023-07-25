#include <stdio.h>
#include <complex.h>
#include <math.h>

#define PI 3.14159265359

void FFT(complex double* x, int N)
{
    if (N <= 1)
        return;
    
    complex double even[N/2];
    complex double odd[N/2];
    
    for (int i = 0; i < N/2; i++)
    {
        even[i] = x[2*i];
        odd[i] = x[2*i + 1];
    }
    
    FFT(even, N/2);
    FFT(odd, N/2);
    
    for (int k = 0; k < N/2; k++)
    {
        complex double t = cexp(-I * 2 * PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N/2] = even[k] - t;
    }
}

int main()
{
    int N = 8;  // Number of samples
    complex double x[N];  // Input signal
    
    // Initialize input signal (example: unit impulse)
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
            x[i] = 1;
        else
            x[i] = 0;
    }
    
    // Perform FFT
    FFT(x, N);
    
    // Display FFT results
    printf("FFT Results:\n");
    for (int i = 0; i < N; i++)
        printf("%.2f + %.2fi\n", creal(x[i]), cimag(x[i]));
    
    return 0;
}
