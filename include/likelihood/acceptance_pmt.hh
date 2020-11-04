#ifndef ACCEPTANCE_PMT_HH
#define ACCEPTANCE_PMT_HH

// c++ STL
#include <memory>
// self-introduced library

class runoption;

double acceptance_pmt_prototype(double theta,std::shared_ptr<runoption> option);
// function of acceptance of pmt. prototype return 1. This is based on http://www-sk.icrr.u-tokyo.ac.jp/sk/_pdf/articles/ikeda-dron.pdf page32 (4.3).
#endif
