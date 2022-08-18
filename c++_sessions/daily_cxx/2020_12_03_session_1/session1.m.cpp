// #include <iostream>

void exercise1() {
  class T;
  T t();
}
// yes it is a function declaration

void exercise2() {
  class T {};
  T t1();
  // T t2 = t1; // no viable conversion from T() to T;
}

// void exercise3() {
//   class T;
//   T t;
//   T t2 = t;
//   // variable is not fully defined ot be used
// }

void exercise4() {
  class T {};
  T t;
  T t2 = t;
  // everything fine: constructor call
}

// int main() { ::std::cout << "hello session1\n"; }
