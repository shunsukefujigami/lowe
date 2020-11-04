// c++ STL
#include <memory>
// ROOT library
#include <TLorentzVector.h>
// WCSim library

// self-introduced library
#include "CSearch_range.hh"
#include "goodness_data.hh"
#include "runoption.hh"

goodness_data WCGoodness_calculate(CSearch_range range,std::shared_ptr<runoption> option)
{
  goodness_data data;
  double x = range.GetXmin();
  for( int i = 0; i < range.GetXNum() ; ++i , x += range.GetXwidth() )
    {
      double y = range.GetYmin();
      for( int j = 0 ; j < range.GetYNum() ; ++j , y += range.GetYwidth() )
	{
	  double z = range.GetZmin();
	  for(int k = 0; k < range.GetZNum() ; ++k , z += range.GetZwidth() )
	    {
	      double t = range.GetTmin();
	      for(int l = 0; l < range.GetTNum() ; ++l , t+= range.GetTwidth() )
		{
		  TLorentzVector vector(x,y,z,t);
		  auto gfunc = option->gfunc;
		  double g_onretro = gfunc(vector,option);
		  if(data.Getgoodness() < g_onretro)
		    {
		      data.Setgoodness(g_onretro);
		      data.Set4Vector(vector);
		    }
		  else{}
		}
	    }
	}
    }
  return data;
}
