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
     G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
    //cum poate fi nul? nu se apeleaza constructorul intai?
     if(particle == G4Geantino::Geantino())
     {
         G4int Z = 63; //nr de p+
         G4int A = 152; //nr de masa

         G4double charge = 0.*eplus;//elementary charge
         G4double energy = 0.*keV;

         G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);

         fParticleGun->SetParticleDefinition(ion);
         fParticleGun->SetParticleCharge(charge);
         fParticleGun->SetParticleEnergy(energy);

     }

     fParticleGun->GeneratePrimaryVertex(anEvent);
 }


