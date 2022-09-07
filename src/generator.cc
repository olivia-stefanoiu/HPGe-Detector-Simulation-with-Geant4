 #include "generator.hh"

 
 MyPrimaryGenerator::MyPrimaryGenerator()
 {
     G4int nr_particles=1;
     fParticleGun = new G4ParticleGun(nr_particles);

     G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

     particleName="geantino";
     G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

     pos=G4ThreeVector(0.,0.,0.); //position vector-in the center
     pos_mom=G4ThreeVector(0.,0.,1.); //z direction - momentum vector
     mom=0*GeV;

     fParticleGun->SetParticlePosition(pos); //for position(in center)
     fParticleGun->SetParticleMomentumDirection(pos_mom); //for direction
     fParticleGun->SetParticleMomentum(mom); //for momentum... in natural units

     fParticleGun->SetParticleDefinition(particle);


     gunMessenger =  new G4GenericMessenger(fParticleGun,"/gun/","Change Momentum");
     gunMessenger->DeclareProperty("momentum",mom,"momentum of particle");
 }
 

  MyPrimaryGenerator::~MyPrimaryGenerator() //delete particle
 {
   delete fParticleGun; //nu vrea sa imi vada pointerul de la messenger?
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


