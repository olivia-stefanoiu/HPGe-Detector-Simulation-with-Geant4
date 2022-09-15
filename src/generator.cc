 #include "generator.hh"

#include "G4RandomDirection.hh"

 
 MyPrimaryGenerator::MyPrimaryGenerator()
 {
     G4int nr_particles=1;
     fParticleGun = new G4ParticleGun(nr_particles);

     G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

     particleName="geantino";
     G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

     fParticleGun->SetParticleDefinition(particle);
     fParticleGun->SetParticleEnergy(1*MeV);
     fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,75.*mm));
     fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

 }
 

  MyPrimaryGenerator::~MyPrimaryGenerator() //delete particle
 {
   delete fParticleGun;
 }
 

 void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
 {

     if(fParticleGun->GetParticleDefinition() == G4Geantino::Geantino())
     {
         G4int Z = 27; //nr de p+
         G4int A = 60; //nr de masa

         G4double ionCharge = 0.*eplus;//elementary charge
         G4double excitEnergy = 0.*keV;

         G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z, A, excitEnergy);

         fParticleGun->SetParticleDefinition(ion);
         fParticleGun->SetParticleCharge(ionCharge);


     }

     G4double cosTheta = 2*G4UniformRand() - 1., phi = CLHEP::twopi*G4UniformRand();
     G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
     G4double ux = sinTheta*std::cos(phi),
             uy = sinTheta*std::sin(phi),
             uz = cosTheta;

     fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));


     fParticleGun->GeneratePrimaryVertex(anEvent);
 }


