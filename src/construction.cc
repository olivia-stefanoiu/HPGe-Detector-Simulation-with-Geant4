#include "construction.hh"


MyDetectorConstruction::MyDetectorConstruction() {

    env_sizeXY = 0.3 * m;
    env_sizeZ = 0.5 * m;
    world_sizeXY = 1.2 * env_sizeXY;
    world_sizeZ = 1.2 * env_sizeZ;

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
    radiator_mat = nist->FindOrBuildMaterial("G4_Fe");

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


/////////////////////////////////////////////////////////////////////////////////////////////PMT
//
//    solidPMT = new G4Tubs("solidPMT",
//                          0 * mm,
//                          51 * mm,
//                          66 * mm,
//                          0. * deg,
//                          360. * deg);
//
//    logicPMT =
//            new G4LogicalVolume(solidPMT,
//                                nist->FindOrBuildMaterial("G4_Cs"),
//                                "logicPMT");
//    new G4PVPlacement(0,
//                      G4ThreeVector(),
//                      logicPMT,
//                      "physPMT",
//                      logicEnv,
//                      false,
//                      0,
//                      checkOverlaps);

    //EPOXY

//    solidEpoxy = new G4Tubs("solidEpoxy",
//                          0 * mm,
//                          58.8 * mm,
//                          0.5 * mm,
//                          0. * deg,
//                          360. * deg);
//
//    logicEpoxy =
//            new G4LogicalVolume(solidPMT,
//                                nist->FindOrBuildMaterial("G4_Cs"),
//                                "logicPMT");
//    new G4PVPlacement(0,
//                      G4ThreeVector(0,0,100.5*mm),
//                      logicEpoxy,
//                      "physEpoxy",
//                      logicEnv,
//                      false,
//                      0,
//                      checkOverlaps);
//
//
//


    // Radiator

    G4double plate_sizeXY = 100 * mm, plate_sizeZ = 0.5 * mm;

    solidRadiator =
            new G4Box("solidRadiator",                    //its name
                      0.5 * plate_sizeXY, 0.5 * plate_sizeXY, 0.5 * plate_sizeZ); //its size

    logicRadiator =
            new G4LogicalVolume(solidRadiator,            //its solid
                                radiator_mat,             //its material
                                "logicRadiator");         //its name

    new G4PVPlacement(0,                       //no rotation
                      G4ThreeVector(0, 0, (93.15-plate_sizeZ*0.5)* mm),         //at (0,0,0)
                      logicRadiator,                //its logical volume
                      "physRadiator",              //its name
                      logicEnv,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking


    //Copper contact pin

    solidCu =
            new G4Tubs("solidCu",
                       0 * mm,
                       1.7 * mm,
                       48.15 * mm,
                       0. * deg,
                       360. * deg);
    logicCu =
            new G4LogicalVolume(solidCu,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicCu");
    new G4PVPlacement(0,
                      G4ThreeVector(),
                      logicCu,
                      "physCu",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    //Boron Contact
    //
    solidBor =
            new G4Tubs("solidBor",
                       5.0997 * mm,
                       5.1 * mm,
                       48.15 * mm,
                       0. * deg,
                       360. * deg);

    solidBorFill =
            new G4Tubs("solidBorFill",
                       0,
                       5.1 * mm,
                       0.00015,
                       0 * deg,
                       360 * deg);

    solidBorUnion =
            new G4MultiUnion("solidBorUnion");
    G4ThreeVector pos_Bor = G4ThreeVector(0, 0, 0);
    G4RotationMatrix rot_Bor = G4RotationMatrix();
    G4Transform3D trBor = G4Transform3D(rot_Bor, pos_Bor);
    solidBorUnion->AddNode(*solidBor, trBor);

    G4ThreeVector pos_BorFill = G4ThreeVector(0, 0, -48.15015* mm);
    G4RotationMatrix rot_BorFill = G4RotationMatrix();
    G4Transform3D tr_BorFill = G4Transform3D(rot_BorFill, pos_BorFill);
    solidBorUnion->AddNode(*solidBorFill, tr_BorFill);

    solidBorUnion->Voxelize();

    logicBorUnion =
            new G4LogicalVolume(solidBorUnion,
                                nist->FindOrBuildMaterial("G4_B"),
                                "logicBorUnion");
    new G4PVPlacement(0,
                      G4ThreeVector(),
                      logicBorUnion,
                      "physBorUnion",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    //Germanium Crystal
    //

    solidGe =
            new G4Tubs("solidGe",
                       5.1 * mm,
                       41.0 * mm,
                       48.15 * mm,
                       0. * deg,
                       360. * deg);

    solidGeFill =
            new G4Tubs("solidGeFill",
                       0,
                       41. * mm,
                       5.2 * mm,
                       0. * deg,
                       360. * deg);

    solidGeUnion =
            new G4MultiUnion("solidGeUnion");
    G4ThreeVector pos_Ge = G4ThreeVector();
    G4RotationMatrix rot_Ge = G4RotationMatrix();
    G4Transform3D tr_Ge = G4Transform3D(rot_Ge, pos_Ge);
    solidGeUnion->AddNode(*solidGe, tr_Ge);

    G4ThreeVector pos_GeFill = G4ThreeVector(0, 0,-53.35 * mm);//fill sunt partile de care am nevoie pentru figurii custom
    G4RotationMatrix rot_GeFill = G4RotationMatrix();
    G4Transform3D tr_GeFill = G4Transform3D(rot_GeFill, pos_GeFill);
    solidGeUnion->AddNode(*solidGeFill, tr_GeFill);

    solidGeUnion->Voxelize();

    logicGeUnion =
            new G4LogicalVolume(solidGeUnion,
                                nist->FindOrBuildMaterial("G4_Ge"),
                                "logicGeUnion");
    new G4PVPlacement(0,
                      G4ThreeVector(),
                      logicGeUnion,
                      "physGeUnion",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);


    solidInactiveGe =
            new G4Tubs("solidInactiveGe",
                       0,
                       41. * mm,
                       1. * mm,
                       0 * deg,
                       360. * deg);

    logicInactiveGe =
            new G4LogicalVolume(solidInactiveGe,
                                nist->FindOrBuildMaterial("G4_Ge"),
                                "logicInactiveGe");
    new G4PVPlacement(0,
                      G4ThreeVector(0, 0, -59.55 * mm),
                      logicInactiveGe,
                      "physInactiveGe",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);


    //Li
    //
    solidLi =
            new G4Tubs("solidLi",
                       41. * mm,
                       41.7 * mm,
                       54.7 * mm,
                       0 * deg,
                       360 * deg);


    solidLiFill =
            new G4Tubs("solidLiFill",
                       0,
                       41.7*mm,
                       0.35*mm,
                       0*deg,
                       360*deg);

    solidLiUnion =
            new G4MultiUnion("solidLiUnion");
    G4ThreeVector pos_Li = G4ThreeVector(0, 0, -6.5625*mm);
    G4RotationMatrix rot_Li = G4RotationMatrix();
    G4Transform3D trLi = G4Transform3D(rot_Li, pos_Li);
    solidLiUnion->AddNode(*solidLi, trLi);

    G4ThreeVector pos_LiFill = G4ThreeVector(0, 0, -60.9* mm);
    G4RotationMatrix rot_LiFill = G4RotationMatrix();
    G4Transform3D tr_LiFill = G4Transform3D(rot_LiFill, pos_LiFill);
    solidLiUnion->AddNode(*solidLiFill, tr_LiFill);

    solidLiUnion->Voxelize();

    logicLiUnion =
            new G4LogicalVolume(solidLiUnion,
                                nist->FindOrBuildMaterial("G4_Li"),
                                "logicLiUnion");


    new G4PVPlacement(0,
                      G4ThreeVector(),
                      logicLiUnion,
                      "physLiUnion",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    //AlFoil
    //

    solidAlFoil =
            new G4Tubs("solidAlFoil",
                       0,
                       41.7*mm,
                       0.0125*mm,
                       0*deg,
                       360*deg);

    logicAlFoil =
            new G4LogicalVolume(solidAlFoil,
                                nist->FindOrBuildMaterial("G4_Al"),
                                "logicAlFoil");


    new G4PVPlacement(0,
                      G4ThreeVector(0,0,-61.2625*mm),
                      logicAlFoil,
                      "physAlFoil",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);
    //AlCup


    solidAlCupFill =
            new G4Tubs("solidAlCupFill",
                       0,
                       42.2*mm,
                       0.25*mm,
                       0*deg,
                       360*deg);

    solidAlCup =
            new G4Tubs("solidAlCup",
                       41.7*mm,
                       42.2*mm,
                       54.9625*mm,
                       0*deg,
                       360*deg);

    solidAlCupUnion =
            new G4MultiUnion("solidAlCupUnion");
    G4ThreeVector pos_AlCup = G4ThreeVector(0, 0, -6.8125*mm);
    G4RotationMatrix rot_AlCup = G4RotationMatrix();
    G4Transform3D trAlCup = G4Transform3D(rot_AlCup, pos_AlCup);
    solidAlCupUnion->AddNode(*solidAlCup, trAlCup);


    G4ThreeVector pos_AlCupFill = G4ThreeVector(0, 0, -61.525* mm);
    G4RotationMatrix rot_AlCupFill = G4RotationMatrix();
    G4Transform3D tr_AlCupFill = G4Transform3D(rot_AlCupFill, pos_AlCupFill);
    solidAlCupUnion->AddNode(*solidAlCupFill, tr_AlCupFill);

    solidAlCupUnion->Voxelize();

    logicAlCupUnion =
            new G4LogicalVolume(solidAlCupUnion,
                                nist->FindOrBuildMaterial("G4_Al"),
                                "logicAlCupUnion");
    new G4PVPlacement(0,
                      G4ThreeVector(),
                      logicAlCupUnion,
                      "physAlCupUnion",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);


    //Alluminum cap
    //
    solidAlCap =
            new G4Tubs("solidAlCap",
                       46.2*mm,
                       47.2*mm,
                       57.4625*mm,
                       0*deg,
                       360*deg);

    solidAlCapFill =
            new G4Tubs("solidAlCapFill",
                       0,
                       47.2*mm,
                       0.5*mm,
                       0*deg,
                       360*deg);

    solidAlCapUnion =
            new G4MultiUnion("solidAlCapUnion");

    G4ThreeVector pos_AlCap = G4ThreeVector(0, 0,  -9.3125 * mm);
    G4RotationMatrix rot_AlCap = G4RotationMatrix();
    G4Transform3D tr_AlCap = G4Transform3D(rot_AlCap, pos_AlCap);
    solidAlCapUnion->AddNode(*solidAlCap, tr_AlCap);

    G4ThreeVector pos_AlCapFill = G4ThreeVector(0, 0, -66.275 * mm);
    G4RotationMatrix rot_AlCapFill = G4RotationMatrix();
    G4Transform3D tr_AlCapFill = G4Transform3D(rot_AlCapFill, pos_AlCapFill);
    solidAlCapUnion->AddNode(*solidAlCapFill, tr_AlCapFill);

    solidAlCapUnion->Voxelize();

    logicAlCapUnion =
            new G4LogicalVolume(solidAlCapUnion,
                                nist->FindOrBuildMaterial("G4_Al"),
                                "logicAlCapUnion");

    new G4PVPlacement(0,
                      G4ThreeVector(),
                      logicAlCapUnion,
                      "physAlCapUnion",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    fScoringVolume=logicGeUnion;



    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
    auto *sensDet = new MySensitiveDetector("logicGeUnion");

    //if(logicGeUnion != nullptr)
    // fScoringVolume=logicGeUnion;
    logicGeUnion->SetSensitiveDetector(sensDet);

}

