#include <stdio.h>
#include <string.h>

int main()
{
	int const width=720;
	int const height=480;
	int data=0xff0000ff;
	int idx_h,idx_w;
	FILE* fd;
	fd=fopen("test.rgb","w+");
	if(fd==NULL)
	{
		printf("open failed\n");
		exit(1);
	}
	for(idx_w=0;idx_w < height/3; idx_w++)
	{
		for(idx_h=0;idx_h < width; idx_h++)
			fwrite(&data,sizeof(int),1,fd);
	}
#if 1
	data=0xff00ff00;
	for(idx_w=height/3;idx_w < height*2/3; idx_w++)
        {
		for(idx_h=0;idx_h < width; idx_h++)
                        fwrite(&data,sizeof(int),1,fd);
        }
	data=0xffff0000;
	for(idx_w=height*2/3;idx_w < height; idx_w++)
        {
		for(idx_h=0;idx_h < width; idx_h++)
                        fwrite(&data,sizeof(int),1,fd);
        }
#endif	
	fflush(fd);
	fclose(fd);
	exit(0);
}
