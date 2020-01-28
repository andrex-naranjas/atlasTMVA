#define TMVAVariables_cxx
#include "TMVAVariables.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TFile.h"
#include "TTree.h"

#include <iostream> 
#include <string>


void TMVAVariables::Loop()//std::string sample)
{
  
  if (fChain == 0) return;
  
  TFile* newfile;
  newfile = new TFile(("./samples/TMVAVariables_"+nameOfSample+".root").c_str(), "RECREATE");
  
  TTree *tree = new TTree("nominal","A ROOT tree");

  //references to pointers
  // std::vector<float>  ref_R_mu_pt;
  // std::vector<float>  *R_mu_pt = &ref_R_mu_pt;

  double R_mu_pt;     tree->Branch( "muon_pt", &R_mu_pt);//, 64000);
  double R_mu_e;      tree->Branch( "muon_e",  &R_mu_e);
  double R_met;       tree->Branch( "met", &R_met);
  double R_mwt;       tree->Branch( "mwt", &R_mwt);
  double R_deltaPhi;  tree->Branch( "deltaPhi", &R_deltaPhi);

  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    
    if(jentry % 100000 == 0) std::cout<<"Processing event  "<<jentry<<"/"<<nentries<<std::endl;
        
    if(mu_pt->size()>0){
      R_mu_pt = mu_pt->at(0);
      R_mu_e  = mu_e->at(0);
      R_met   = met_met;
      float dPhi=std::fabs(met_phi-mu_phi->at(0));
      if(dPhi>3.14159265) dPhi=2.*3.14159265-dPhi;
      R_deltaPhi = dPhi;
      R_mwt = std::sqrt(2.*((mu_pt->at(0))*met_met)*(1.-std::cos(dPhi)));              
      tree->Fill();       
    }
    
    
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
  }
  
  newfile->Write();  
}
