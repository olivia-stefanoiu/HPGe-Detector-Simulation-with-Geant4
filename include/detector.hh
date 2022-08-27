//clipul7
#ifndef DETECTOR_HH
#define DETECTOR_HH

//clip8
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

//clip7 - create a SD(fotosensor)
//header file

#include "G4VSensitiveDetector.hh"


class MySensitiveDetector : public G4VSensitiveDetector //class in G4
{

public:
   MySensitiveDetector(G4String);
   ~MySensitiveDetector()override;

private:
   G4bool ProcessHits(G4Step *, G4TouchableHistory *)override; //function for hits porcess
   
};

#endif


