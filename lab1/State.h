#ifndef STATE
#define STATE
using namespace std;

class State{
public:
  double position;
  double velocity;
  double acceleration;
  double time;
  void set(double pos, double vel, double acc, double tim){
    position = pos;
    velocity = vel;
    acceleration = acc;
    time = tim;
  };

  State(){
    set(0,0,0,0);
  }

  State(double pos, double vel, double acc, double tim){
    set(pos,vel,acc,tim);
  }

};

inline ostream& operator<<(ostream& os, State& state){
  os<<"t:"<<state.time<<", x:"<<state.position<<", v:"<<state.velocity<<", a:"<<state.acceleration;
  return os;
}

#endif
