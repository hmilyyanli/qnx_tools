#include <stdio.h>

int function2(void) 
{
  static int i, state = 0;
  switch (state) 
  {
    case 0:
    for (i = 0; i < 10; i++) 
    {
      state = 1;
      return i;
      case 1:;
    }
  }
}
int main()
{
    fprintf(stdout, "func0 : %d\n", function2());
    fprintf(stdout, "func1 : %d\n", function2());
    fprintf(stdout, "func2 : %d\n", function2());
    fprintf(stdout, "func3 : %d\n", function2());
    fprintf(stdout, "func4 : %d\n", function2());
    fprintf(stdout, "func5 : %d\n", function2());
    fprintf(stdout, "func6 : %d\n", function2());

    return 0;
}
