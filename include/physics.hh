#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
//#include "G4OpticalPhysics.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"


class MyPhysicsList : public G4VModularPhysicsList {

public:
    MyPhysicsList();

    ~MyPhysicsList() override;
//
//protected:
//    // Construct particle and physics
//    virtual void ConstructParticle();
//    virtual void ConstructProcess();
//
//    virtual void SetCuts();

//protected:
//    // these methods Construct particles
//    void ConstructBosons();
//    void ConstructLeptons();

protected:
    // these methods Construct physics processes and register them
  //  void ConstructGeneral();
    void ConstructEM();

};

#endif
