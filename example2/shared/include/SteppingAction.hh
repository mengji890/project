#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class EventAction;
class HistoManager;
class G4LogicalVolume;

/// Stepping action class
/// 

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction*, HistoManager*);
    virtual ~SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    EventAction*  fEventAction;
    HistoManager* fHistoManager;
    G4LogicalVolume* fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
