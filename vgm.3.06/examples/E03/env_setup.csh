# $Id: env_setup.csh 700 2011-12-09 15:09:01Z ihrivnac $
# The environment setting for the E01 example 
#
# by I. Hrivnacova, IPN Orsay

# set Geant4 environment for building example via GNU Make 
if ( "`which geant4-config >& /dev/null`" != "" ) then
  source "`geant4-config --prefix`"/share/Geant4-"`geant4-config --version`"/geant4make/geant4make.csh         
endif

setenv G4WORKDIR `pwd`/N03
setenv PATH ${G4WORKDIR}/bin/${G4SYSTEM}:${PATH}
setenv LD_LIBRARY_PATH ${G4WORKDIR}/tmp/${G4SYSTEM}/exampleN03:${LD_LIBRARY_PATH}
rehash
