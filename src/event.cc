#include "event.hh"


MyEventAction::MyEventAction(MyRunAction *runAction) : fRunAction(runAction) {

}

MyEventAction::~MyEventAction() {}

void MyEventAction::BeginOfEventAction(const G4Event *) {
    fEdep = 0.;

}

void MyEventAction::EndOfEventAction(const G4Event *) {
//    G4cout << "Energia depozitata: " << fEdep << G4endl;
    fRunAction->AddEdepTotal(fEdep);


    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleDColumn(1, 0, fEdep);
    man->AddNtupleRow(1);

}


