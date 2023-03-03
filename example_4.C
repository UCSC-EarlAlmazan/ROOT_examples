{

  // This example shows how to generate random numbers, fill and plot histograms, and perform a fit using ROOT

  double b_mgg , s_mgg ;

  TH1F* h_s = new TH1F("h_s","h_s",120,100,160);
  TH1F* h_b = new TH1F("h_b","h_b",120,100,160);
  for( int i = 0 ; i < 100000 ; i ++ )
    {
      s_mgg = gRandom->Gaus( 125, 2);
      b_mgg = gRandom->Exp(500);

      double signal_weight = 0.01;

      h_s -> Fill( s_mgg , signal_weight) ;
      h_b -> Fill( b_mgg ) ;

      //      cout << " randomized s_mgg and b_mgg " << s_mgg << " " << b_mgg << endl;
    }

  TCanvas *c_1 = new TCanvas();

  h_s->SetLineWidth(2);
  h_s->SetLineColor(2);
  h_s->SetLineStyle(1);
  h_s->SetFillColor(2);

  h_s->Fit("gaus","","",120,130);

  double max_s = h_s->GetMaximum() * 1.5;

  h_s->GetXaxis()->SetTitle("M_{#gamma#gamma} [GeV]");
  h_s->GetYaxis()->SetTitle("Entries");

  h_s->GetYaxis()->SetRangeUser(0,max_s);

  h_s->Draw();
  //  h_b->Draw("same");

  c_1->SaveAs("plot_fit_a_gaus.png");

}