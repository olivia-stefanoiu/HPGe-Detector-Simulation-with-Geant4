#ifndef STEPPING_HH
#define STEPPING_HH

//de inclus anumite file...
#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "construction.hh"
#include "event.hh"
#include "run.hh"


//similara cu MyRunAction...
class MySteppingAction : public G4UserSteppingAction
{
  public:
    MySteppingAction(MyEventAction* eventAction);
    ~MySteppingAction()override;
    
     void UserSteppingAction(const G4Step*)override; //basic function
    
  private:
    MyEventAction *fEventAction;
};

#endif
