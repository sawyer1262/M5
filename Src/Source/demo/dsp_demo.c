

#include "type.h"
#include <math.h>
#include "arm_math.h"
#include "debug.h"
#include "dsp_demo.h"

/* ----------------------------------------------------------------------
* Defines each of the tests performed
* ------------------------------------------------------------------- */
#define MAX_BLOCKSIZE   32
#define DELTA           (0.0001f)


/* ----------------------------------------------------------------------
* Test input data for Floating point sin_cos example for 32-blockSize
* Generated by the MATLAB randn() function
* ------------------------------------------------------------------- */

const FP32 testInput_f32[MAX_BLOCKSIZE] =
{
  -1.244916875853235400,  -4.793533929171324800,   0.360705030233248850,   0.827929644170887320,  -3.299532218312426900,   3.427441903227623800,   3.422401784294607700,  -0.108308165334010680,
   0.941943896490312180,   0.502609575000365850,  -0.537345278736373500,   2.088817392965764500,  -1.693168684143455700,   6.283185307179590700,  -0.392545884746175080,   0.327893095115825040,
   3.070147440456292300,   0.170611405884662230,  -0.275275082396073010,  -2.395492805446796300,   0.847311163536506600,  -3.845517018083148800,   2.055818378415868300,   4.672594161978930800,
  -1.990923030266425800,   2.469305197656249500,   3.609002606064021000,  -4.586736582331667500,  -4.147080139136136300,   1.643756718868359500,  -1.150866392366494800,   1.985805026477433800


};

const FP32 testRefOutput_f32 = 1.000000000;

/* ----------------------------------------------------------------------
* Declare Global variables
* ------------------------------------------------------------------- */
uint32_t blockSize = 32;
FP32  testOutput;
FP32  cosOutput;
FP32  sinOutput;
FP32  cosSquareOutput;
FP32  sinSquareOutput;

/* ----------------------------------------------------------------------
* Max magnitude FFT Bin test
* ------------------------------------------------------------------- */

arm_status status;

void sin_cos_demo(void)
{
  FP32 diff;
  UINT32 i;
	
	FP32 a[2] = {2,3};
	FP32 b[2] = {4,5};
	
	FP32 e[2] = {0};
	
	cosOutput = 2;
	sinOutput = 3;
	
	arm_mult_f32(a, a, e, 1);
	arm_mult_f32(a, a, e, 2);
	arm_mult_f32(a, b, e, 1);
	arm_mult_f32(a, b, e, 2);
	
//sin^2+cos^2=1
  for(i=0; i< blockSize; i++)
  {
    cosOutput = arm_cos_f32(testInput_f32[i]);
    sinOutput = arm_sin_f32(testInput_f32[i]);
		
		printf("COS(x) =  %f   sin(x) = %f \r\n",cosOutput,sinOutput);  
		

    arm_mult_f32(&cosOutput, &cosOutput, &cosSquareOutput, 1);		//cos平方
    arm_mult_f32(&sinOutput, &sinOutput, &sinSquareOutput, 1);		//sin平方

    arm_add_f32(&cosSquareOutput, &sinSquareOutput, &testOutput, 1);//平方加

    /* absolute value of difference between ref and test */
    diff = fabsf(testRefOutput_f32 - testOutput);
	
		printf("sin2(x)+cos2(x) = %f  diff =  %f \r\n",testOutput,diff);  
    /* Comparison of sin_cos value with reference */
    if (diff > DELTA)
    {
       status = ARM_MATH_TEST_FAILURE;
    }

    if ( status == ARM_MATH_TEST_FAILURE)
    {
				printf("block %d fail!\r\n",i);      
				return;
    }
		
		printf("block %d success!\r\n",i);
  }
	
}


void DSP_Demo(void)
{
	sin_cos_demo();
}
