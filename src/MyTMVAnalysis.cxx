//Class to do regression
#ifndef MYTMVANALYSIS_CXX
#define MYTMVANALYSIS_CXX

#include "MyTMVAnalysis.h"

#include <iostream>
#include <vector>
#include <fstream>




MyTMVAnalysis::MyTMVAnalysis()
{
}

MyTMVAnalysis::~MyTMVAnalysis(){}


void MyTMVAnalysis::initialize(){

  TMVA::Tools::Instance();

  TString option="BDT";
  bool important=false;
  bool doDNN = true;

  m_inputFile_s   = new TFile("/u/user/andres/atlas/run/samples/TMVAVariables_wminmunu.root");
  m_inputFile_b1  = new TFile("/u/user/andres/atlas/run/samples/TMVAVariables_zmumu.root");
  m_inputFile_b2  = new TFile("/u/user/andres/atlas/run/samples/TMVAVariables_wwplnumqq.root");
  m_inputFile_b3  = new TFile("/u/user/andres/atlas/run/samples/TMVAVariables_zzllll.root");
  m_inputFile_b4  = new TFile("/u/user/andres/atlas/run/samples/TMVAVariables_ttbar.root");
  
  //Declare the factory

  m_outputFile = new TFile("./TMVAOutputBDT_ATLAS.root", "RECREATE");
  
  if(option=="reg")//not necessary for variable importance
    m_factory = new TMVA::Factory("TMVARegression", m_outputFile,
				  "!V:!Silent:Color:DrawProgressBar:AnalysisType=Regression" );
  if(option!="reg")
    m_factory = new TMVA::Factory("TMVAClassification", m_outputFile,
				  "!V:ROC:!Correlations:!Silent:Color:!DrawProgressBar:AnalysisType=Classification" );

  //Declare the data loader 
  m_loader = new TMVA::DataLoader("dataset");  

  //Add the feature variables, names reference branches in inputFile ttree
  m_loader->AddVariable("muon_pt");
  m_loader->AddVariable("met");
  m_loader->AddVariable("muon_e");
  m_loader->AddVariable("deltaPhi");
  m_loader->AddVariable("mwt");
  
  if(option=="reg")
    m_loader->AddTarget( "target := var2+var3" ); // define the target for the regress

  //Setup the data set
  TTree *tsignal, *tbackground1, *tbackground2, *tbackground3, *tbackground4;
  m_inputFile_s->GetObject("nominal", tsignal);
  m_inputFile_b1->GetObject("nominal", tbackground1);
  m_inputFile_b2->GetObject("nominal", tbackground2);
  m_inputFile_b3->GetObject("nominal", tbackground3);
  m_inputFile_b4->GetObject("nominal", tbackground4);
  
  TCut mycuts = ""; // e.g. TCut mycuts = "abs(var1)<0.5";
  TCut mycutb = ""; // e.g. TCut mycuts = "abs(var1)<0.5";


  if(option=="reg"){
    m_loader->AddRegressionTree(tsignal, 1.);  // link the TTree to the loader, weight for each event  = 1
    m_loader->PrepareTrainingAndTestTree(mycuts,
					 "nTrain_Regression=1000:nTest_Regression=1000:SplitMode=Random:NormMode=NumEvents:!V" );
  }


  if(option!="reg"){
    m_loader->AddSignalTree(tsignal, 1.);            //signal weight = 1
    m_loader->AddBackgroundTree (tbackground1, 1.);  //background weight = 1 
    m_loader->AddBackgroundTree (tbackground2, 1.);  //background weight = 1 
    m_loader->AddBackgroundTree (tbackground3, 1.);  //background weight = 1 
    m_loader->AddBackgroundTree (tbackground4, 1.);  //background weight = 1 
    m_loader->PrepareTrainingAndTestTree(mycuts, mycutb,
					 "nTrain_Signal=10000:nTrain_Background=10000:nTest_Signal=5000:nTest_Background=5000:SplitMode=Random:NormMode=NumEvents:!V" );
  }

  return;
}  


