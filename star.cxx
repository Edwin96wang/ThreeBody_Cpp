#include "star.hh"
#include "TMath.h"
#include <iostream>
#include "Rtypes.h"

using namespace std;

extern double dis_min;
extern double G_value;
extern double time_div; 

star::star(string fname){
    name = fname;
}


void star::set_position(double x1, double x2, double x3){
    position = TVector3(x1, x2, x3);
}

void star::set_velocity(double v1, double v2, double v3){
    velocity = TVector3(v1, v2, v3);
}

void star::set_mass(float m){
    mass = m;
}

void star::set_color(EColor c){
    color = c;
}
void star::move(){
    position = position + velocity * time_div + \
                            1/2 * acceleration * time_div * time_div;
    velocity =velocity + time_div * acceleration;
}

void star::acc_update(vector<star*> s){
    vector<star*>::iterator pos = find(s.begin(), s.end(), this);
    if (pos != s.end()) s.erase(pos);

    TVector3 F_total = TVector3(0,0,0);
    for(const auto it : s){
        F_total = F_total + force(it->get_position(), it->get_mass());
    }
    acceleration = 1/mass*F_total;

    time_d = (sqrt(velocity.Mag2()+ 2 * acceleration.Mag()*dis_min) - velocity.Mag())/acceleration.Mag();
}
TVector3 star::force(TVector3 dis, double m){
    TVector3 r = dis - position;
    return( G_value * m * mass/TMath::Power(r.Mag(), 3)*r);
}

TVector3 star::get_position(){
    return(position);
}

double star::get_mass(){
    return(mass);
}

TVector3 star::get_velocity(){
    return(velocity);
}

TVector3 star::get_acceleration(){
    return(acceleration);
}

EColor star::get_color(){
    return(color);
}