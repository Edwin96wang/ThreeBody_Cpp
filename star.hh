#pragma once

#include <string>  
#include <vector>
#include "TVector3.h"
#include "Rtypes.h"

using namespace std;

extern double dis_min;
extern double G_value;
extern double time_div; 


class star{
    public:
    star(string fname);
    void set_position(double x1, double x2, double x3);
    void set_velocity(double v1, double v2, double v3);
    void set_mass(float m);
    void set_color(EColor c);
    void move();
    void acc_update(vector<star*> s);
    TVector3 force(TVector3 dis, double m);
    TVector3 get_position();
    double get_mass();
    TVector3 get_velocity();
    TVector3 get_acceleration();
    EColor get_color();
    double time_d;




    private:
    string name;
    double mass = 1.0;
    TVector3 position = TVector3(0, 0, 0);
    TVector3 velocity = TVector3(0, 0, 0);
    TVector3 acceleration = TVector3(0, 0, 0);
    EColor color = EColor(kBlack);
};