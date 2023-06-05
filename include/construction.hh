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
            *logicBorUnion = nullptr,
            *logicInactiveGe = nullptr,
            *logicAlFoil = nullptr,
            *logicLiUnion = nullptr,
            *logicAlCapUnion,
            *logicAlCupUnion;

    G4Box *solidRadiator = nullptr,
            *solidWorld = nullptr,
            *solidEnv = nullptr;

    G4Tubs
            *solidCu = nullptr,
            *solidGe = nullptr,
            *solidGeFill = nullptr,
            *solidBor = nullptr,
            *solidBorFill = nullptr,
            *solidInactiveGe = nullptr,
            *solidAlFoil = nullptr,
            *solidLi = nullptr,
            *solidLiFill = nullptr,
            *solidAlCap,
            *solidAlCapFill,
            *solidAlCupFill,
            *solidAlCup;

    G4GenericMessenger *fMessenger;

    G4double env_sizeXY, env_sizeZ,
            world_sizeXY, world_sizeZ;


    G4Material
            *world_mat = nullptr,
            *env_mat = nullptr,
            *radiator_mat = nullptr;

    G4MultiUnion
            *solidGeUnion = nullptr,
            *solidBorUnion = nullptr,
            *solidLiUnion = nullptr,
            *solidAlCapUnion,
            *solidAlCupUnion;

    G4Tubs *solidPMT = nullptr,
            *solidEpoxy = nullptr,
            *solidBase = nullptr,
            *solidInter = nullptr,
            *solidCrystal = nullptr,
            *solidSuport = nullptr,
            *solidPin1 = nullptr,
            *solidPinBase1 = nullptr,
            *solidReflector = nullptr,
            *solidAl = nullptr,
            *solidEpoxySeal = nullptr,
            *solidMagnetic = nullptr,
            *solidReflectorCap = nullptr;



    G4LogicalVolume *logicPMT = nullptr,
            *logicEpoxy = nullptr,
            *logicBase = nullptr,
            *logicInter = nullptr,
            *logicCrystal = nullptr,
            *logicSuport = nullptr,
            *logicPin1 = nullptr,
            *logicPin2 = nullptr,
            *logicPin3 = nullptr,
            *logicPin4 = nullptr,
            *logicPin5 = nullptr,
            *logicPin6 = nullptr,
            *logicPin7 = nullptr,
            *logicPin8 = nullptr,
            *logicPin9 = nullptr,
            *logicPin10= nullptr,
            *logicPin11 = nullptr,
            *logicPin12 = nullptr,
            *logicPin13 = nullptr,
            *logicPin14= nullptr,
            *logicPin15= nullptr,
            *logicPin16= nullptr,
            *logicPinBase1 = nullptr,
            *logicPinBase2 = nullptr,
            *logicPinBase3 = nullptr,
            *logicPinBase4 = nullptr,
            *logicPinBase5 = nullptr,
            *logicPinBase6 = nullptr,
            *logicPinBase7 = nullptr,
            *logicPinBase8 = nullptr,
            *logicPinBase9 = nullptr,
            *logicPinBase10= nullptr,
            *logicPinBase11 = nullptr,
            *logicPinBase12 = nullptr,
            *logicPinBase13 = nullptr,
            *logicPinBase14= nullptr,
            *logicPinBase15= nullptr,
            *logicPinBase16= nullptr,
            *logicReflector = nullptr,
            *logicAl = nullptr,
            *logicEpoxySeal = nullptr,
            *logicMagnetic,
            *logicReflectorCap = nullptr;


    void DefineMaterials();

    void ResetRadiator(G4String, G4double);

    G4VPhysicalVolume *DefineVolumes();


};

#endif


