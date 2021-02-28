//Function File for FMA code 

#include "pch.h" 
#include <openacc.h>

//FMA operation 
void CPU_FMA(float *A, float *B, float *C, float *D, const int rows, const int cols)
{
        float fSum;
        for (int i=0; i<cols;i++)
        {
                for(int j = 0; j<rows; j++)
                {
                        fSum = 0.0f;
                        for(int k=0; k<rows; k++)
                        {
				//linear adressing multiplication 
                                fSum +=(A[(i*rows)+k]*B[(k*rows)+j]);
                        }
			//Addition
                        D[(i*rows)+j] = fSum + C[(i*rows)+j];
                }
        }
}

//OpenAcc FMA execution
void ACC_FMA(float *A, float *B, float *C, float *D, const int nx, const int ny)
{
	float fSum; 
        //Initial transfer of data to the GPU
 	#pragma acc enter data copyin(fSum) create(D[:nx*ny])
	//Inform compiler that Matrix data has already been moved to the GPU
	#pragma acc data present(A[:nx*ny],B[:nx*ny],C[:nx*ny]) 	
	//Directive to indicate what should be executed on the GPU
	#pragma acc parallel loop collapse(2)
	for (int i=0; i<ny;i++)
        {
		//#pragma acc loop independent
		for(int j = 0; j<nx; j++)
                {
			fSum = 0.0f;
			#pragma acc loop seq //reduction(+:fSum)
			for(int k=0; k<nx; k++)
                        {
				fSum +=(A[(i*nx)+k]*B[(k*nx)+j]);
			}
			D[(i*nx)+j] = fSum + C[(i*nx)+j];
		}
	}
}


//Print Function to display first 3 elements 
void DisplayElements(float *temp, const int nx)
{
	printf("\n Displaying first element of first 3 rows of output Matrix \n"); 
	for (int i=0; i<3; i++) 
	{
		printf("Element [%d] = %f \n",(i*nx),temp[i*nx]);
	}	
}