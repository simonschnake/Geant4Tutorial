/* Definition of a toy sampling calorimeter
   Layer Structure taken from the CMS Hadroncalorimeter
*/

void toyCalorimeter()
{
  // media
  const TGeoMedium *medVac = gGeoManager->GetMedium("Vacuum");
  const TGeoMedium *medSci = gGeoManager->GetMedium("Scintillator");
  const TGeoMedium *medSte = gGeoManager->GetMedium("Steel");
  const TGeoMedium *medBra = gGeoManager->GetMedium("Brass");

}
