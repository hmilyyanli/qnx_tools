#include <iostream>
//class without strong type

class Rectangle
{
    public:
        Rectangle(double width,double height):m_width(width),m_height(height){}
        auto get_width() -> double const
        {
            return m_width;
        }
    private:
        double m_width;
        double m_height;
};

template <typename T, typename Parameter>
class NamedType
{
    public:
        explicit NamedType(T const &_val):m_val(_val){}
         auto get_val() -> T
         {
             return m_val;
         }
         const T& get_val() const
         {
             return m_val;
         }
     private:
         T m_val;
};

using WIDTH=NamedType<uint32_t, struct width>;
using HEIGHT=NamedType<uint32_t, struct height>;

 class RectangleTyped
 {
     public:
         //using WIDTH=NamedType<uint32_t, struct width>;
         //using HEIGHT=NamedType<uint32_t, struct height>;
         RectangleTyped(WIDTH const width,HEIGHT const height):m_width(width.get_val()),m_height(height.get_val()){}
         double get_width() const
         {
             return m_width;
         }
     private:
         double m_width;
         double m_height;
 };

int main()
{
//problem 1: type convertion from 
    Rectangle r1(10U,20U);
//problem 2: can't see which parameter is width and which is height, and can't prevent the wrong order
    
    std::cout<<"width: "<<r1.get_width()<<std::endl;
    Rectangle r2(20U,10U);
    std::cout<<"width: "<<r2.get_width()<<std::endl;
    //NamedType<unsigned int,struct Width > width_t(10U);
    //NamedType<unsigned int,struct height> height_t(20U);
    //std::cout<<"width: "<<r2.get_width()<<std::endl;
    RectangleTyped r11(WIDTH(10U),HEIGHT(20U));
    //RectangleTyped r12(10U,20U);//compile error
    //RectangleTyped r13(HEIGHT(20U),WIDTH(10U));//compile error
    std::cout<<"width: "<<r11.get_width()<<std::endl;
}
