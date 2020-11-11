// ROOT library
#include <TCanvas.h>

enum Detectortype
  {
    SK,
    HK };

void eventdisplay_edge(TCanvas* c1,Detectortype type=SK);
