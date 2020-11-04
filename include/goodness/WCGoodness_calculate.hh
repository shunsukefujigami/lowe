#ifndef WCGOODNESS_CALCULATE_HH
#define WCGOODNESS_CALCULATE_HH
//C++ STL
#include <memory>

// self-introduced library
#include "CSearch_range.hh"
#include "goodness_data.hh"
#include "runoption.hh"

goodness_data WCGoodness_calculate(CSearch_range range,std::shared_ptr<runoption> option);
// function to exercise grid search of goodness
#endif
