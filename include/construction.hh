#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

//Clipul3_ Detector Construction
#include "G4VUserDetectorConstruction.hh"

#include "G4SystemOfUnits.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4Trd.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"

#include "G4NistManager.hh"
#include "G4GenericMessenger.hh"

#include <map>

//Clipul3_ Detector Construction
//clasa

//clip7
#include "detector.hh"

#include <iostream>

using namespace std;


class MyDetectorConstruction : public G4VUserDetectorConstruction {

public:
    MyDetectorConstruction();  //constructor
    ~MyDetectorConstruction() override; //destructor

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    G4VPhysicalVolume *Construct() override; //fct care cosntruieste detectorul
    void ConstructSDandField() override; //for fileds and SD rep.

    //clipul7
private:

    G4Tubs *solidBor, *solidBorPlate,
            *solidDetector,
            *solidAl, *solidAlPlate, *solidAlTick, *solidAlTickPlate,
            *solidLiPlate,
            *solidGePlate, *solidLi;

    G4Box *solidWorld, *solidEnv, *solidRadiator;

    G4LogicalVolume *fScoringVolume;//pentru volumul tinta;

    G4LogicalVolume *logicDetector, *logicEnv, *logicWorld, *logicRadiator,
            *logicBor, *logicBorPlate,
            *logicGePlate,
            *logicLi, *logicLiPlate,
            *logicAl, *logicAlPlate, *logicAlTick, *logicAlTickPlate;

    G4VPhysicalVolume *physWorld, *physDetector, *physEnv, *physRadiator,
            *physBor, *physBorPlate,
            *physGePlate,
            *physLi, *physLiPlate,
            *physAl, *physAlPlate, *physAlTick, *physAlTickPlate;

    G4Material *env_mat, *world_mat, *radiator_mat,
            *component2_mat, *component3_mat, *component4_mat, *component5_mat,
            *component6_mat, *component7_mat, *component8_mat,
            *component9_mat, *component10_mat, *component11_mat;

    G4GenericMessenger *fMessenger;

    G4double env_sizeX, env_sizeY, env_sizeZ,
             world_sizeX, world_sizeY, world_sizeZ,
             rad_sizeX,rad_sizeY,rad_sizeZ;

    map<G4String, G4LogicalVolume *> logicalVolumeMap;


    void DefineMaterials(); //a new function for materials
    G4VPhysicalVolume *DefineVolumes();

    void ResetMaterials(G4String, G4String);
    void ResetRadiator(G4String,G4double);

    G4bool checkOverlaps = true;

};

#endif

//Clipul3_ Detector Construction
