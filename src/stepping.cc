#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
:fEventAction(eventAction){}


MySteppingAction::~MySteppingAction(){}


void MySteppingAction::UserSteppingAction(const G4Step *step)
{                                                                                                                
     G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
     const auto *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    
     G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
    
     if(volume != fScoringVolume) return;
    
    G4double eDep = step->GetTotalEnergyDeposit();
    if(eDep>0.) fEventAction->AddEdep(eDep);


}
