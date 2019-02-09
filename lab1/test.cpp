#include<iostream>
#include<string>
#include"Car.h"
#include"State.h"
using namespace std;

void Car::accelerate(bool on){
  if(true){
    engine_force = engine_force;
  }else{
    engine_force = 0;
  }
}


int main(){
  Car car1("Mazda 3",1600,790,0.61);
  Car car2("Toyota Prius",1450,740,0.58);

  car1.accelerate(true);
  car2.accelerate(true);




return 0;
}
