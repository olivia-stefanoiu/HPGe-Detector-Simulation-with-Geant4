//clip8 stocare date(hits data ) intr-un Root file
#ifndef RUN_HH
#define RUN_HH

//clasele necesare
#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"
#include "G4AnalysisManager.hh"
#include "G4UserRunAction.hh"
#include "G4Run.hh"

class MyRunAction : public G4UserRunAction //define a class for action 
{

public:
    MyRunAction();

    ~MyRunAction() override;

    void BeginOfRunAction(const G4Run *) override;

    void EndOfRunAction(const G4Run *) override;

    void AddEdepTotal(G4double edep);

private:
    G4Accumulable<G4double> fEdepTotal = 0.;
};

#endif
