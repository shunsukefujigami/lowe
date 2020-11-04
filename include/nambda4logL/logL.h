#ifndef LOGL_H
#define LOGL_H
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
double logL(WCSimRootTrigger *wcsimroottrigger,WCSimRootGeom *wcsimrootgeom,const double sigma,const double parameter[]);
#endif
