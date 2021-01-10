#include <TFile.h>
#include <TH2D.h>

class complex
{
public:
  complex(double r,double i)
    :real(r),image(i)
  {
  }
  virtual ~complex()
  {
  }
  double Getreal()
  {
    return real;
  }
  double Getimage()
  {
    return image;
  }
  
  complex operator+(complex& c)
  {
    return complex(c.Getreal() + real,c.Getimage() + image);
  }
  complex operator*(complex& c)
  {
    double newreal = c.Getreal()* real - c.Getimage()* image;
    double newimage = c.Getimage()* real + c.Getreal()* image;
    return complex(newreal,newimage);
  }

  double Abs()
  {
    return real*real + image* image;
  }
  
private:
  double real;
  double image;
};

complex tocomplex(double d)
{
  return complex(d,0.);
}

complex zn(complex c,int n,complex z0)
{
  if(n != 0)
    {
      complex znminus1 = zn(c,n-1,z0);
      return znminus1*znminus1 + c;
    }
  if(n == 0)
    return z0;
}

int main()
{
  TFile* outfile = new TFile("~/retro/lowe/mandelbro.root","recreate");
  int xnum = 10000;
  double xmin = -2.;
  double xmax = 1.;
  double xwidth = (xmax - xmin)/(double)xnum;
  int ynum = 10000;
  double ymin = -1.5;
  double ymax = 1.5;
  double ywidth = (ymax - ymin)/(double)ynum;
  int loopnum = 30;
  TH2D* h1 = new TH2D("mandelbro","",xnum,xmin,xmax,ynum,ymin,ymax);
  complex c(-0.3,-0.63);
  for(double x = xmin; x < xmax; x+= xwidth)
    {
      for(double y = ymin; y < ymax; y+= ywidth)
	{
	  complex z0(x,y);
	  if(zn(c,loopnum,z0).Abs() < 2.)
	    h1->Fill(x,y);
	}
    }
  outfile->Write();
  outfile->Close();
  return 0;
}

  
