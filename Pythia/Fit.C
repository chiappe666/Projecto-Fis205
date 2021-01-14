int Fit()
{
	TFile *f = new TFile("mymain01.root");
 	TH1F *h1;
 	TH1F *h2;
 	TH1F *h3;
 	TH1F *h4;
 	TH1F *h5;
 	TH1F *h6;
 	Double_t par0;
 	TFitResultPtr r;
 	f -> GetObject("PlLund",h1);
 	f -> GetObject("thLund",h2);
 	f -> GetObject("PlJade",h4);
 	f -> GetObject("thJade",h3);
 	f -> GetObject("PlDurham",h5);
 	f -> GetObject("thDurham",h6);
 	//Lund plane
 	TCanvas *c1 = new TCanvas();
 	h1 -> Fit("expo","B","Same",0,1);
 	//Lund angle
 	TCanvas *c2 = new TCanvas();
 	h2 -> Fit("expo","B","Same",0,1.6);
 	//Jade plane
 	TCanvas *c3 = new TCanvas();
 	h3 -> Fit("expo","B","Same",0,1);
 	//Jade angle
 	TCanvas *c4 = new TCanvas();
 	h4 -> Fit("expo","B","Same",0,1.6);
 	//Durham plane
 	TCanvas *c5 = new TCanvas();
 	h5 -> Fit("expo","B","Same",0,1);
 	//Durham angle
 	TCanvas *c6 = new TCanvas();
 	h6 -> Fit("expo","S","",0,1.6);
	return 0;
}
