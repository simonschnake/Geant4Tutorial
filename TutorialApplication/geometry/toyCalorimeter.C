/* Definition of a toy sampling calorimeter
   Layer Structure taken from the CMS Hadroncalorimeter
   | layer 0     | 9 mm scint   | 40 mm stainless steel |           |
   | layer 1-8   | 3.7 mm scint | 50.5 mm brass         |           |
   | layer 9-14  | 3.7 mm scint | 56.5 mm brass         |           |
   | layer 15+16 | 3.7 mm scint | 75 mm stainless steel | 9mm scint |


   everything in cm, degree, g/cm3
   boxes are from -dx to + dx
   0 is the middle point
*/

void toyCalorimeter()
{
  // half the width in cm 
  Double_t w_scint_0 = 0.9*0.5;
  Double_t w_scint_1 = 0.37*0.5;
  Double_t w_steel_0 = 4.0*0.5; //update phase 2
  Double_t w_steel_3 = 5.05*0.5;
  Double_t w_brass_1 = 5.05*0.5;
  Double_t w_brass_2 = 5.65*0.5;

  Double_t std_length = 30.*0.5;
  
  
  // media
  const TGeoMedium *medVac = gGeoManager->GetMedium("Vacuum");
  const TGeoMedium *medSci = gGeoManager->GetMedium("Scintillator");
  const TGeoMedium *medSte = gGeoManager->GetMedium("Steel");
  const TGeoMedium *medBra = gGeoManager->GetMedium("Brass");

  
  //boxes for layers
  TGeoVolume* scint0 = gGeoManager->MakeBox("scint0", medSci, w_scint_0, std_length, std_length);
  TGeoVolume* scint1 = gGeoManager->MakeBox("scint1", medSci, w_scint_1, std_length, std_length);
  TGeoVolume* steel0 = gGeoManager->MakeBox("steel0", medSte, w_steel_0, std_length, std_length);
  TGeoVolume* steel3 = gGeoManager->MakeBox("steel3", medSte, w_steel_3, std_length, std_length);
  TGeoVolume* brass1 = gGeoManager->MakeBox("brass1", medBra, w_brass_1, std_length, std_length);
  TGeoVolume* brass2 = gGeoManager->MakeBox("brass2", medBra, w_brass_2, std_length, std_length);
  
  //construct layer

  // layer 0
  Double_t width_layer0 = w_scint_0+w_steel_0;
  TGeoVolume* layer0 = gGeoManager->MakeBox("Layer0", medVac, width_layer0, std_length, std_length);
  layer0->AddNode(scint0, 0, new TGeoTranslation(-w_scint_0*0.5, 0, 0));
  layer0->AddNode(steel0, 1, new TGeoTranslation(w_steel_0*0.5, 0, 0));


  // layer 1 - 8
  Double_t width_layer1 =   w_scint_1+w_brass_1;
  TGeoVolume* layer1 = gGeoManager->MakeBox("Layer1", medVac, width_layer1, std_length, std_length);
  layer1->AddNode(scint1, 0, new TGeoTranslation(-w_scint_1*0.5,0,0));
  layer1->AddNode(brass1, 1, new TGeoTranslation(w_brass_1*0.5,0,0));

  // layer 9 - 14
  Double_t width_layer2 = w_scint_1+w_brass_2;
  TGeoVolume* layer2 = gGeoManager->MakeBox("Layer2", medVac, width_layer2, std_length, std_length);
  layer2->AddNode(scint1, 0, new TGeoTranslation(-w_scint_1*0.5,0,0));
  layer2->AddNode(brass2, 1, new TGeoTranslation(w_brass_2*0.5,0,0));
   
  // layer 15 - 16
  Double_t width_layer3 = w_scint_1+w_steel_3+w_scint_0;
  TGeoVolume* layer3
      = gGeoManager->MakeBox("Layer3", medVac, width_layer3, std_length, std_length);
  layer3->AddNode(scint1, 0, new TGeoTranslation(-w_scint_1*0.5,0,0));
  layer3->AddNode(steel3, 1, new TGeoTranslation(w_steel_3*0.5,0,0));
  layer3->AddNode(scint0, 2, new TGeoTranslation(w_steel_3+w_scint_0*0.5,0,0));


  // total width
  Double_t width_total = width_layer0+8*width_layer1+6*width_layer2+width_layer3;
  
  // experimental hall, "world volume" 
  TGeoVolume* top = gGeoManager->MakeBox("EXPH",medVac, 1.5*width_total, std_length, std_length);

  
  // Calorimeter 
  //  TGeoVolume* cal = gGeoManager->MakeBox("CALO",medVac, width_t
                                         otal, std_length, std_length);
  gGeoManager->SetTopVolume(top );  
  
  // add layers to top
  Double_t x = -width_total/2;
    
  top->AddNode(layer0, 0, new TGeoTranslation(x,0,0));
  x+= width_layer0;

  for(int i = 1; i <= 8; ++i)
  {
    top->AddNode(layer1, i, new TGeoTranslation(x,0,0));
  x+= width_layer1;
  }

  for(int i = 9; i <= 14; ++i)
  {
    top->AddNode(layer2, i, new TGeoTranslation(x,0,0));
  x+= width_layer1;
  }

  top->AddNode(layer3, 15, new TGeoTranslation(x,0,0));

  //  TGeoVolume* calo_z = calo->Divide("calo_p",3,-1,0,std_length/4,0,"S");
  //  top->AddNote(cal, 0, new TGeoTranslation(0, 0, 0));
}
