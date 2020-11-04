#ifndef LOOPNAMBDA4LOGL_H
#define LOOPNAMBDA4LOGL_H
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
void loopnambda4logL(double (&parameter)[4],WCSimRootTrigger *wcsimroottrigger,WCSimRootGeom *wcsimrootgeom,const double sigma,double first_value[],int n_loop,double threshold_min[4],double threshold_max[4]);
#endif
