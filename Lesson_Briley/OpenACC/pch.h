
#ifndef pch 
#define pch

//Add headers that you want to pre-compile here 
#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <math.h>
#include <openacc.h> 

//Function Declarations in Common
void InitializeMatrixSame(float *array, const int ny, const int nx, const float val);
void InitializeMatrixRand(float *array, const int ny, const int nx);
void MatrixVerification(float *hostC, float *gpuC, const int ny, const int nx, const float fTolerance);

//CPU functions
void CPU_FMA(float *A, float *B, float *C, float *D, const int nx, const int ny);

//Acc Functions
void ACC_FMA(float *A, float *B, float *C, float *accD, const int nx, const int ny);

#endif
