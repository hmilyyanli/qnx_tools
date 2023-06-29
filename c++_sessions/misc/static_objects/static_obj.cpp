// Example program
#include <iostream>
#include <string>
 
class banana
{
    public:
    int banana_ID{0} ;
    banana()
    {  
        std::cout<<"Banana Picked and ....  ";
    }
    banana(int val)
    {
	banana_ID = val;
        std::cout<<"Banana value " << banana_ID << std::endl;
    }
    ~banana()
    {  
        std::cout<<"its gone!"<<std::endl;
    }
     
};
 
//int banana::banana_ID=0;
 
void f1(int num)
{
	if(num % 2)
	{
		static int count1 = 0;
		count1++;
		std::cout << "count1 " << count1 << std::endl;
	}
	else
	{
		static int count2 = 0;
		count2++;
		std::cout << "count2 " << count2 << std::endl;
	}
}
int main()
{  
    for(int x=0; x<10; x++)
    {
       static banana current_banana(x);
       //f1(x);
    }
    //std::cout<<"Total Bananas Eaten: "<<banana::banana_ID<<std::endl;
}
