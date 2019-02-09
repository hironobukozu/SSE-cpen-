#ifndef CAR
#define CAR
#include "State.h"
using namespace std;

class Car{
protected:
  string model;
  double mass;
  double engine_force;
  double drag_area;
  State state;

public:
  Car(string Model,double Mass,double Engine_force,double Drag_area){
    model = Model;
    mass = Mass;
    engine_force = Engine_force;
    drag_area = Drag_area;

  };
  string getModel();
  double getMass();
  void accelerate(bool on);
  virtual void drive(double dt);
  State getState();
  double getPos();
  double getVel();

};

class Prius : public Car{
public:
  Prius():Car("Toyota Prius",1450,740,0.58){};
};
class Mazda : public Car{
public:
  Mazda():Car("Mazda 3",1600,790,0.61){};
};
class Tesla : public Car{
public:
  Tesla():Car("Tesla",2000,1000,0.6){};
};
class Herbie : public Car{
public:
  Herbie():Car("Herbie",1000,2000,0.5){};
  void drive(double dt);
};

#endif
