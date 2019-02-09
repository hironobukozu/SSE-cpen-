#include<iostream>
#include<string>
#include "physics.h"
#include "State.h"
#include "Car.h"
using namespace std;

string Car::getModel(){
  return model;
}

double Car::getMass(){
  return mass;
}

void Car::accelerate(bool on){
  if(on == true){
    engine_force = engine_force;
  }else {
    engine_force = 0;
  }
}


void Car::drive(double dt){
    double f = engine_force-physics::f_drag(drag_area, state.velocity);
    state.acceleration = physics::compute_acceleration(f, mass);
    state.velocity = physics::compute_velocity(state.velocity, state.acceleration, dt);
    state.position = physics::compute_position(state.position, state.velocity, dt);
  }


State Car::getState(){
   return state;
}

double Car::getPos(){
  return state.position;
}

double Car::getVel(){
  return state.velocity;
}

void Herbie::drive(double dt){
  state.acceleration = physics::compute_acceleration(engine_force, mass);
  state.velocity = physics::compute_velocity(state.velocity, state.acceleration, dt);
  state.position = physics::compute_position(state.position, state.velocity, dt);

}
