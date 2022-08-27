#include "construction.hh"


MyDetectorConstruction::MyDetectorConstruction() {

    logicalVolumeMap = map<G4String, G4LogicalVolume *>();

    G4cout << logicalVolumeMap["logicWorld"]
           << "))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))";
    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
    fMessenger->DeclareMethod("changeMat", &MyDetectorConstruction::ResetMaterials,
                              "Change Material of detector component");
    fMessenger->DeclareMethod("changeRad", &MyDetectorConstruction::ResetRadiator,
                              "Change Material and thickness of coliamteur");

    env_sizeX = 30 * cm;
    env_sizeY = 30 * cm;
    env_sizeZ = 30 * cm;

    world_sizeX = 40 * cm;
    world_sizeY = 40 * cm;
    world_sizeZ = 40 * cm;

    rad_sizeX = 29 * cm;
    rad_sizeY = 29 * cm;
    rad_sizeZ = 0.5 * cm;

    //DefineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction() {
    delete fMessenger;
}

void MyDetectorConstruction::ResetMaterials(G4String volume, G4String newMat) {


    G4NistManager *nist = G4NistManager::Instance();
    auto vol = this->logicalVolumeMap.find(volume);

    if (vol != this->logicalVolumeMap.end()) {
        auto mat = nist->FindOrBuildMaterial(newMat);
        vol->second->SetMaterial(mat);
    }

}

void MyDetectorConstruction::ResetRadiator(G4String newMat, G4double thickness) {

    G4NistManager *nist = G4NistManager::Instance();

    auto mat = nist->FindOrBuildMaterial(newMat);
    logicRadiator->SetMaterial(mat);
    solidRadiator->SetZHalfLength(thickness);
}


G4VPhysicalVolume *MyDetectorConstruction::Construct() {

    DefineMaterials();
    return DefineVolumes();
}

void MyDetectorConstruction::DefineMaterials() {
    G4NistManager *nist = G4NistManager::Instance();

    component2_mat = nist->FindOrBuildMaterial("G4_B"); //select a material
    component3_mat = nist->FindOrBuildMaterial("G4_B");

    component4_mat = nist->FindOrBuildMaterial("G4_Ge");
    component5_mat = nist->FindOrBuildMaterial("G4_Ge");

    component6_mat = nist->FindOrBuildMaterial("G4_Li");
    component7_mat = nist->FindOrBuildMaterial("G4_Li");

    component8_mat = nist->FindOrBuildMaterial("G4_Al");
    component9_mat = nist->FindOrBuildMaterial("G4_Al");
    component10_mat = nist->FindOrBuildMaterial("G4_Al");
    component11_mat = nist->FindOrBuildMaterial("G4_Al");

    world_mat = nist->FindOrBuildMaterial("G4_AIR"); //world material
    env_mat = nist->FindOrBuildMaterial("G4_AIR");

    radiator_mat = nist->FindOrBuildMaterial("G4_Al");


}


