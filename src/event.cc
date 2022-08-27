#include "event.hh"

//constructorul;
MyEventAction::MyEventAction(MyRunAction *runAction):fRunAction(runAction) {

}

MyEventAction::~MyEventAction() {}

void MyEventAction::BeginOfEventAction(const G4Event *) {
    fEdep = 0.; //energia este setata la 0(la fiecare start, de fiecare data)

}

void MyEventAction::EndOfEventAction(const G4Event *) {
    G4cout << "Energia depozitata: " << fEdep << G4endl;
    fRunAction->AddEdepTotal(fEdep);

    //accesarea unui manager pentru analiza distrib de energie depozitata
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleDColumn(1, 0, fEdep); //a new Tuple
    man->AddNtupleRow(1); //generam o alta intrare/row - pentru distributia de valori

}


