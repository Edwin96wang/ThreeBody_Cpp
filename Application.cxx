#include "Application.hh"
#include "TGraph.h"
#include "TLine.h"
#include "Rtypes.h"
#include "TMath.h"
#include "TAxis.h"
#include "TSystem.h"

extern double time_div;

using namespace std;

Application::Application(const char* name, vector<star*> star){
    app = new TApplication(name, 0, 0);
    stars = star;
    star_num = stars.size();
    line_start = get_star_positions();
    graph_setup();
}

void Application::set_canvas(int l, int w){
    canvas = new TCanvas("c","Three-body simulation",l,w);
}

void Application::graph_setup(){
    mg = new TMultiGraph();
    for(unsigned int i = 0; i < star_num; i++){
        graphs.push_back(new TGraph(1));
        graphs.back()->SetPoint(0, stars[i]->get_position().x(), stars[i]->get_position().y());
        graphs.back()->SetMarkerStyle(marker_style);
        graphs.back()->SetMarkerColor(stars[i]->get_color());
        mg->Add(graphs.back());
    }
}


void Application::start(){
    canvas -> Draw();
    mg->Draw("AP");
    while(true){
        update();
        plot_lines();
        plot_points();
        graph_resize();
        canvas->Update();
        //gSystem->Sleep(100);
        
    }
}

void Application::update(){
    for(const auto it: stars){
        it->acc_update(stars);
    }
    vector<double> time_list;
    for(const auto it: stars){
        time_list.push_back(it->time_d);
    }
    time_div = TMath::MinElement(time_list.size(), time_list.data());
    for(const auto it: stars){
        it->move();
    }
}

vector<TVector3> Application::get_star_positions(){
    vector<TVector3> vec_pos(0);
    for(const auto it: stars){
        vec_pos.push_back(it->get_position());
    }
    return(vec_pos);
}

void Application::plot_lines(){
    line_end = get_star_positions();
    for(unsigned int i =0; i < stars.size(); i++){
        lines.push_back(new TLine(line_start[i].x(),
                line_start[i].y(),line_end[i].x(),line_end[i].y()));
        lines.back()->SetLineColor(stars[i]->get_color());
        lines.back()->Draw("SAME");
    }
    line_start = get_star_positions();
}

void Application::plot_points(){
    for(unsigned int i =0; i < stars.size(); i++){
        graphs[i]->SetPoint(0, stars[i]->get_position().X(),
                stars[i]->get_position().Y());
    }
}

void Application::graph_resize(){
    int rang = 30;
    mg->GetYaxis()->SetRangeUser(-rang, rang);
    mg->GetXaxis()->SetLimits(-rang, rang);
    for(const auto it : graphs){
        it->GetYaxis()->SetRangeUser(-rang, rang);
        it->GetXaxis()->SetLimits(-rang, rang);
    }
}