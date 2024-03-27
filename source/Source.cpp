#include "Simulation.h"


int main() {
	srand(time(NULL));
	
	Simulation sim;
	
	

	while (sim.isWindowOpen()) {

		
		
		sim.pullEvents();


		sim.update();


		sim.render();

		
	}







	





}




