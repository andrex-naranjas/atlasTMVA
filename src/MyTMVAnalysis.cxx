//Class to compare several TMVA algorithms
//author Andres Ramirez (andres.ramirez.morales@cern.ch)

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
  
  //input files
  m_inputFile_s   = new TFile("/home/andrex/PostDoc/FirstCode/atlas/run/samples/TMVAVariables_wminmunu.root");
  m_inputFile_b1  = new TFile("/home/andrex/PostDoc/FirstCode/atlas/run/samples/TMVAVariables_zmumu.root");
  m_inputFile_b2  = new TFile("/home/andrex/PostDoc/FirstCode/atlas/run/samples/TMVAVariables_wwplnumqq.root");
  m_inputFile_b3  = new TFile("/home/andrex/PostDoc/FirstCode/atlas/run/samples/TMVAVariables_zzllll.root");
  m_inputFile_b4  = new TFile("/home/andrex/PostDoc/FirstCode/atlas/run/samples/TMVAVariables_ttbar.root");

  //output
  m_outputFile = new TFile("./TMVAOutputBDT_ATLAS.root", "RECREATE");

  //Declare the factory
  m_factory = new TMVA::Factory("TMVAClassification", m_outputFile,
				  "!V:ROC:!Correlations:!Silent:Color:!DrawProgressBar:AnalysisType=Classification" );
  //Declare the data loader 
  m_loader = new TMVA::DataLoader("dataset");  

  //Add the feature variables, names reference branches in inputFile ttree
  m_loader->AddVariable("muon_pt");
  m_loader->AddVariable("met");
  //m_loader->AddVariable("muon_e");
  m_loader->AddVariable("deltaPhi");
  m_loader->AddVariable("mwt");

  
  //Setup the data set
  TTree *tsignal, *tbackground1, *tbackground2, *tbackground3, *tbackground4;
  m_inputFile_s->GetObject("nominal", tsignal);
  m_inputFile_b1->GetObject("nominal", tbackground1);
  m_inputFile_b2->GetObject("nominal", tbackground2);
  m_inputFile_b3->GetObject("nominal", tbackground3);
  m_inputFile_b4->GetObject("nominal", tbackground4);
  
  TCut mycuts = ""; // e.g. TCut mycuts = "abs(var1)<0.5";
  TCut mycutb = ""; // e.g. TCut mycuts = "abs(var1)<0.5"; 

  //add trees
  m_loader->AddSignalTree(tsignal, 1.);            //signal weight = 1
  m_loader->AddBackgroundTree (tbackground1, 1.);  //background weight = 1 
  m_loader->AddBackgroundTree (tbackground2, 1.);  //background weight = 1 
  m_loader->AddBackgroundTree (tbackground3, 1.);  //background weight = 1 
  m_loader->AddBackgroundTree (tbackground4, 1.);  //background weight = 1 
  m_loader->PrepareTrainingAndTestTree(mycuts, mycutb,
				       //"nTrain_Signal=1000:nTrain_Background=1000:nTest_Signal=500:nTest_Background=500:SplitMode=Random:NormMode=NumEvents:!V" );
				       "nTrain_Signal=10000:nTrain_Background=10000:nTest_Signal=5000:nTest_Background=5000:SplitMode=Random:NormMode=NumEvents:!V" );

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
  
 
  // //Book the MVA method
  // //Boosted Decision Trees
  // m_factory->BookMethod(/*&*/m_loader,TMVA::Types::kBDT, "BDTG",
  // 			TString("!H:!V:NTrees=64::BoostType=Grad:Shrinkage=0.3:nCuts=20:MaxDepth=4:")+
  // 			TString("RegressionLossFunctionBDTG=AbsoluteDeviation"));
  
  //Boosted Decision Trees
  m_factory->BookMethod(m_loader,TMVA::Types::kBDT, "BDT",
  		     "!V:NTrees=100:MinNodeSize=5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.15:SeparationType=GiniIndex:nCuts=100" );
  //  		     "!V:NTrees=200:MinNodeSize=2.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
  
  // //Multi-Layer Perceptron (Neural Network)
  // m_factory->BookMethod(m_loader, TMVA::Types::kMLP, "MLP",
  // 		     "!H:!V:NeuronType=tanh:VarTransform=N:NCycles=100:HiddenLayers=N+5:TestRate=5:!UseRegulator" );

  // Support Vector Machine
  m_factory->BookMethod( m_loader, TMVA::Types::kSVM, "SVM_RBF", "Kernel=RBF:Gamma=0.25:Tol=0.001:VarTransform=Norm" );
  m_factory->BookMethod( m_loader, TMVA::Types::kSVM, "SVM_MG",  "Kernel=MultiGauss:GammaList=0.25,0.25,0.25,0.25:Tol=0.001:VarTransform=Norm" );//MultiGauss kernel
  m_factory->BookMethod( m_loader, TMVA::Types::kSVM, "SVM_Poly","Kernel=Polynomial:Theta=0.1:Order=2:Tol=0.001:VarTransform=Norm" );//Polynomial kernel
  
  m_factory->BookMethod( m_loader, TMVA::Types::kSVM, "SVM_prod_polRBF","Kernel=Prod:KernelList=RBF*Polynomial:Gamma=0.1:Theta=1:Order=1:Tol=0.001:VarTransform=Norm" );//prod
  m_factory->BookMethod( m_loader, TMVA::Types::kSVM, "SVM_sum_polRBF", "Kernel=Sum:KernelList=RBF+Polynomial:Gamma=0.1:Theta=1:Order=1:Tol=0.001:VarTransform=Norm" );//sum
  m_factory->BookMethod( m_loader, TMVA::Types::kSVM, "SVM_prod_mgRBF", "Kernel=Prod:KernelList=RBF*MultiGauss:Gamma=0.25:GammaList=0.1,0.2:Tol=0.001:VarTransform=Norm" );//prod
  m_factory->BookMethod( m_loader, TMVA::Types::kSVM, "SVM_sum_mgRBF",  "Kernel=Sum:KernelList=RBF+MultiGauss:Gamma=0.25:GammaList=0.1,0.2:Tol=0.001:VarTransform=Norm" );//prod


  //Deep Neural Networks
  // configDNN();
  // // Multi-core CPU implementation.
  // TString cpuOptions = dnnOptions + ":Architecture=CPU";
  // m_factory->BookMethod(m_loader, TMVA::Types::kDNN, "DNN_CPU", cpuOptions);

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