G4VPhysicalVolume *MyDetectorConstruction::DefineVolumes() {


    solidRadiator = new G4Box("solidRadiator",
                              rad_sizeX, rad_sizeY, rad_sizeZ);

    logicRadiator = new G4LogicalVolume(solidRadiator,
                                        radiator_mat,
                                        "logicRadiator");

    physRadiator = new G4PVPlacement(0,
                                     G4ThreeVector(0., 0., -20 * cm),
                                     logicRadiator,
                                     "physRadiator",
                                     logicWorld,
                                     false,
                                     0,
                                     true);


    solidWorld = new G4Box("World",
                           world_sizeX, world_sizeY, world_sizeZ);

    logicWorld = new G4LogicalVolume(solidWorld,
                                     world_mat,
                                     "World");            //its name

    physWorld = new G4PVPlacement(0,                     //no rotation
                                  G4ThreeVector(),       //at (0,0,0)
                                  logicWorld,            //its logical volume
                                  "World",               //its name
                                  0,                     //its mother  volume
                                  false,                 //no boolean operation
                                  0,                     //copy number
                                  true);                 //overlaps checking


    solidEnv = new G4Box("Envelope",                    //its name
                         env_sizeX, env_sizeY, env_sizeZ); //its size

    logicEnv = new G4LogicalVolume(solidEnv,            //its solid
                                   env_mat,             //its material
                                   "Envelope");         //its name

    //  fScoringVolume = logicEnv;

    physEnv = new G4PVPlacement(0,                       //no rotation
                                G4ThreeVector(),         //at (0,0,0)
                                logicEnv,                //its logical volume
                                "Envelope",              //its name
                                logicWorld,              //its mother  volume
                                false,                   //no boolean operation
                                0,                       //copy number
                                checkOverlaps);          //overlaps checking


    // component 2- Boron Contact layer

    solidBor = new G4Tubs("solidBor", // name
                          5.1 * mm, // inner radius (0)
                          5.1003 * mm, // outer radius
                          48.15 * mm, // Z half! length
                          0. * deg, // starting Phi (0)
                          360. * deg); // segment angle (twopi)

    logicBor = new G4LogicalVolume(solidBor,    //its solid
                                   component2_mat,  //its material
                                   "logicBor"); //its name(logic)

    physBor = new G4PVPlacement(0,
                                G4ThreeVector(0, 0, 0),                         //position vector
                                logicBor,              //its logical volume
                                "physBor",                  //its name
                                logicEnv,                     //its mother volume
                                false,                        //no boolean operation
                                0,                            //copy number
                                checkOverlaps);               //verifica suprapunerile(de evitat)


    //for Boron plate(top) - component3

    solidBorPlate = new G4Tubs("solidBorPlate", // name
                               0. * mm, // inner radius (0)
                               5.1003 * mm, // outer radius
                               0.0003 * mm, // Z half! length
                               0. * deg, // starting Phi (0)
                               360. * deg); // segment angle (twopi)

    logicBorPlate = new G4LogicalVolume(solidBorPlate,    //its solid
                                        component3_mat,  //its material
                                        "logicBorPlate"); //its name(logic)

    //if(logicDetector != NULL)
    //logicDetector->SetSensitiveDetector(sensDet);

    physBorPlate = new G4PVPlacement(0,
                                     G4ThreeVector(0, 0, 48.15015),  //position vector
                                     logicBorPlate,              //its logical volume
                                     "physBorplate",               //its name
                                     logicEnv,                     //its mother volume
                                     false,                        //no boolean operation
                                     0,                            //copy number
                                     checkOverlaps);               //verifica suprapunerile(de evitat)

    //llllllllllllllllllllllllllllllllllllllllll_SECTION 3_(Ge)lllllllllllllllllllllllllllllllllllllllllll


    solidDetector = new G4Tubs("solidDetector", // name(detectorul principal)
                               5.1004 * mm, // inner radius (0)
                               41. * mm, // outer radius
                               48.15016 * mm, // Z half! length
                               0. * deg, // starting Phi (0)
                               360. * deg); // segment angle (twopi)


    logicDetector = new G4LogicalVolume(solidDetector,    //its solid
                                        component4_mat,  //its material
                                        "logicDetector"); //its name(logic)

    fScoringVolume = logicDetector; // ................................................................................................Vol tinta.


    physDetector = new G4PVPlacement(0,
                                     G4ThreeVector(0, 0, 0.00015),  //position vector
                                     logicDetector,              //its logical volume
                                     "physDetector",                  //its name
                                     logicEnv,                     //its mother volume
                                     false,                        //no boolean operation
                                     0,                            //copy number
                                     checkOverlaps);               //verifica suprapunerile(de evitat)

    // component 5- GePlateTop

    solidGePlate = new G4Tubs("solidGePlate", // name
                              0. * mm, // inner radius (0)
                              41. * mm, // outer radius
                              6.2 * mm, // Z half! length
                              0. * deg, // starting Phi (0)
                              360. * deg); // segment angle (twopi)

    logicGePlate = new G4LogicalVolume(solidGePlate,    //its solid
                                       component5_mat,  //its material
                                       "logicGePlate"); //its name(logic)
    // fScoringVolume = logicGePlate;

    physGePlate = new G4PVPlacement(0,
                                    G4ThreeVector(0, 0, 55.),  //position vector
                                    logicGePlate,              //its logical volume
                                    "physGePlate",                  //its name
                                    logicEnv,                     //its mother volume
                                    false,                        //no boolean operation
                                    0,                            //copy number
                                    checkOverlaps);               //verifica suprapunerile(de evitat)


    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa_SECTION 4(Li)aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

    // component 6- Li contact zone- layer

    solidLi = new G4Tubs("solidLi", // name
                         41.1 * mm, // inner radius (0)
                         41.8 * mm, // outer radius
                         61.2 * mm, // Z half! length
                         0. * deg, // starting Phi (0)
                         360. * deg); // segment angle (twopi)

    logicLi = new G4LogicalVolume(solidLi,      //its solid
                                  component6_mat,  //its material
                                  "logicLi");  //its name(logic)

    physLi = new G4PVPlacement(0,
                               G4ThreeVector(0, 0, 0),  //position vector
                               logicLi,              //its logical volume
                               "physLi",                  //its name
                               logicEnv,                     //its mother volume
                               false,                        //no boolean operation
                               0,                            //copy number
                               checkOverlaps);               //verifica suprapunerile(de evitat)

    //Li plate TOP - 2

    solidLiPlate = new G4Tubs("solidLiplate", // name
                              0 * mm, // inner radius (0)
                              41.8 * mm, // outer radius
                              0.35 * mm, // Z half! length
                              0. * deg, // starting Phi (0)
                              360. * deg); // segment angle (twopi)

    logicLiPlate = new G4LogicalVolume(solidLiPlate,      //its solid
                                       component7_mat,  //its material
                                       "logicLiplate");  //its name(logic)

    physLiPlate = new G4PVPlacement(0,
                                    G4ThreeVector(0, 0, 70),  //position vector
                                    logicLiPlate,              //its logical volume
                                    "physLiplate",                  //its name
                                    logicEnv,                     //its mother volume
                                    false,                        //no boolean operation
                                    0,                            //copy number
                                    checkOverlaps);               //verifica suprapunerile(de evitat)


    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa_SECTION 5(Al)aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

    // component 8- Al foil contact zone- layer2

    solidAl = new G4Tubs("solidAl", // name
                         41.9 * mm, // inner radius (0)
                         42.4 * mm, // outer radius
                         62.5 * mm, // Z half! length
                         0. * deg, // starting Phi (0)
                         360. * deg); // segment angle (twopi)


    logicAl = new G4LogicalVolume(solidAl,      //its solid
                                  component8_mat,  //its material
                                  "logicAl");  //its name(logic)

    physAl = new G4PVPlacement(0,
                               G4ThreeVector(0, 0, 0),  //position vector
                               logicAl,              //its logical volume
                               "physAl",                  //its name
                               logicEnv,                     //its mother volume
                               false,                        //no boolean operation
                               0,                            //copy number
                               checkOverlaps);               //verifica suprapunerile(de evitat)


    //Al plate foil TOP - component9

    solidAlPlate = new G4Tubs("solidAlPlate", // name
                              0 * mm, // inner radius (0)
                              41.9 * mm, // outer radius
                              0.5 * mm, // Z half! length
                              0. * deg, // starting Phi (0)
                              360. * deg); // segment angle (twopi)

    logicAlPlate = new G4LogicalVolume(solidAlPlate,      //its solid
                                       component9_mat,  //its material
                                       "logicAlPlate");  //its name(logic)

    physAlPlate = new G4PVPlacement(0,
                                    G4ThreeVector(0, 0, 63.),  //position vector
                                    logicAlPlate,              //its logical volume
                                    "physAlPlate",                  //its name
                                    logicEnv,                     //its mother volume
                                    false,                        //no boolean operation
                                    0,                            //copy number
                                    checkOverlaps);               //verifica suprapunerile(de evitat)


    //kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk

    //component10 - exterior Al_tick

    solidAlTick = new G4Tubs("solidAlTick",
                             45. * mm, // inner radius (0)
                             46. * mm, // outer radius
                             67 * mm, // Z half! length
                             0. * deg, // starting Phi (0)
                             360. * deg); // segment angle (twopi)


    logicAlTick = new G4LogicalVolume(solidAlTick,
                                      component10_mat,
                                      "logicAltick");

    physAlTick = new G4PVPlacement(0,
                                   G4ThreeVector(0, 0, 4. * mm),  //position vector
                                   logicAlTick,              //its logical volume
                                   "physAlTick",                  //its name
                                   logicEnv,                     //its mother volume
                                   false,                        //no boolean operation
                                   0,                            //copy number
                                   checkOverlaps);               //verifica suprapunerile(de evitat)


    //component11 - exterior Al_tick plate


    solidAlTickPlate = new G4Tubs("solidAlTickPlate", // name
                                  0, // inner radius (0)
                                  46. * mm, // outer radius
                                  0.5 * mm, // Z half! length
                                  0. * deg, // starting Phi (0)
                                  360. * deg); // segment angle (twopi)


    logicAlTickPlate = new G4LogicalVolume(solidAlTickPlate,      //its solid
                                           component11_mat,          //its material
                                           "logicAltickplate");       //its name(logic)


    physAlTickPlate = new G4PVPlacement(0,
                                        G4ThreeVector(0, 0, 71.7 * mm),  //position vector
                                        logicAlTickPlate,          //its logical volume
                                        "physAlTickPlate",            //its name
                                        logicEnv,                     //its mother volume
                                        false,                        //no boolean operation
                                        0,                            //copy number
                                        checkOverlaps);               //verifica suprapunerile(de evitat)


    logicalVolumeMap.insert(pair<G4String, G4LogicalVolume *>("logicDetector", this->logicDetector));
    //logicalVolumeMap.insert(pair<G4String, G4LogicalVolume *>("logicWorld", this->logicWorld));
    logicalVolumeMap.insert(pair<G4String, G4LogicalVolume *>("logicEnv", this->logicEnv));
    logicalVolumeMap.insert(pair<G4String, G4LogicalVolume *>("logicGePlate", this->logicGePlate));
    logicalVolumeMap.insert(pair<G4String, G4LogicalVolume *>("logicLi", this->logicLi));

    return physWorld;
}

//for sensitive Detector;
void MyDetectorConstruction::ConstructSDandField() {    //createan object
    auto *sensDet = new MySensitiveDetector("SensitiveDetector");

    //logic det. part

    if (logicDetector != nullptr)
        logicDetector->SetSensitiveDetector(sensDet);

    //  if(logicEnv != NULL)
    //  logicEnv->SetSensitiveDetector(sensDet);

}

