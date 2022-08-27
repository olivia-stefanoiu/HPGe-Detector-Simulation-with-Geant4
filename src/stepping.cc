#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
:fEventAction(eventAction){}


MySteppingAction::~MySteppingAction(){}


void MySteppingAction::UserSteppingAction(const G4Step *step)
{                                                                                                                
     G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume(); //lant
    
     const auto *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    
     G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
    
     if(volume != fScoringVolume) return; // volumul tinta trebuie sa fie cel specificat
    
    G4double edep = step->GetTotalEnergyDeposit(); //obt energia totala/step
    fEventAction->AddEdep(edep); // acumulare;

}
