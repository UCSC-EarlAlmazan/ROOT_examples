{
  // This example shows how to read out data from a ntuple.
  TFile *f = TFile::Open("ntuple.root");
  TTree* Hgg = (TTree*)f->Get("Hgg") ;

  int nevt = Hgg->GetEntries();
  cout <<  nevt << endl;
  double mgg, weight;
  int is_signal, is_MC ;

  vector<int> *n_SCThits;

  Hgg->SetBranchAddress( "mgg", &mgg );
  Hgg->SetBranchAddress( "weight", &weight );
  Hgg->SetBranchAddress( "is_signal", &is_signal );
  Hgg->SetBranchAddress( "is_MC", &is_MC );

  Hgg->SetBranchAddress( "n_SCThits", &n_SCThits );

  TH1F* h_s = new TH1F("h_s","h_s",120,100,160);
  TH1F* h_b = new TH1F("h_b","h_b",120,100,160);

  for( int i = 0 ; i < nevt ; i ++ )
    {
      Hgg->GetEntry(i);
      if( (*n_SCThits).size() <= 15 ) continue ; // throw away events where the size of n_SCThits vector is less than 15.

      cout << (*n_SCThits)[0] << endl;
      //      cout << mgg << " " << weight << " " << is_signal << " " << is_MC << endl;
      if( is_signal == 1 ) // select events with is_signal == 1
        {
          h_s->Fill(mgg,weight);
        }
      else
        h_b->Fill(mgg,weight);

      //      cout << " Number of tracks is " << n_SCThits.size() << endl;
    }

  TCanvas *c_1 = new TCanvas();

  h_s->SetLineWidth(2);
  h_s->SetLineColor(2);
  h_s->SetLineStyle(1);
  h_s->SetFillColor(2);

  h_b->SetLineWidth(2);
  h_b->SetLineColor(1);
  h_b->SetLineStyle(1);
  h_b->SetFillColor(5);

  THStack *sk_1 = new THStack();
  sk_1->Add(h_b);
  sk_1->Add(h_s);
  sk_1->Draw();
  sk_1->GetXaxis()->SetTitle("M_{#gamma#gamma} [GeV]");
  sk_1->GetYaxis()->SetTitle("Entries");

  TLegend leg_1(0.65,0.8,0.85,0.9);
  leg_1.AddEntry(h_s,"H #rightarrow #gamma#gamma","FL");
  leg_1.AddEntry(h_b,"Background","F");
  leg_1.SetLineColor(0);
  leg_1.SetTextSize(0.05);
  leg_1.SetShadowColor(0);
  leg_1.SetFillStyle(0);
  leg_1.Draw();

  TLatex cap_1;
  cap_1.SetNDC();
  cap_1.SetTextColor(1);
  cap_1.DrawLatex(0.2,0.25,"#int Ldt = 20.3 fb^{-1} #sqrt{s} = 8 TeV");
  cap_1.DrawLatex(0.2,0.35,"ATLAS Internal");

  c_1->SaveAs("example3_figure_1.png");
}