//Test TMVA program
#include "TMVAVariables.h"
#include "MyTMVAnalysis.h"
//#include "TMVAClassificationApp.h"


#include <iostream>
#include <vector>
#include <string>



int main(int argc, char** argv){
//int main(){

  // TMVAVariables *variables = new TMVAVariables("wwplnumqq");
  // variables->Loop();
  
  MyTMVAnalysis *tmva = new MyTMVAnalysis();
  tmva->initialize();
  tmva->execute();
  tmva->finalize();


  // TString methodList;
  // TMVAClassificationApp *tmva_app = new TMVAClassificationApp();
  // for (int i=1; i<argc; i++) {
  //   TString regMethod(argv[i]);
  //   if(regMethod=="-b" || regMethod=="--batch") continue;
  //   if (!methodList.IsNull()) methodList += TString(",");
  //   methodList += regMethod;
  // }
  // tmva_app->execute(methodList);

   
  return 0;

}
