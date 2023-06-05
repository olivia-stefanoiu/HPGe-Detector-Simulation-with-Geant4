#include "run.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"




MyRunAction::MyRunAction() {

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent");

    man->CreateNtupleDColumn("Energy");
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

    man->OpenFile("output" + strRunID.str() + ".root");

    G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();
}

void MyRunAction::EndOfRunAction(const G4Run *) {
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    G4cout << "Energia depozitata total:""""""""""""""""""""""""' " << fEdepTotal.GetValue() << G4endl;
    for(int i =0;i<180;i++){
        if(myArray[i]!=0){
            G4cout<<i<<" "<<myArray[i]<<'\n';
        }

    }
    man->Write();
    man->CloseFile();
}

void MyRunAction::AddEdepTotal(G4double edep) {
    fEdepTotal += edep;
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(0, evt);


    myArray[int(edep*100)]++;
    man->AddNtupleRow(0);
    man->FillNtupleDColumn(1, edep);
}



