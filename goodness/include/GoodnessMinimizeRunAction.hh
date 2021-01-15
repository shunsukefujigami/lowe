#ifndef GOODNESSMINIMIZERUNACTION_HH
#define GOODNESSMINIMIZERUNACTION_HH

class GoodnessMinimizeRunAction : public VAction
{
public:
  GoodnessMinimizeRunAction(const char* outfile_in,const char* infilelikelihood_in);
  virtual ~GoodnessMinimizeRunAction();
  void BeginOfAction(std::shared_ptr<Process> process);
  void EndOfAction(std::shared_ptr<Process> process);
private:
  const char* outfile;
  const char* cinfilelikelihood;
  

};

#endif
  