void MyTMVAnalysis::MVAMethods(){
  //book the MVA methods

  bool important = false;
  //Varibale importance
  if(important){
    m_vi = new TMVA::VariableImportance(m_loader);
  
    m_vi->BookMethod(TMVA::Types::kBDT, "BDT",
		     "!V:NTrees=5:MinNodeSize=2.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
    
    m_vi->SetType(TMVA::kShort);
    
    m_vi->Evaluate();
  }
  
      
  //Book the regression method

  //Book the MVA method
  //Boosted Decision Trees
  m_factory->BookMethod(/*&*/m_loader,TMVA::Types::kBDT, "BDTG",
  			TString("!H:!V:NTrees=64::BoostType=Grad:Shrinkage=0.3:nCuts=20:MaxDepth=4:")+
  			TString("RegressionLossFunctionBDTG=AbsoluteDeviation"));
  
  //Boosted Decision Trees
  m_factory->BookMethod(m_loader,TMVA::Types::kBDT, "BDT",
  		     "!V:NTrees=200:MinNodeSize=2.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
  
  //Multi-Layer Perceptron (Neural Network)
  m_factory->BookMethod(m_loader, TMVA::Types::kMLP, "MLP",
  		     "!H:!V:NeuronType=tanh:VarTransform=N:NCycles=100:HiddenLayers=N+5:TestRate=5:!UseRegulator" );

  // Support Vector Machine
  m_factory->BookMethod( m_loader, TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );


  //Deep Neural Networks
  configDNN();
  // Multi-core CPU implementation.
  TString cpuOptions = dnnOptions + ":Architecture=CPU";
  //m_factory->BookMethod(m_loader, TMVA::Types::kDNN, "DNN_CPU", cpuOptions);

  // Cuda implementation.
  // TString gpuOptions = dnnOptions + ":Architecture=GPU";
  // m_factory->BookMethod(m_loader, TMVA::Types::kDNN, "DNN_GPU", gpuOptions);
  

  return;
}

void MyTMVAnalysis::execute(){

  bool doTMVA = true;

  std::cout<<"Exucuting..."<<std::endl;

  if(doTMVA){
    //Book Method(s)
    MVAMethods();
    //Train the method(s)
    m_factory->TrainAllMethods();  
    //Test and evaluate the model(s)
    m_factory->TestAllMethods();
    m_factory->EvaluateAllMethods();
  }
  
  return;
}


void MyTMVAnalysis::finalize(){
  
  //Gather and plot the results
  bool doTMVA = true;
  bool doRegression = false;
  if(doRegression){
    m_outputFile->Close();
    auto resultsFile = TFile::Open("TMVAOutputBDT.root");
    auto resultsTree = resultsFile->Get("dataset/TestTree"); 
    TCanvas c;
    resultsTree->Draw("BDTG-target"); // BDTG is the predicted value, target is the true value
    c.Print("./Plots/regression.pdf");
  }

  if(doTMVA){
    //Plot ROC Curve
    auto c1 = m_factory->GetROCCurve(/*&*/m_loader);
    c1->Print("./Plots/dataLoader.pdf");
    m_outputFile->Close();

  }

  //variable importance results
  bool important = false;
  if(important){
    m_result_vi = m_vi->GetResults();
    m_result_vi.Print();
    TCanvas *plot = m_result_vi.Draw();
    plot->Print("./Plots/VariableImportance.pdf");
  }
  

  return;
}

void MyTMVAnalysis::configDNN(){
  // General layout.
  TString layoutString ("Layout=TANH|128,TANH|128,TANH|128,LINEAR");

  // Training strategies.
  TString training0("LearningRate=1e-1,Momentum=0.9,Repetitions=1,"
		    "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
		    "WeightDecay=1e-4,Regularization=L2,"
		    "DropConfig=0.0+0.5+0.5+0.5, Multithreading=True");

  TString training1("LearningRate=1e-2,Momentum=0.9,Repetitions=1,"
		    "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
		    "WeightDecay=1e-4,Regularization=L2,"
		    "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");

  TString training2("LearningRate=1e-3,Momentum=0.0,Repetitions=1,"
		    "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
		    "WeightDecay=1e-4,Regularization=L2,"
		    "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
  TString trainingStrategyString ("TrainingStrategy=");
  trainingStrategyString += training0 + "|" + training1 + "|" + training2;
  
  // General Options.
  dnnOptions = "!H:V:ErrorStrategy=CROSSENTROPY:VarTransform=N:"
               "WeightInitialization=XAVIERUNIFORM";

  dnnOptions.Append (":"); dnnOptions.Append (layoutString);
  dnnOptions.Append (":"); dnnOptions.Append (trainingStrategyString);
  return;
}


#endif

//https://gitlab.cern.ch/vgrauer/tmva/blob/master/TMVAscr.C
//https://gitlab.cern.ch/zhcui/tmva-script/tree/master
