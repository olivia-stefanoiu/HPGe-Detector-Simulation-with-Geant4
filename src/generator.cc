 #include "generator.hh"

 
 MyPrimaryGenerator::MyPrimaryGenerator()
 {
     G4int nr_particles=1;
     fParticleGun = new G4ParticleGun(nr_particles);

     G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

     particleName="geantino";
     G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
     fParticleGun->SetParticleDefinition(particle);

     fParticleGun->SetParticleEnergy(0*eV);
     fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,70.*mm));
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

     fParticleGun->GeneratePrimaryVertex(anEvent);
 }


