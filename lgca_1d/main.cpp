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

	int largo=atoi(args[1]);
    int bS=atoi(args[2]); 
    int bT=atoi(args[3]); 
    double nu=atof(args[4]);
    int alpha=atoi(args[5]); 
    double psym=atof(args[6]);
    double death=atof(args[7]);
    int time=atoi(args[8]);
    /*int rep=atoi(args[10]);
    int ns0=atoi(args[11]);
    int nt0=atoi(args[12]);
	*/
	LGCA_uni Mundo = LGCA_uni(largo, bS, bT, nu, alpha, psym, death);
    Mundo.putstrip();
    Mundo.walk(time);
    
    return 0;
}
