//clip5_generatig Particles
#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh" //legatura cu actionInitialization

#include "G4ParticleGun.hh"   // construct the particle gun
#include "G4ParticleTable.hh" // clasa- pentru a stoca proprietatile intr-o lista
#include "G4SystemOfUnits.hh" // clasa- SI
#include "G4GenericMessenger.hh"

//for decay

#include "G4Geantino.hh"
#include "G4IonTable.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction //our class
{
  public:
     MyPrimaryGenerator();
     ~MyPrimaryGenerator()override;

   void GeneratePrimaries(G4Event*)override; //generator function("main") crate the primaries
  
  private:

     G4ParticleGun *fParticleGun=nullptr; // particle gun fct.
     G4GenericMessenger *gunMessenger=nullptr;
     G4ThreeVector pos,pos_mom;
     G4double mom;

    G4String particleName;
};

#endif
