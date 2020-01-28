#ifndef TMVAVariables_h
#define TMVAVariables_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

#include <iostream>
#include <string>

class TMVAVariables {
  
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Fixed size dimensions of array or collections stored in the TTree if any.
  
  std::string nameOfSample;
  
  // Declaration of leaf types
  Float_t         weight_mc;
  Float_t         weight_pileup;
  Float_t         weight_leptonSF;
  Float_t         weight_globalLeptonTriggerSF;
  Float_t         weight_oldTriggerSF;
  Float_t         weight_jvt;
  ULong64_t       eventNumber;
  UInt_t          runNumber;
  UInt_t          randomRunNumber;
  UInt_t          mcChannelNumber;
  Float_t         mu;
  UInt_t          backgroundFlags;
  UInt_t          hasBadMuon;
  
  
  std::vector<float>   *mu_pt;
  std::vector<float>   *mu_eta;
   std::vector<float>   *mu_phi;
   std::vector<float>   *mu_e;
   std::vector<float>   *mu_charge;
   std::vector<float>   *mu_topoetcone20;
   std::vector<float>   *mu_ptvarcone30;
   std::vector<float>   *mu_d0sig;
   std::vector<float>   *mu_delta_z0_sintheta;
   std::vector<int>     *mu_true_type;
   std::vector<int>     *mu_true_origin;
   std::vector<char>    *mu_true_isPrompt;
   Float_t         met_met;
   Float_t         met_phi;
   Int_t           munu_2017;
   Int_t           mumu_2017;
   Char_t          HLT_mu50;
   Char_t          HLT_mu26_ivarmedium;
   std::vector<char>    *mu_trigMatch_HLT_mu50;
   std::vector<char>    *mu_trigMatch_HLT_mu26_ivarmedium;
  
   ULong64_t       weight_pileup_hash;
   Float_t         bornMass_KFactor;
   Double_t        weight_KFactor;

  
   Int_t           primaryVertices;
   Float_t         hadronic_pt;
   Float_t         hadronic_eta;
   Float_t         hadronic_phi;
   Float_t         hadronic_e;
   Double_t        sumET_PFO;

  std::vector<float>   *mu_topoetcone30;
   std::vector<float>   *mu_topoetcone40;
   std::vector<float>   *mu_ptvarcone20;
   std::vector<float>   *mu_ptvarcone40;
   std::vector<float>   *mu_ptcone20;
   std::vector<float>   *mu_ptcone30;
   std::vector<float>   *mu_ptcone40;

   std::vector<int>     *muon_trigger_mu20_iloose_L1MU15;
   std::vector<int>     *muon_trigger_mu50;

   // List of branches
   TBranch        *b_weight_mc;   //!
   TBranch        *b_weight_pileup;   //!
   TBranch        *b_weight_leptonSF;   //!
   TBranch        *b_weight_globalLeptonTriggerSF;   //!
   TBranch        *b_weight_oldTriggerSF;   //!
   TBranch        *b_weight_jvt;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_randomRunNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_backgroundFlags;   //!
   TBranch        *b_hasBadMuon;   //!
  
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_e;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_topoetcone20;   //!
   TBranch        *b_mu_ptvarcone30;   //!
   TBranch        *b_mu_d0sig;   //!
   TBranch        *b_mu_delta_z0_sintheta;   //!
   TBranch        *b_mu_true_type;   //!
   TBranch        *b_mu_true_origin;   //!
   TBranch        *b_mu_true_isPrompt;   //!
  
   TBranch        *b_met_met;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_munu_2017;   //!
   TBranch        *b_mumu_2017;   //!
   TBranch        *b_HLT_mu50;   //!
   TBranch        *b_HLT_mu26_ivarmedium;   //!
   TBranch        *b_mu_trigMatch_HLT_mu50;   //!
   TBranch        *b_mu_trigMatch_HLT_mu26_ivarmedium;   //!
   TBranch        *b_weight_pileup_hash;   //!
   TBranch        *b_bornMass_KFactor;   //!
   TBranch        *b_weight_KFactor;   //!
  
