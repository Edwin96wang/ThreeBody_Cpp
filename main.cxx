#include <iostream>
#include <vector>
#include "star.hh"
#include "Application.hh"
#include "Rtypes.h"

using namespace std;

double dis_min = 0.01;
double G_value = 0.1;
double time_div; 

int main(){

    star a = star("a");
    star b = star("b");

    a.set_mass(1);
    b.set_mass(200);

    a.set_color(EColor(kRed));
    b.set_color(EColor(kBlack));

    a.set_position(10, 0, 0);
    b.set_position(0, 0, 0);

    a.set_velocity(0, 1, 0);
    b.set_velocity(0, 0, 0);

    vector<star*> stars = {&a, &b};
    auto app = new Application("app", stars);
    app->set_canvas(900, 900);
    app->start();
    return 0;
}