#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include  "HistoManager.hh"
#include "G4Step.hh"
//#include "G4Event.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* evt,HistoManager*histo)
: G4UserSteppingAction(),
  fEventAction(evt),
  fScoringVolume(0),
  fHistoManager(histo)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) { 
    const DetectorConstruction* detectorConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;

  // get the name of generated particle
  G4String particlename = step->GetTrack()->GetDefinition()->GetParticleName();
  G4double numberStep =0;
  G4double intrackid =0;
  G4double trackid = step->GetTrack()->GetTrackID();
  G4double trackenergy = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
  G4double trackmomentum = step->GetTrack()->GetDynamicParticle()->GetMomentum();
  G4double energyStep =0;
  G4double momentumStep=0;
  // fill histograms

  fHistoManager->FillHisto(0,trackenergy);
  fHistoManager->FillHisto(1,trackmomentum);

  //fill ntuple
  fHistoManager->FillNtuple(trackenergy,trackmomentum;)

  if (particlename == "pi-" || particlename =="pi+" )
      if (trackid > intrackid)
         {
           numberStep += 1;
           intrackid +=1;
           energyStep +=trackenergy;
           momentumStep +=trackmomentum;
          }
       else
          numberStep +=0;
  else  
  numberStep += 0;
  fEventAction->AddNumb(numberStep);
  fEventAction ->AddEnergy(energyStep);
  fEventAction->AddMomentum(momentumStep);
}
