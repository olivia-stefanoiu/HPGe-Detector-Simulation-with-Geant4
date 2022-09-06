#include "construction.hh"


MyDetectorConstruction::MyDetectorConstruction() {

    env_sizeXY = 0.3 * m;
    env_sizeZ = 0.5 * m;
    world_sizeXY = 1.2 * env_sizeXY;
    world_sizeZ = 1.2 * env_sizeZ;

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
    radiator_mat = nist->FindOrBuildMaterial("G4_Al");

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

    //
    //Radiator

    G4double plate_sizeXY = 10 * cm, plate_sizeZ = 1 * cm;

    solidRadiator =
            new G4Box("solidRadiator",                    //its name
                      0.5 * plate_sizeXY, 0.5 * plate_sizeXY, 0.5 * plate_sizeZ); //its size

    logicRadiator =
            new G4LogicalVolume(solidRadiator,            //its solid
                                radiator_mat,             //its material
                                "logicRadiator");         //its name

    new G4PVPlacement(0,                       //no rotation
                      G4ThreeVector(0, 0, 20 * cm),         //at (0,0,0)
                      logicRadiator,                //its logical volume
                      "physRadiator",              //its name
                      logicEnv,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking


    //Copper contact pin
    //
    solidCu =
            new G4Tubs("solidCu",
                       0*mm,
                       1.7*mm,
                       48.15*mm,
                       0.*deg,
                       360.*deg);
    logicCu =
            new G4LogicalVolume(solidCu,
                                nist->FindOrBuildMaterial("G4_Cu"),
                                "logicCu");
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,6.2*mm),
                      logicCu,
                      "physCu",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);

    //Germanium Crystal
    //
    solidGe =
            new G4Tubs("solidGe",
                       5.1*mm,
                       41.0*mm,
                       54.35*mm,
                       0.*deg,
                       360.*deg);
    /*
    logicGe =
            new G4LogicalVolume(solidGe,
                                nist->FindOrBuildMaterial("G4_Ge"),
                                "logicGe");

    new G4PVPlacement(0,
                      G4ThreeVector(),
                      logicGe,
                      "physGe",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);
    */
    solidGeFill =
            new G4Tubs("solidGeFill",
                       0,
                       5.1*mm,
                       6.2*mm,
                       0.*deg,
                       360.*deg);
    /*
    logicGeFill =
            new G4LogicalVolume(solidGeFill,
                                nist->FindOrBuildMaterial("G4_Ge"),
                                "logicGeFill");

    new G4PVPlacement(0,
                      G4ThreeVector(0*mm,0.*mm,-48.15*mm),
                      logicGeFill,
                      "physGeFill",
                      logicEnv,
                      false,
                      0,
                      checkOverlaps);
    */
    auto *solidGeUnion =
            new G4MultiUnion("solidGeUnion");
    G4ThreeVector pos = G4ThreeVector ();
    G4RotationMatrix rot=G4RotationMatrix ();
    G4Transform3D tr= G4Transform3D(rot,pos);
    solidGeUnion->AddNode(*solidGe,tr);

    G4ThreeVector pos_fill = G4ThreeVector (0,0,-48.15*mm);
    G4RotationMatrix rot_fill=G4RotationMatrix ();
    G4Transform3D tr_fill= G4Transform3D(rot_fill,pos_fill);
    solidGeUnion->AddNode(*solidGeFill,tr_fill);

    solidGeUnion->Voxelize();

    auto *logicGeUnion=
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

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    auto *sensDet = new MySensitiveDetector("SensitiveDetector");
    
    if(logicGe!= nullptr)
        logicGe->SetSensitiveDetector(sensDet);

}

