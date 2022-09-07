#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh" //legatura cu actionInitialization

#include "G4ParticleGun.hh"   // construct the particle gun
#include "G4ParticleTable.hh" // clasa- pentru a stoca proprietatile intr-o lista
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"

#include "G4Geantino.hh"
#include "G4IonTable.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
  public:
     MyPrimaryGenerator();
     ~MyPrimaryGenerator()override;

   void GeneratePrimaries(G4Event*)override;
    G4ParticleGun* GetParticleGun() { return fParticleGun;} ;
  
  private:

     G4ParticleGun *fParticleGun=nullptr;

     G4GenericMessenger *gunMessenger=nullptr;
     G4ThreeVector pos,pos_mom;
     G4double mom;

    G4String particleName;
};

#endif
