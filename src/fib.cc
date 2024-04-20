// dip.cc
// 引入必要的头文件；
#include <emscripten.h>

// 以C语言的方式导出，避免 name mangling
extern "C"
{
  // fib函数；
  // 告诉Emscripten编译器在编译时不要移除这个函数(不要给它 tree-shaking掉)
  EMSCRIPTEN_KEEPALIVE int fib(int n)
  {
    if (n == 0 || n == 1)
    {
      return 1;
    }

    return fib(n - 1) + fib(n - 2);
  }
}
