# Daily C++ (#4)

## C.67: A polymorphic class should suppress copying (Cpp Core Guidelines)

## Example, bad

    class BaseBad {
    public:
      virtual ~BaseBad() = default;
      virtual int calc() const = 0;
    };
    
    class Derived1 : public BaseBad {
      int m_data;
    
    public:
      explicit Derived1(int f_data) : m_data{f_data} {}
    
      int calc() const override { return this->m_data; }
    };
    
    void slicing(BaseBad &b) {
      Derived1 d{10};
      b = d; // oops, slicing!
    }

## Example 

    class BaseGood {
    protected:
      BaseGood() = default;
      BaseGood(const BaseGood &) = default;
      BaseGood(BaseGood &&) noexcept = default;
    
      auto operator=(const BaseGood &) & -> BaseGood & = default;
      auto operator=(BaseGood &&) & -> BaseGood & = default;
    
    public:
      virtual ~BaseGood() = default;
      virtual int calc() const = 0;
    };
    
    class Derived2 : public BaseGood {
      int m_data;
    
    public:
      explicit Derived2(int f_data) : m_data{f_data} {}
    
      int calc() const override { return this->m_data; }
    };
    
    void slicing(BaseGood &b) {
      Derived2 d{11};
      // b = d; // compile error
    }
