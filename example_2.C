{

  // This example shows how to generate random numbers, save the data in a TTree object.
  // The ROOT file containing a TTree object is called a "ntuple"

  TTree fOutputTree("Hgg","Hgg") ;
  TFile fOuputFile("ntuple.root","recreate") ;

  double mgg , weight;
  int is_signal, is_MC ;
  vector<double> n_SCThits ;
  fOutputTree.Branch("mgg", &mgg , "mgg/D") ;
  fOutputTree.Branch("weight", &weight , "weight/D") ;
  fOutputTree.Branch("is_signal", &is_signal , "is_signal/I") ;
  fOutputTree.Branch("is_MC", &is_MC , "is_MC/I") ;

  fOutputTree.Branch("n_SCThits", &n_SCThits) ;

  for( int i = 0 ; i < 100000 ; i ++ )
    {
      n_SCThits.clear();
      mgg = gRandom->Gaus( 125, 2);
      weight = 0.01;
      is_signal = 1 ;
      is_MC = 1 ;

      int n_trk = gRandom->Poisson(25);
      int nscthits ;
      for( int j = 0 ; j < n_trk ; j ++ ){
        nscthits = gRandom->Poisson(14);
        n_SCThits.push_back(nscthits);
      }

      fOutputTree.Fill();
    }

  for( int i = 0 ; i < 150000 ; i ++ )
    {
      n_SCThits.clear();
      mgg = gRandom->Exp(500);
      weight = 1 ;
      is_signal = 0 ;
      is_MC = 1 ;

      int n_trk = gRandom->Poisson(35);
      int nscthits ;
      for( int j = 0 ; j < n_trk ; j ++ ){
        nscthits = gRandom->Poisson(8);
        n_SCThits.push_back(nscthits);
      }

      fOutputTree.Fill();
    }

  fOutputTree.Write();
  fOuputFile.Close();

}
