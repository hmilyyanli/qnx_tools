// Example program
#include <iostream>
#include <string>
 
class writer
{
    public:
    int a;
    writer()
    {
        std::cout<<"Constructed"<<std::endl;
        a=1;
    }
    writer(int v):a(v)
    {
	std::cout<<" V Constructed"<<std::endl;
    }
    ~writer()
    {
        std::cout<<"Destroyed"<<std::endl;
    }
};
 
void func_1()
{
    static writer test;
}

enum nvm_surf_type
{
	NVM_SURF_ATTR_BITS_PER_COMPONENT_0,
	NVM_SURF_ATTR_BITS_PER_COMPONENT_1,
	NVM_SURF_ATTR_BITS_PER_COMPONENT_2
};

#define ELEMENT_NAME(name,index)    name##_##index

int main()
{
  
    for(int x=0; x<10; x++)
    {
	nvm_surf_type name= ELEMENT_NAME(NVM_SURF_ATTR_BITS_PER_COMPONENT,2);
	//writer ELEMENT_NAME(test,x)(x);
       // for(int y=0; y<10; y++)
        //{
        //    func_1();
        //}
    }
    std::cout<<"End of Main"<<std::endl;
}
