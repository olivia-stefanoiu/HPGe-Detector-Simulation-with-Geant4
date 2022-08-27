#ifndef EVENT_HH //if not define... then define
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

//to store
#include "G4AnalysisManager.hh"

//to access the runAction
#include "run.hh"

//root
#include "G4AnalysisManager.hh"

class MyRunAction;
class MyEventAction : public G4UserEventAction {
public:
    MyEventAction(MyRunAction *runAction);

    ~MyEventAction() override;

    //moments of the EVENT - 2 functii virtuale ... (membre)
    void BeginOfEventAction(const G4Event *) override;
    void EndOfEventAction(const G4Event *) override;

    void AddEdep(G4double edep) { fEdep += edep;fEdeptTotal+=edep;} //fct. de transfer a energiei depozitate(tip double)

private:
    MyRunAction* fRunAction =nullptr;
    G4double fEdep = 0.,fEdeptTotal=0.; //energia depozitata este privata

};

#endif
