#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH


#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4NistManager.hh"
#include "G4GenericMessenger.hh"
#include "G4Material.hh"
#include "G4MultiUnion.hh"

#include "detector.hh"

#include <iostream>

using namespace std;


class MyDetectorConstruction : public G4VUserDetectorConstruction {

public:
    MyDetectorConstruction();

    ~MyDetectorConstruction() override;

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    G4VPhysicalVolume *Construct() override;

    void ConstructSDandField() override; //for fileds and SD rep.


protected:

    G4bool checkOverlaps = true;

    G4LogicalVolume *fScoringVolume = nullptr,
            *logicWorld = nullptr,
            *logicEnv = nullptr,
            *logicRadiator = nullptr,
            *logicCu = nullptr,
            *logicGeUnion = nullptr,
            *logicBorUnion= nullptr,
            *logicInactiveGe= nullptr,
            *logicAlFoil= nullptr,
            *logicLi,
            *logicLiFill;

    G4Box *solidRadiator = nullptr,
            *solidWorld = nullptr,
            *solidEnv = nullptr;

    G4Tubs *solidCu = nullptr,
            *solidGe = nullptr,
            *solidGeFill = nullptr,
            *solidBor = nullptr,
            *solidBorFill= nullptr,
            *solidInactiveGe= nullptr,
            *solidAlFoil= nullptr,
            *solidLi,
            *solidLiFill;

    G4GenericMessenger *fMessenger;

    G4double env_sizeXY, env_sizeZ,
            world_sizeXY, world_sizeZ;


    G4Material *world_mat = nullptr,
            *env_mat = nullptr,
            *radiator_mat = nullptr;

    G4MultiUnion *solidGeUnion= nullptr,
                 *solidBorUnion= nullptr,
                 *solidLiUnion= nullptr;


    void DefineMaterials();

    void ResetRadiator(G4String, G4double);

    G4VPhysicalVolume *DefineVolumes();


};

#endif


