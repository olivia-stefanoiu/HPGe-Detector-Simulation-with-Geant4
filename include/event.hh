#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

#include "run.hh"


class MyEventAction : public G4UserEventAction {
public:
    MyEventAction(MyRunAction *runAction);

    ~MyEventAction() override;

    void BeginOfEventAction(const G4Event *) override;

    void EndOfEventAction(const G4Event *) override;

    void AddEdep(G4double edep) {
        fEdep += edep;
        fEdeptTotal += edep;
    }

private:
    MyRunAction *fRunAction = nullptr;

    G4double fEdep = 0.,
             fEdeptTotal = 0.;

};

#endif
