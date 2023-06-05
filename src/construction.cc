#include "construction.hh"


MyDetectorConstruction::MyDetectorConstruction() {

    env_sizeXY = 0.3 * m;
    env_sizeZ = 0.5 * m;
    world_sizeXY = 1.2 * env_sizeXY;
    world_sizeZ = 1.8 * env_sizeZ;

    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
    fMessenger->DeclareMethod("ResetRadiator",
                              &MyDetectorConstruction::ResetRadiator,
                              "Change Material and thickness of radiator");

}

MyDetectorConstruction::~MyDetectorConstruction() {
    delete fMessenger;
}


void MyDetectorConstruction::ResetRadiator(G4String newMat, G4double thickness) {

    G4NistManager *nist = G4NistManager::Instance();

    auto mat = nist->FindOrBuildMaterial(newMat);
    logicRadiator->SetMaterial(mat);
    solidRadiator->SetZHalfLength(0.5 * thickness * cm);
}


G4VPhysicalVolume *MyDetectorConstruction::Construct() {

    DefineMaterials();
    return DefineVolumes();
}

void MyDetectorConstruction::DefineMaterials() {

    G4NistManager *nist = G4NistManager::Instance();

    world_mat = nist->FindOrBuildMaterial("G4_AIR");
    env_mat = nist->FindOrBuildMaterial("G4_AIR");
    radiator_mat = nist->FindOrBuildMaterial("G4_Cu");

}


