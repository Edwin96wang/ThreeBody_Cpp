#pragma once

#include "TApplication.h"
#include "TRint.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include "star.hh"

using namespace std;

class TGraph;
class TLine;
class TVector3;

class Application : public TApplication{
    public:
        Application(const char* name, vector<star*> star);
        void set_canvas(int l, int w);
        void graph_setup();
        void start();
        void update();
        vector<TVector3> get_star_positions();
        void plot_lines();
        void plot_points();
        void graph_resize();

    private:
        TApplication* app;
        TCanvas* canvas;
        TMultiGraph* mg;
        vector<star*> stars;
        unsigned int star_num = 0;
        vector<TGraph* > graphs;
        vector<TLine*> lines;
        unsigned int marker_style = 8;
        vector<TVector3> line_start;
        vector<TVector3> line_end;
};