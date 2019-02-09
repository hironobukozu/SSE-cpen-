#include<iostream>
#include<string>
#include<cmath>
#include"State.h"
#include"Car.h"
using namespace std;



int main(){
  Car car1("Mazda 3",1600,790,0.61);
  Car car2("Toyota Prius",1450,740,0.58);

  State state1();
  State state2();

  double dt = 0.01;

  car1.accelerate(true);
  car2.accelerate(true);

  double v = 0;
  double a = 0;
  double x = 0;
  int n = 0;
  for (double t =0; t<=60; t+= dt){
    car1.drive(dt);
    car2.drive(dt);

    n=n+1;
    if(n%100 == 0){

    if(car1.getPos()>car2.getPos()){
      cout<<car1.getModel()<<" is in the lead"<<endl;
    } else if(car1.getPos()<car2.getPos()) {
      cout<<car2.getModel()<<" is in the lead"<<endl;
    }
  }

    if(car1.getPos()>=403.2 && car2.getPos()>=403.2){
      car1.accelerate(false);
      car2.accelerate(false);
      exit;

    }

  }
  if(car1.getPos()>car1.getPos()){
    cout<<"Winner:"<<car1.getModel()<<endl;
  }else{
    cout<<"Winner:"<<car2.getModel()<<endl;
  }
return 0;

}
