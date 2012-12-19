
#include "CleaverMeshDumper.h"

#include <CompuCell3D/Simulator.h>
using namespace CompuCell3D;

#include <BasicUtils/BasicPluginProxy.h>

BasicPluginProxy<Steppable, CleaverMeshDumper> 
cleaverMeshDumperProxy("CleaverMeshDumper", "Autogenerated steppeble - the author of the plugin should provide brief description here",
	    &Simulator::steppableManager);        
