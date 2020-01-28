//MyTMVAnalysis includes
#ifndef MYTMVANALYSIS_H
#define MYTMVANALYSIS_H

#include "TFile.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Types.h"
#include "TMVA/VariableImportance.h"

#include <TFile.h>

#include "TTree.h"
#include "TCut.h"
#include "TFile.h"
#include "TString.h"




class MyTMVAnalysis{

 public:
  MyTMVAnalysis();
  virtual ~MyTMVAnalysis();

  virtual void initialize();
  virtual void execute();
  virtual void finalize();

 private:
  virtual void MVAMethods();
  virtual void configDNN();

  //TMVA objects
  TMVA::Factory    *m_factory;
  TMVA::DataLoader *m_loader;
  TMVA::VariableImportance *m_vi;
  TMVA::VariableImportanceResult m_result_vi; //reference cannot use pointer
  
  TFile *m_inputFile_s;
  TFile *m_inputFile_b1,*m_inputFile_b2,*m_inputFile_b3, *m_inputFile_b4;
  TFile *m_outputFile;  
  TString dnnOptions="";

  
};

#endif