   TBranch        *b_primaryVertices;   //!
   TBranch        *b_hadronic_pt;   //!
   TBranch        *b_hadronic_eta;   //!
   TBranch        *b_hadronic_phi;   //!
   TBranch        *b_hadronic_e;   //!
   TBranch        *b_sumET_PFO;   //!
   TBranch        *b_mu_topoetcone30;   //!
   TBranch        *b_mu_topoetcone40;   //!
   TBranch        *b_mu_ptvarcone20;   //!
   TBranch        *b_mu_ptvarcone40;   //!
   TBranch        *b_mu_ptcone20;   //!
   TBranch        *b_mu_ptcone30;   //!
   TBranch        *b_mu_ptcone40;   //!
   TBranch        *b_muon_trigger_mu20_iloose_L1MU15;   //!
   TBranch        *b_muon_trigger_mu50;   //!

  TMVAVariables(std::string);
  virtual ~TMVAVariables();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TMVAVariables_cxx
TMVAVariables::TMVAVariables(std::string process) : fChain(0) 
{

  TTree *tree;

  nameOfSample = process;
  TChain *chain = new TChain("nominal","");
  chain->Add(("/home/andrex/PostDoc/FirstCode/atlas/data/"+nameOfSample+"/*.root").c_str());
  tree=chain;
  Init(tree);


  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.  
   // if (tree == 0) {
   //    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/andrex/PostDoc/FirstCode/atlas/data/wminmunu/user.anramire.15871832._000001.mc_mj_d0.root");
   //    if (!f || !f->IsOpen()) {
   //       f = new TFile("/home/andrex/PostDoc/FirstCode/atlas/data/wminmunu/user.anramire.15871832._000001.mc_mj_d0.root");
   //    }
   //    f->GetObject("nominal",tree);

   // }
   // Init(tree);
}

TMVAVariables::~TMVAVariables()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TMVAVariables::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TMVAVariables::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TMVAVariables::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   mu_pt = 0;
   mu_eta = 0;
   mu_phi = 0;
   mu_e = 0;
   mu_charge = 0;
   mu_topoetcone20 = 0;
   mu_ptvarcone30 = 0;
   mu_d0sig = 0;
   mu_delta_z0_sintheta = 0;
   mu_true_type = 0;
   mu_true_origin = 0;
   mu_true_isPrompt = 0;
   mu_trigMatch_HLT_mu50 = 0;
   mu_trigMatch_HLT_mu26_ivarmedium = 0;
   mu_topoetcone30 = 0;
   mu_topoetcone40 = 0;
   mu_ptvarcone20 = 0;
   mu_ptvarcone40 = 0;
   mu_ptcone20 = 0;
   mu_ptcone30 = 0;
   mu_ptcone40 = 0;
   muon_trigger_mu20_iloose_L1MU15 = 0;
   muon_trigger_mu50 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("weight_mc", &weight_mc, &b_weight_mc);
   fChain->SetBranchAddress("weight_pileup", &weight_pileup, &b_weight_pileup);
   fChain->SetBranchAddress("weight_leptonSF", &weight_leptonSF, &b_weight_leptonSF);
   fChain->SetBranchAddress("weight_globalLeptonTriggerSF", &weight_globalLeptonTriggerSF, &b_weight_globalLeptonTriggerSF);
   fChain->SetBranchAddress("weight_oldTriggerSF", &weight_oldTriggerSF, &b_weight_oldTriggerSF);
   fChain->SetBranchAddress("weight_jvt", &weight_jvt, &b_weight_jvt);

   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("randomRunNumber", &randomRunNumber, &b_randomRunNumber);
   fChain->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("backgroundFlags", &backgroundFlags, &b_backgroundFlags);
   fChain->SetBranchAddress("hasBadMuon", &hasBadMuon, &b_hasBadMuon);
   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_e", &mu_e, &b_mu_e);
   fChain->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain->SetBranchAddress("mu_topoetcone20", &mu_topoetcone20, &b_mu_topoetcone20);
   fChain->SetBranchAddress("mu_ptvarcone30", &mu_ptvarcone30, &b_mu_ptvarcone30);
   fChain->SetBranchAddress("mu_d0sig", &mu_d0sig, &b_mu_d0sig);
   fChain->SetBranchAddress("mu_delta_z0_sintheta", &mu_delta_z0_sintheta, &b_mu_delta_z0_sintheta);
   fChain->SetBranchAddress("mu_true_type", &mu_true_type, &b_mu_true_type);
   fChain->SetBranchAddress("mu_true_origin", &mu_true_origin, &b_mu_true_origin);
   fChain->SetBranchAddress("mu_true_isPrompt", &mu_true_isPrompt, &b_mu_true_isPrompt);
   fChain->SetBranchAddress("met_met", &met_met, &b_met_met);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("munu_2017", &munu_2017, &b_munu_2017);
   fChain->SetBranchAddress("mumu_2017", &mumu_2017, &b_mumu_2017);
   fChain->SetBranchAddress("HLT_mu50", &HLT_mu50, &b_HLT_mu50);
   fChain->SetBranchAddress("HLT_mu26_ivarmedium", &HLT_mu26_ivarmedium, &b_HLT_mu26_ivarmedium);
   fChain->SetBranchAddress("mu_trigMatch_HLT_mu50", &mu_trigMatch_HLT_mu50, &b_mu_trigMatch_HLT_mu50);
   fChain->SetBranchAddress("mu_trigMatch_HLT_mu26_ivarmedium", &mu_trigMatch_HLT_mu26_ivarmedium, &b_mu_trigMatch_HLT_mu26_ivarmedium);
   fChain->SetBranchAddress("weight_pileup_hash", &weight_pileup_hash, &b_weight_pileup_hash);
   fChain->SetBranchAddress("bornMass_KFactor", &bornMass_KFactor, &b_bornMass_KFactor);
   fChain->SetBranchAddress("weight_KFactor", &weight_KFactor, &b_weight_KFactor);
   fChain->SetBranchAddress("primaryVertices", &primaryVertices, &b_primaryVertices);
   fChain->SetBranchAddress("hadronic_pt", &hadronic_pt, &b_hadronic_pt);
   fChain->SetBranchAddress("hadronic_eta", &hadronic_eta, &b_hadronic_eta);
   fChain->SetBranchAddress("hadronic_phi", &hadronic_phi, &b_hadronic_phi);
   fChain->SetBranchAddress("hadronic_e", &hadronic_e, &b_hadronic_e);
   fChain->SetBranchAddress("sumET_PFO", &sumET_PFO, &b_sumET_PFO);
   fChain->SetBranchAddress("mu_topoetcone30", &mu_topoetcone30, &b_mu_topoetcone30);
   fChain->SetBranchAddress("mu_topoetcone40", &mu_topoetcone40, &b_mu_topoetcone40);
   fChain->SetBranchAddress("mu_ptvarcone20", &mu_ptvarcone20, &b_mu_ptvarcone20);
   fChain->SetBranchAddress("mu_ptvarcone40", &mu_ptvarcone40, &b_mu_ptvarcone40);
   fChain->SetBranchAddress("mu_ptcone20", &mu_ptcone20, &b_mu_ptcone20);
   fChain->SetBranchAddress("mu_ptcone30", &mu_ptcone30, &b_mu_ptcone30);
   fChain->SetBranchAddress("mu_ptcone40", &mu_ptcone40, &b_mu_ptcone40);
   fChain->SetBranchAddress("muon_trigger_mu20_iloose_L1MU15", &muon_trigger_mu20_iloose_L1MU15, &b_muon_trigger_mu20_iloose_L1MU15);
   fChain->SetBranchAddress("muon_trigger_mu50", &muon_trigger_mu50, &b_muon_trigger_mu50);
   Notify();
}

Bool_t TMVAVariables::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TMVAVariables::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TMVAVariables::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TMVAVariables_cxx
