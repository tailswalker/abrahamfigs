// std includes
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <complex>
#include <cmath>
#include <algorithm>

using namespace std;

// OpenCV includes

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

// Miscellanius functions
#include "wire/aux_func.h"

// LGCA code
#include "wire/node.h"
#include "wire/lgca.h"


int main(int argc, const char** args) {
	srand(315671513);

	int altura=atoi(args[1]); //height of the Lattice
	int largo=atoi(args[2]);
    int bS=atoi(args[3]); 
    int bT=atoi(args[4]); 
    double nu=atof(args[5]);
    int alpha=atoi(args[6]); 
    double psym=atof(args[7]);
    double death=atof(args[8]);
    int time=atoi(args[9]);
    /*int rep=atoi(args[10]);
    int ns0=atoi(args[11]);
    int nt0=atoi(args[12]);
	*/
	LGCA Mundo = LGCA(altura, largo, bS, bT, nu, alpha, psym, death);
    Mundo.putstrip();
    Mundo.take_live_chS(time);
    
    return 0;
}
