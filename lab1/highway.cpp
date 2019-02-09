
#include <iostream>
#include <string>
#include "State.h"
#include "Car.h"



int main() {

  Car* car1[100];
  Car* car2[100];
  Car* car3[100];

  for (int i=0; i<100; ++i) {
    car1[i] = new Prius();
    car2[i] = new Mazda();
    car3[i] = new Tesla();
  }

  Herbie herbie;
  Car* her = &herbie;

  double dt = 1;

  for(int t=0; t<=10 ;++dt){
	  for (int i = 0; i <= 99;i=i+1) {
		  car1[i]->drive(dt);
		  car2[i]->drive(dt);
		  car3[i]->drive(dt);
	  }
      her->drive(dt);
	  if (car1[99]->getVel() >= 27.8) {
		  break;
	  }
  }
  for (int i = 0; i <= 99; ++i) {
    cout<<car1[i]->getModel()<<" is at "<<car1[i]->getPos()<<endl;
    cout<<car2[i]->getModel()<<" is at "<<car2[i]->getPos()<<endl;
    cout<<car3[i]->getModel()<<" is at "<<car3[i]->getPos()<<endl;
  }
  cout<<her->getModel()<<" is at "<<her->getPos()<<endl;
  for(int i=0;i<=99;++i){
    delete car1[i];
    delete car2[i];
    delete car3[i];
  }

return 0;
  }
