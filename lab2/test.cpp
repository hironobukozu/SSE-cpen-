#include <iostream>
#include <random>
#include <thread>
#include <cmath>   // for exp, abs
#include <array>

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

std::array <double,3>D;
std::array <double,3>XD;
std::array <double,3>YD;
std::array <double,3>ZD;


void integration(int n){
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

  for (int i = 0; i < n; i++) {
    double a = dist(rnd);
    double b = dist(rnd);
    double c = dist(rnd);

    D[0] += d1.eval(a,b,c);
    XD[0] += xd1.eval(a,b,c);
    YD[0] += yd1.eval(a,b,c);
    ZD[0] += zd1.eval(a,b,c);

    D[1] += d2.eval(a,b,c);
    XD[1] += xd2.eval(a,b,c);
    YD[1] += yd2.eval(a,b,c);
    ZD[1] += zd2.eval(a,b,c);

    D[2] += d3.eval(a,b,c);
    XD[2] += xd3.eval(a,b,c);
    YD[2] += yd3.eval(a,b,c);
    ZD[2] += zd3.eval(a,b,c);

  }
}



int main() {

int n = 100;

std::thread thread1(integration,n/2);
std::thread thread2(integration,n/2);

thread1.join();
thread2.join();


  std::cout << "d1.eval: " << D[0]/n << std::endl;
  std::cout << "xd1.eval: " << XD[0]/n << std::endl;
  std::cout << "yd1.eval: " << YD[0]/n << std::endl;
  std::cout << "zd1.eval: " << ZD[0]/n<< std::endl;

  std::cout << "d2.eval: " << D[1] / n << std::endl;
  std::cout << "xd2.eval: " << XD[1] / n << std::endl;
  std::cout << "yd2.eval: " << YD[1] / n << std::endl;
  std::cout << "zd2.eval: " << ZD[1] / n << std::endl;

  std::cout << "d3.eval: " << D[2] / n << std::endl;
  std::cout << "xd3.eval: " << XD[2] / n << std::endl;
  std::cout << "yd3.eval: " << YD[2] / n << std::endl;
  std::cout << "zd3.eval: " << ZD[2] / n << std::endl;


std::cin.get();

  return 0;
}
