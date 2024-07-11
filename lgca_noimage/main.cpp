
// Standar libraries
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <complex>
#include <cmath>

using namespace std;

const string path = "/home/muon02/Documents/Tesis/lgca_noimage/output/";

#include "wire/aux_func.h"
// lgca definition
#include "wire/node.h"
#include "wire/lgca.h"
// simulations of the thesis
#include "simulations/sim001.h"
#include "simulations/sim002.h"
#include "simulations/sim003.h"
#include "simulations/sim004.h"
#include "simulations/sim005.h"

/*int main(int argc, const char** args) {
    
    experimento_8();

    return 0;
}*/

int main(int argc, char** args){

    srand(315671513);

    int no_of_exp = atoi(args[1]);

    if (no_of_exp == 1)
    {
        experimento_1();
    }else if (no_of_exp == 2)
    {
        experimento_2();
    }else if (no_of_exp == 3)
    {
        experimento_3();
    }else if (no_of_exp == 4)
    {
        experimento_4();
    }else if (no_of_exp == 5)
    {
        int altura=atoi(args[2]); //height of the Lattice
        int bS=atoi(args[3]); 
        int bT=atoi(args[4]); 
        double nu=atof(args[5]);
        int alpha=atoi(args[6]); 
        double psym=atof(args[7]);
        double death=atof(args[8]);
        int time=atoi(args[9]);
        int rep=atoi(args[10]);
        int ns0=atoi(args[11]);
        int nt0=atoi(args[12]);
        experimento_5(time,bS,bT,nu,alpha,psym,death,ns0,nt0,rep);
    }else
    {
        cout<<"None expriment was done";
    }
    
    /*
    int altura=atoi(args[1]); //height of the Lattice
    int bS=atoi(args[2]); 
    int bT=atoi(args[3]); 
    double nu=atof(args[4]);
    int alpha=atoi(args[5]); 
    double psym=atof(args[6]);
    double death=atof(args[7]);
    int time=atoi(args[8]);
    int rep=atoi(args[9]);
    int ns0=atoi(args[10]);
    int nt0=atoi(args[11]);
    */
    /*
    LGCA mundo = LGCA(altura, time+4, bS, bT, nu, alpha, psym, death);
    mundo.putstrip();
    mundo.walk_uni(time);
    */
    /*LGCA mundo = LGCA(altura, time+4, bS, bT, nu, alpha, psym, death);
    mundo.putstrip();
    mundo.walk(1);
    mundo.get_ydata();
    */
    //experimento_1();
    //experimento_2();
    //experimento_3();
    //experimento_4();
    //experimento_5(time,bS,bT,nu,alpha,psym,death,ns0,nt0,rep);
    /*
    int altura=atoi(args[1]); //height of the Lattice
    int bS=atoi(args[2]); 
    int bT=atoi(args[3]); 
    double nu=atof(args[4]);
    int alpha=atoi(args[5]); 
    double psym=atof(args[6]);
    double death=atof(args[7]);
    int time=atoi(args[8]); 

    LGCA mundo = LGCA(altura, time+4, bS, bT, nu, alpha, psym, death);
    mundo.putstrip();
    mundo.walk(time);
    */
}

