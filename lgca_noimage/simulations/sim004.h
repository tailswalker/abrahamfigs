
#ifndef sim004_h
#define sim004_h

void experimento_4(){
    int altura=1000; //height of the Lattice
    double nu=1;

    int Time = 1000;
    float psym = 0.7;
    float death = 0.5;
    int alpha = 2;
    
    vector<int> vecbT = {4,6,8,4,6,8,4,6,8};
    vector<int> vecbS = {4,4,4,6,6,6,8,8,8};

    for(int j=0; j < vecbS.size(); j++){
        LGCA mundo = LGCA(altura, Time+15, vecbS[j], vecbT[j], nu, alpha, psym, death);
        mundo.putstrip();
        for(int t = 0; t < Time; t++){
            mundo.walk(1);
            mundo.get_ydata("sim004/");
        }
    }
}



#endif