G4VPhysicalVolume *MyDetectorConstruction::DefineVolumes() {

    G4NistManager *nist = G4NistManager::Instance();


    // World
    //
    solidWorld =
            new G4Box("World",                       //its name
                      0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);     //its size

    logicWorld =
            new G4LogicalVolume(solidWorld,          //its solid
                                world_mat,           //its material
                                "World");            //its name

    G4VPhysicalVolume *physWorld =
            new G4PVPlacement(0,                     //no rotation
                              G4ThreeVector(),       //at (0,0,0)
                              logicWorld,            //its logical volume
                              "World",               //its name
                              0,                     //its mother  volume
                              false,                 //no boolean operation
                              0,                     //copy number
                              checkOverlaps);        //overlaps checking


    // Envelope
    //
    solidEnv =
            new G4Box("Envelope",                    //its name
                      0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ); //its size

    logicEnv =
            new G4LogicalVolume(solidEnv,            //its solid
                                env_mat,             //its material
                                "Envelope");         //its name

    new G4PVPlacement(0,                       //no rotation
                      G4ThreeVector(),         //at (0,0,0)
                      logicEnv,                //its logical volume
                      "Envelope",              //its name
                      logicWorld,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking

    // Radiator

    G4double plate_sizeXY = 100 * mm, plate_sizeZ = 15 * mm;

    solidRadiator =
            new G4Box("solidRadiator",                    //its name
                      0.5 * plate_sizeXY, 0.5 * plate_sizeXY, 0.5 * plate_sizeZ); //its size

    logicRadiator =
            new G4LogicalVolume(solidRadiator,            //its solid
                                radiator_mat,             //its material
                                "logicRadiator");         //its name

    new G4PVPlacement(0,                       //no rotation
                      G4ThreeVector(0, 0, 140-0.5*plate_sizeZ * mm),         //at (0,0,0)
                      logicRadiator,                //its logical volume
                      "physRadiator",              //its name
                      logicEnv,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking



/////////////////////////////////////////////////////////////////////////////////////////////PMT

    solidPMT = new G4Tubs("solidPMT",
                          0 * mm,
                          51 * mm,
                          66 * mm,
                          0. * deg,
                          360. * deg);

    logicPMT =
            new G4LogicalVolume(solidPMT,
                                nist->FindOrBuildMaterial("G4_Cs"),
                                "logicPMT");
    new G4PVPlacement(0,
                      G4ThreeVector(),
                      logicPMT,
                      "physPMT",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    ///BASE

    solidBase = new G4Tubs("solidBase",
                            0 * mm,
                            19.6 * mm,
                            10.89 * mm,
                            0. * deg,
                            360. * deg);

    logicBase =
            new G4LogicalVolume(solidBase,
                                nist->FindOrBuildMaterial("G4_Cs"),
                                "logicBase");
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,77.89*mm),
                      logicBase,
                      "physBase",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    ////Epoxy

    solidEpoxy = new G4Tubs("solidEpoxy",
                          0 * mm,
                          58.8 * mm,
                          0.5 * mm,
                          0. * deg,
                          360. * deg);

    logicEpoxy =
            new G4LogicalVolume(solidEpoxy,
                                nist->FindOrBuildMaterial("G4_Cs"),
                                "logicEpoxy");
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,66.5*mm),
                      logicEpoxy,
                      "physEpoxy",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    ///Silicone interface

    solidInter = new G4Tubs("solidInter",
                              0 * mm,
                              51 * mm,
                              1 * mm,
                              0. * deg,
                              360. * deg);

    logicInter =
            new G4LogicalVolume(solidInter,
                                nist->FindOrBuildMaterial("G4_Si"),
                                "logicInter");
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,-67*mm),
                      logicInter,
                      "physInter",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);


    ///Crystal

    solidCrystal = new G4Tubs("solidCrystal",
                            0 * mm,
                            51 * mm,
                            25.5 * mm,
                            0. * deg,
                            360. * deg);

    logicCrystal =
            new G4LogicalVolume(solidCrystal,
                                nist->FindOrBuildMaterial("G4_Na"),
                                "logicCrystal");
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,-92.5*mm),
                      logicCrystal,
                      "physCrystal",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    ///SUPORT

    solidSuport = new G4Tubs("solidSuport",
                            0 * mm,
                            6* mm,
                            1 * mm,
                            0. * deg,
                            360. * deg);

    logicSuport =
            new G4LogicalVolume(solidSuport,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicSuport");
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,68*mm),
                      logicSuport,
                      "physSuport",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    ///PINS and PinBase

    solidPin1 = new G4Tubs("solidPin1",
                             0 * mm,
                             2* mm,
                             7.5 * mm,
                             0. * deg,
                             360. * deg);

    solidPinBase1 = new G4Tubs("solidPinBase",
                              0 * mm,
                              6* mm,
                              1 * mm,
                              0. * deg,
                              360. * deg);


    logicPin1 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin1");
    new G4PVPlacement(0,
                      G4ThreeVector(0,-48*mm,75.5*mm),
                      logicPin1,
                      "physPin1",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase1 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPinBase1");
    new G4PVPlacement(0,
                      G4ThreeVector(0,-48*mm,68*mm),
                      logicPinBase1,
                      "physPinBase1",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);


    logicPin2 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin2");
    new G4PVPlacement(0,
                      G4ThreeVector(18.37*mm,-44.35*mm,75.5*mm),
                      logicPin2,
                      "physPin1",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase2 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPinBase2");
    new G4PVPlacement(0,
                      G4ThreeVector(18.37*mm,-44.35*mm,68*mm),
                      logicPinBase2,
                      "physPinBase2",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPin3 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin3");
    new G4PVPlacement(0,
                      G4ThreeVector(35.85*mm,-34.03*mm,75.5*mm),
                      logicPin3,
                      "physPin1",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase3 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPinBase3");
    new G4PVPlacement(0,
                      G4ThreeVector(35.85*mm,-34.03*mm,68*mm),
                      logicPinBase3,
                      "physPin1",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPin4 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin4");
    new G4PVPlacement(0,
                      G4ThreeVector(44.35*mm,-18.37*mm,75.5*mm),
                      logicPin4,
                      "physPin1",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase4 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin4");
    new G4PVPlacement(0,
                      G4ThreeVector(44.35*mm,-18.37*mm,68*mm),
                      logicPinBase4,
                      "physPin1",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPin5 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin5");
    new G4PVPlacement(0,
                      G4ThreeVector(48*mm,-0.13*mm,75.5*mm),
                      logicPin5,
                      "physPin5",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase5 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin5");
    new G4PVPlacement(0,
                      G4ThreeVector(48*mm,-0.13*mm,68*mm),
                      logicPinBase5,
                      "physPin5",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);


    logicPin6 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin6");
    new G4PVPlacement(0,
                      G4ThreeVector(44.35*mm,18.37*mm,75.5*mm),
                      logicPin6,
                      "physPin6",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase6 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin6");
    new G4PVPlacement(0,
                      G4ThreeVector(44.35*mm,18.37*mm,68*mm),
                      logicPinBase6,
                      "physPin6",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPin7 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin7");
    new G4PVPlacement(0,
                      G4ThreeVector(33.85*mm,34.03*mm,75.5*mm),
                      logicPin7,
                      "physPin7",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase7 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin7");
    new G4PVPlacement(0,
                      G4ThreeVector(33.85*mm,34.03*mm,68*mm),
                      logicPinBase7,
                      "physPin7",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPin8 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin8");
    new G4PVPlacement(0,
                      G4ThreeVector(18.37*mm,44.35*mm,75.5*mm),
                      logicPin8,
                      "physPin8",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase8 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin8");
    new G4PVPlacement(0,
                      G4ThreeVector(18.37*mm,44.35*mm,68*mm),
                      logicPinBase8,
                      "physPin8",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPin9 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin9");
    new G4PVPlacement(0,
                      G4ThreeVector(-0.13*mm,48*mm,75.5*mm),
                      logicPin9,
                      "physPin9",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase9 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin9");
    new G4PVPlacement(0,
                      G4ThreeVector(-0.13*mm,48*mm,68*mm),
                      logicPinBase9,
                      "physPin9",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPin10 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin10");
    new G4PVPlacement(0,
                      G4ThreeVector(-18.37*mm,44.35*mm,75.5*mm),
                      logicPin10,
                      "physPin10",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase10 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin10");
    new G4PVPlacement(0,
                      G4ThreeVector(-18.37*mm,44.35*mm,68*mm),
                      logicPinBase10,
                      "physPin10",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);


    logicPin11 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin11");
    new G4PVPlacement(0,
                      G4ThreeVector(-33.85*mm,34.03*mm,75.5*mm),
                      logicPin11,
                      "physPin11",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase11 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin11");
    new G4PVPlacement(0,
                      G4ThreeVector(-33.85*mm,34.03*mm,68*mm),
                      logicPinBase11,
                      "physPin11",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);


    logicPin12 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin12");
    new G4PVPlacement(0,
                      G4ThreeVector(-44.35*mm,18.37*mm,75.5*mm),
                      logicPin12,
                      "physPin12",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase12 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin12");
    new G4PVPlacement(0,
                      G4ThreeVector(-44.35*mm,18.37*mm,68*mm),
                      logicPinBase12,
                      "physPin12",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPin13 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin13");
    new G4PVPlacement(0,
                      G4ThreeVector(-48*mm,0.13*mm,75.5*mm),
                      logicPin13,
                      "physPin13",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase13 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin13");
    new G4PVPlacement(0,
                      G4ThreeVector(-48*mm,0.13*mm,68*mm),
                      logicPinBase13,
                      "physPin13",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPin14 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin14");
    new G4PVPlacement(0,
                      G4ThreeVector(-44.35*mm,-18.37*mm,75.5*mm),
                      logicPin14,
                      "physPin14",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase14 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin14");
    new G4PVPlacement(0,
                      G4ThreeVector(-44.35*mm,-18.37*mm,68*mm),
                      logicPinBase14,
                      "physPin14",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPin15 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin15");
    new G4PVPlacement(0,
                      G4ThreeVector(-33.85*mm,-34.03*mm,75.5*mm),
                      logicPin15,
                      "physPin15",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase15 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin15");
    new G4PVPlacement(0,
                      G4ThreeVector(-33.85*mm,-34.03*mm,68*mm),
                      logicPinBase15,
                      "physPin15",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPin16 =
            new G4LogicalVolume(solidPin1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin16");
    new G4PVPlacement(0,
                      G4ThreeVector(-18.37*mm,-44.35,75.5*mm),
                      logicPin16,
                      "physPin16",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    logicPinBase16 =
            new G4LogicalVolume(solidPinBase1,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicPin16");
    new G4PVPlacement(0,
                      G4ThreeVector(-18.37*mm,-44.35,68*mm),
                      logicPinBase16,
                      "physPin16",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

/////Reflector

    solidReflector = new G4Tubs("Reflector",
                             52 * mm,
                             56.2* mm,
                             92.5 * mm,
                             0. * deg,
                             360. * deg);

    logicReflector =
            new G4LogicalVolume(solidReflector,
                                nist->FindOrBuildMaterial("G4_Pb"),
                                "logicReflector");
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,-26.5*mm),
                      logicReflector,
                      "physReflector",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    solidReflectorCap = new G4Tubs("ReflectorCap",
                                0 * mm,
                                51* mm,
                                1.3* mm,
                                0. * deg,
                                360. * deg);

    logicReflectorCap =
            new G4LogicalVolume(solidReflectorCap,
                                nist->FindOrBuildMaterial("G4_Pb"),
                                "logicReflector");
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,-118.3*mm),
                      logicReflectorCap,
                      "physReflector",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    ////Aluminum

    solidAl = new G4Tubs("Aluminum",
                                56.2 * mm,
                                57* mm,
                                30 * mm,
                                0. * deg,
                                360. * deg);

    logicAl =
            new G4LogicalVolume(solidAl,
                                nist->FindOrBuildMaterial("G4_Al"),
                                "logicReflector");
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,-89*mm),
                      logicAl,
                      "physReflector",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

   ////EpoxySeal

    solidEpoxySeal = new G4Tubs("EpoxySeal",
                         57 * mm,
                         58* mm,
                         71.25 * mm,
                         0. * deg,
                         360. * deg);

    logicEpoxySeal =
            new G4LogicalVolume(solidEpoxySeal,
                                nist->FindOrBuildMaterial("G4_Cs"),
                                "logicReflector");
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,-5.25*mm),
                      logicEpoxySeal,
                      "physEpoxySeal",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    ////Magnetic

    solidMagnetic = new G4Tubs("Magnetic",
                                58 * mm,
                                58.8* mm,
                                71.25 * mm,
                                0. * deg,
                                360. * deg);

    logicMagnetic =
            new G4LogicalVolume(solidMagnetic,
                                nist->FindOrBuildMaterial("G4_Ni"),
                                "logicMagnetic");
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,-5.25*mm),
                      logicMagnetic,
                      "physMagnetic",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);


    fScoringVolume=logicCrystal;

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
    auto *sensDet = new MySensitiveDetector("logicCrystal");

    //if(logicGeUnion != nullptr)
    // fScoringVolume=logicGeUnion;
    logicCrystal->SetSensitiveDetector(sensDet);

}

