#ifndef EVENTDISPLAY_FUNC_HH
#define EVENTDISPLAY_FUNC_HH

// c++ STL
#include <memory>
#include <vector>

// ROOT library
#include <TH2D.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
// function to use eventdisplay analize

void eventdisplay_plot(TH2D* h_hit,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom);
// function to plot all hits to given histogram 
void eventdisplay_plot_dir(TH2D* h_hit,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,std::vector<int>* vhitdirorref);
// function to plot hit by direct photon to given histogram
void eventdisplay_plot_ref(TH2D* h_hit,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,std::vector<int>* vhitdirorref);
// function to plot hit by reflect photon to given histogram
void eventdisplay_plot_dir_restrict(TH2D* h_hit,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,std::vector<int>* vhitdirorref,std::vector<double>* vhitgoodness);
// function to plot hit by direct photon to given histogram 
// corresponding goodness larger than 1/e is plotted
void eventdisplay_plot_ref_restrict(TH2D* h_hit,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,std::vector<int>* vhitdirorref,std::vector<double>* vhitgoodness);
// function to plot hit by reflect photon to given histogram
// corresponding goodness larger than 1/e is plotted
#endif
