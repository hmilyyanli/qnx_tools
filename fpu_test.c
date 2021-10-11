#include <stdio.h>
#include <tgmath.h>
#include <arm_neon.h>
int main()
{
	float64x1_t a= (float64x1_t)(-0.1234);
	float64x1_t sum = (float64x1_t)(0.0);
	int idx;
	for(idx = 0; idx < 0x100000; idx++)
	{
		//sum=fabs(a);
		sum = vabs_f64(a);
		a -= 0.001;
	}
	printf("completed\n");
	return 0;
#if 0
	float a=5.625;
	float b=5.625;
	float res_add,res_sub,res_mul,res_div;
	res_add = a+b;
	res_sub = a-b;
	res_mul = a*b;
	res_div = a/b;
	printf("res_add %f\n",res_add);
	printf("res_sub %f\n",res_sub);
	printf("res_mul %f\n",res_mul);
	printf("res_div %f\n",res_div);
#endif
		
}
