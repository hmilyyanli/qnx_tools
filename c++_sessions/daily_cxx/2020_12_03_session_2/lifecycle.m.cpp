#include <aempty.h> // A

#include <iostream> // cout

void lifecycle() {
  using namespace ::std;
  cout << "begin lifecycle()\n";
  { // compount statement begin
    cout << "{\n=== begin Block\n";
    cout << "=== A a1;\n";
    A a1; // variable definition; default c'tor
    cout << "=== a1.i: " << a1.i << '\n';
    a1.i = 42;
    cout << "=== a1.i=42: " << a1.i << '\n';
    A a2 = a1; // copy c'tor via =
    cout << "a2.i: " << a2.i << '\n';
    cout << "=== A a3(a1);" << endl;
    A a3(a1); // copy c'tor via ()
    cout << "a3.i: " << a3.i << '\n';
    a1.i = 43;
    cout << "=== a1.i = 43: " << a1.i << endl;

    cout << "=== a2 = a1" << endl;
    a2 = a1; // copy assignment
    cout << "a2.i: " << a2.i << endl;

    cout << "=== A a4(std::move(a1));" << endl;
    A a4(::std::move(a1)); // move c'tor
    cout << "a1.i: " << a1.i << endl;
    cout << "a4.i: " << a4.i << endl;

    cout << "a4 = ::std::move(a3);" << endl;
    a4 = ::std::move(a3); // move assignment
    cout << "a3.i: " << a3.i << endl;
    cout << "a4.i: " << a4.i << endl;

    cout << "\n=== end Block\n}\n";
  } // compount statement end
  cout << "end lifecycle()\n";
}
int main() { ::lifecycle(); }
