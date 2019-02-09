#include <iostream>
#include <random>
#include <thread>
#include <cmath>   // for exp, abs

// three-dimensional point
struct Point {
  double x,y,z;
};

// virtual base class for functions
class Function {
 public:
  virtual double eval(double x, double y, double z) = 0;
};

// computes x*fn(x,y,z)
class XFunction : public Function {
  Function& fn;
 public:
  XFunction(Function& fn) : fn(fn){};
  double eval(double x, double y, double z) {
    return x*fn.eval(x,y,z);
  }
};

// computes y*fn(x,y,z)
class YFunction : public Function {
  Function& fn;
 public:
  YFunction(Function& fn) : fn(fn){};
  double eval(double x, double y, double z) {
    return y*fn.eval(x,y,z);
  }
};

// computes z*fn(x,y,z)
class ZFunction : public Function {
  Function& fn;
 public:
  ZFunction(Function& fn) : fn(fn){};
  double eval(double x, double y, double z) {
    return z*fn.eval(x,y,z);
  }
};

// new function for representing density 1
class Density1 : public Function {
 public:
  double eval(double x, double y, double z) {
    double norm2 = x*x+y*y+z*z;
    if (norm2 > 1) {
      return 0;
    }
    return std::exp(-norm2);
  }
};

class Density2 : public Function {
 public:
  double eval(double x, double y, double z) {
    double norm3 = x+y+z;
    if (norm3 > 1) {
      return 0;
    }
    return std::abs(norm3);
  }
};

class Density3 : public Function {
 public:
  double eval(double x, double y, double z) {
    double norm4 = (x-1)*(x-1)+(y-2)*(y-2)+(z-3)*(z-3);
    if (norm4 > 1) {
      return 0;
    }
    return norm4;
  }
};

int main() {
  std::default_random_engine rnd;
  std::uniform_real_distribution<double> dist(-1.0,1.0);
  // sample usage of functions
  Density1 d1;
  XFunction xd1(d1);  // x*d1(x,y,z)
  YFunction yd1(d1);  // y*d1(x,y,z)
  ZFunction zd1(d1);  // z*d1(x,y,z)

  Density2 d2;
  XFunction xd2(d2);
  YFunction yd2(d2);
  ZFunction zd2(d2);

  Density3 d3;
  XFunction xd3(d3);
  YFunction yd3(d3);
  ZFunction zd3(d3);



  std::cout << "d1.eval(0.1,0.2,0.3): " << d1.eval(0.1,0.2,0.3) << std::endl;
  std::cout << "xd1.eval(0.1,0.2,0.3): " << xd1.eval(0.1,0.2,0.3) << std::endl;
  std::cout << "yd1.eval(0.1,0.2,0.3): " << yd1.eval(0.1,0.2,0.3) << std::endl;
  std::cout << "zd1.eval(0.1,0.2,0.3): " << zd1.eval(0.1,0.2,0.3) << std::endl;

  std::cout << "d2.eval(0.1,0.2,0.3): " << d2.eval(0.1,0.2,0.3) << std::endl;
  std::cout << "xd2.eval(0.1,0.2,0.3): " << xd2.eval(0.1,0.2,0.3) << std::endl;
  std::cout << "yd2.eval(0.1,0.2,0.3): " << yd2.eval(0.1,0.2,0.3) << std::endl;
  std::cout << "zd2.eval(0.1,0.2,0.3): " << zd2.eval(0.1,0.2,0.3) << std::endl;

  std::cout << "d3.eval(0.1,0.2,0.3): " << d3.eval(0.1,0.2,0.3) << std::endl;
  std::cout << "xd3.eval(0.1,0.2,0.3): " << xd3.eval(0.1,0.2,0.3) << std::endl;
  std::cout << "yd3.eval(0.1,0.2,0.3): " << yd3.eval(0.1,0.2,0.3) << std::endl;
  std::cout << "zd3.eval(0.1,0.2,0.3): " << zd3.eval(0.1,0.2,0.3) << std::endl;



std::cin.get();

  return 0;
}
