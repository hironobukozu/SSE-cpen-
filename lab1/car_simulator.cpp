#include<iostream>
#include "physics.h"
#include "State.h"
using namespace std;

int main(){
cout<<"Enter the mass of the car(kg):";
double mass;
std::cin>>mass;

cout<<"Enter the net force of the engine(N):";
double engine_force;
cin>>engine_force;

cout<<"Enter the car's drag area (m^2):";
double drag_area;
cin>>drag_area;

cout<<"Enter the simulation time step(s):";
double dt;
cin>>dt;

cout<<"Enter the number ot time steps (int):";
int N;
cin>>N;

State A,B;
A.set(1,4,6,7);
B.set(12,8,9,7);
cout<<A<<endl;
cout<<B<<endl;

double x=0;
double v=0;
double a=0;
double t=0;

for(int i=0; i<N; i++){
  t+=dt;
  double f = engine_force-physics::f_drag(drag_area, v);
  a = physics::compute_acceleration(f, mass);
  v = physics::compute_velocity(v, a, dt);
  x = physics::compute_position(x, v, dt);

  cout<<"t:"<<t<<", a:"<<a<<", v:"<<v<<", x:"<<x<<endl;
}
return 0;
}
