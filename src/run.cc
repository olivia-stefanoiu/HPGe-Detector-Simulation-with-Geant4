#include "run.hh"


MyRunAction::MyRunAction() {

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent");

    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);

    man->CreateNtuple("Scoring", "Scoring");
    man->CreateNtupleDColumn("fEdep");
    man->FinishNtuple(1);

    G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(fEdepTotal);
}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run *run) {
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    //pentru a nu suprascrie output-ul
    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    man->OpenFile("output" + strRunID.str() + ".xml");

    G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();
}

void MyRunAction::EndOfRunAction(const G4Run *) {
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    G4cout << "Energia depozitata total: " << fEdepTotal.GetValue() << G4endl;

    man->Write();
    man->CloseFile();
}

void MyRunAction::AddEdepTotal(G4double edep) {
    fEdepTotal += edep;
}



