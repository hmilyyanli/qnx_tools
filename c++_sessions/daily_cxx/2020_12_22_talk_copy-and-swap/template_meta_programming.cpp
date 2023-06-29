#include "dummy_array.h"
#include <memory>
Dummy_Array CreateNew(void)
{
    Dummy_Array temp(5);
    return temp;
}

void dump_array(Dummy_Array&& arr)
{
    std::cout<<"dummy_array[0]: "<<arr[0]<<"dummy_array[1] "<<arr[1]<<std::endl;
}
int main()
{
    Dummy_Array arr1(10);
    arr1[0]=10;
    arr1[1]=11;
    std::cout<<"val0: "<<arr1[0]<<"val1 "<<arr1[1]<<std::endl;
    const Dummy_Array arr2(arr1);
    Dummy_Array arr3=arr2;
    std::cout<<"arr3[0]: "<<arr3[0]<<"arr3[1] "<<arr3[1]<<std::endl;
    Dummy_Array arr4;
    arr4=arr3;
    std::cout<<"arr4[0]: "<<arr4[0]<<"arr4[1] "<<arr4[1]<<std::endl;
    Dummy_Array&& rarr5=CreateNew();
    std::cout<<"arr5[0]: "<<rarr5[0]<<"arr5[1] "<<rarr5[1]<<std::endl;
    auto pDummy = std::make_unique<Dummy_Array>(arr4);
    std::cout<<"arr6[0]: "<<(*pDummy)[0]<<"arr6[1] "<<(*pDummy)[1]<<std::endl;
    dump_array(std::move(arr1));
    std::cout<<"val0: "<<arr1[0]<<"val1 "<<arr1[1]<<std::endl;
    return 0;
}
