#ifndef VEVENT_HH
#define VEVENT_HH

class VEvent
{
public:
  VEvent(){};
  virtual ~VEvent(){};
  void SetEventID(int i)
  {
    eventID = i;
  }
  int GetEventID() const 
  {
    return eventID;
  }
protected:
  int eventID;
};

#endif
  
