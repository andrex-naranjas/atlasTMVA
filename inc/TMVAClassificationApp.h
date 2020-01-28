//TMVAApp Class
#ifndef TMVACLASSIFICATIONAPP_H
#define TMVACLASSIFICATIONAPP_H

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

//TMVA Includes
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

class TMVAClassificationApp{

public:
TMVAClassificationApp();
virtual ~TMVAClassificationApp();

virtual void execute(TString myList="");



};

#endif
