

#ifndef sim003_h
#define sim003_h

void experimento_3(){
    int altura=1000; //height of the Lattice //WARNINGG: ORI 1000
    double nu=0.8;

    int Time = 3000; //WARNINGG: ORI 3000
    float psym = 0.5;
    float death = 0.5;
    int alpha = 2;
    
    int rep = 15;
    
    int bT = 4; //a:16, b:4 
    vector<int> vecbS = {4,8,12,16,20,24}; //Trait variables

    // Register of information for bs=bt vs front(s) position(s) graphs
    
    vector<float> mean_front_95(vecbS.size(),0); 
    vector<float> sd_front_95(vecbS.size(),0); 

    vector<float> mean_front_95CSC(vecbS.size(),0); 
    vector<float> sd_front_95CSC(vecbS.size(),0); 

    vector<float> mean_front_95TD(vecbS.size(),0);
    vector<float> sd_front_95TD(vecbS.size(),0); 

    vector<float> mean_front_Naive(vecbS.size(),0); 
    vector<float> sd_front_Naive(vecbS.size(),0); 

    vector<float> mean_front_NaiveCSC(vecbS.size(),0); 
    vector<float> sd_front_NaiveCSC(vecbS.size(),0); 

    vector<float> mean_front_NaiveTD(vecbS.size(),0);
    vector<float> sd_front_NaiveTD(vecbS.size(),0); 

    vector<float> mean_front_zeros(vecbS.size(),0); 
    vector<float> sd_front_zeros(vecbS.size(),0); 

    vector<float> mean_front_zerosCSC(vecbS.size(),0); 
    vector<float> sd_front_zerosCSC(vecbS.size(),0); 

    vector<float> mean_front_zerosTD(vecbS.size(),0);
    vector<float> sd_front_zerosTD(vecbS.size(),0); 

    // Register of information for bs=bt vs front(s) form(s) graphs (dom mode)

    vector<float> mean_dom_mode_95(vecbS.size(),0); 
    vector<float> sd_dom_mode_95(vecbS.size(),0); 

    vector<float> mean_dom_mode_95CSC(vecbS.size(),0); 
    vector<float> sd_dom_mode_95CSC(vecbS.size(),0); 

    vector<float> mean_dom_mode_95TD(vecbS.size(),0);
    vector<float> sd_dom_mode_95TD(vecbS.size(),0); 

    vector<float> mean_dom_mode_zeros(vecbS.size(),0); 
    vector<float> sd_dom_mode_zeros(vecbS.size(),0); 

    vector<float> mean_dom_mode_zerosCSC(vecbS.size(),0); 
    vector<float> sd_dom_mode_zerosCSC(vecbS.size(),0); 

    vector<float> mean_dom_mode_zerosTD(vecbS.size(),0);
    vector<float> sd_dom_mode_zerosTD(vecbS.size(),0); 

    // Register of information for bs=bt vs front(s) form(s) graphs (leght of polygonal)

    vector<float> mean_leght_poly_95(vecbS.size(),0); 
    vector<float> sd_leght_poly_95(vecbS.size(),0); 

    vector<float> mean_leght_poly_95CSC(vecbS.size(),0); 
    vector<float> sd_leght_poly_95CSC(vecbS.size(),0); 

    vector<float> mean_leght_poly_95TD(vecbS.size(),0);
    vector<float> sd_leght_poly_95TD(vecbS.size(),0); 

    vector<float> mean_leght_poly_zeros(vecbS.size(),0); 
    vector<float> sd_leght_poly_zeros(vecbS.size(),0); 

    vector<float> mean_leght_poly_zerosCSC(vecbS.size(),0); 
    vector<float> sd_leght_poly_zerosCSC(vecbS.size(),0); 

    vector<float> mean_leght_poly_zerosTD(vecbS.size(),0);
    vector<float> sd_leght_poly_zerosTD(vecbS.size(),0); 
    
    //Simulation
    
    for(int j = 0; j < vecbS.size(); j++){
        vector<float> record_mean_95(rep,0);
        vector<float> record_mean_95CSC(rep,0);
        vector<float> record_mean_95TD(rep,0);

        vector<float> record_mean_Naive(rep,0);
        vector<float> record_mean_NaiveCSC(rep,0);
        vector<float> record_mean_NaiveTD(rep,0);

        vector<float> record_mean_zeros(rep,0);
        vector<float> record_mean_zerosCSC(rep,0);
        vector<float> record_mean_zerosTD(rep,0);

        vector<float> record_dom_mode_95(rep,0);
        vector<float> record_dom_mode_95CSC(rep,0);
        vector<float> record_dom_mode_95TD(rep,0);

        vector<float> record_dom_mode_zeros(rep,0);
        vector<float> record_dom_mode_zerosCSC(rep,0);
        vector<float> record_dom_mode_zerosTD(rep,0);


        vector<float> record_leght_poly_95(rep,0);
        vector<float> record_leght_poly_95CSC(rep,0);
        vector<float> record_leght_poly_95TD(rep,0);

        vector<float> record_leght_poly_zeros(rep,0);
        vector<float> record_leght_poly_zerosCSC(rep,0);
        vector<float> record_leght_poly_zerosTD(rep,0);

        //Simulation

        ofstream data_info_fronts (path+"sim003/b_fronts.py", ios_base::app);
        ofstream data_info_frontsCSC (path+"sim003/b_frontsCSC.py", ios_base::app);
        ofstream data_info_frontsTD (path+"sim003/b_frontsTD.py", ios_base::app);
        
        for(int k = 0; k < rep; k++){
            LGCA mundo = LGCA(altura, 50, vecbS[j], bT, nu, alpha, psym, death);
            mundo.putstrip();
            mundo.walk(Time);
            mundo.draw_line();

            //To draw the homogenity
            mundo.limit_frontier();
            data_info_fronts << "bS_" << to_string(vecbS[j]) << "_rep_" << k << "=[ ";
            data_info_frontsCSC << "bS_" << to_string(vecbS[j]) << "_rep_" << k << "CSC=[ ";
            data_info_frontsTD << "bS_" << to_string(vecbS[j]) << "_rep_" << k << "TD=[ ";
            for(int x = mundo.left_front; x <= mundo.right_front; x++){ //Visit form left frontier to right frontier
                int density_column = 0;
                int density_columnCSC = 0;
                int density_columnTD = 0;
                for(int y=0; y < mundo.height; y++){ //Visit top to buttom
                    density_column += mundo.Lattice[y][x].density();
                    density_columnCSC += mundo.Lattice[y][x].densityS();
                    density_columnTD += mundo.Lattice[y][x].densityT();
                }
                if(x==mundo.right_front){
                    data_info_fronts << to_string(density_column) + " ]" << endl;
                    data_info_frontsCSC << to_string(density_columnCSC) + " ]" << endl;
                    data_info_frontsTD << to_string(density_columnTD) + " ]" << endl;
                }else{
                    data_info_fronts << to_string(density_column) + " ,";
                    data_info_frontsCSC << to_string(density_columnCSC) + " ,";
                    data_info_frontsTD << to_string(density_columnTD) + " ,";
                }
            }
            data_info_fronts << endl;

            //To draw the homogenity

            record_mean_95[k] = avg(mundo.front);
            record_mean_95CSC[k] = avg(mundo.frontCSC);
            record_mean_95TD[k] = avg(mundo.frontTD);

            record_mean_Naive[k] = mundo.front_Naive;
            record_mean_NaiveCSC[k] = mundo.front_NaiveCSC;
            record_mean_NaiveTD[k] = mundo.front_NaiveTD;

            record_mean_zeros[k] = avg(mundo.front_zero);
            record_mean_zerosCSC[k] = avg(mundo.front_zeroCSC);
            record_mean_zerosTD[k] = avg(mundo.front_zeroTD);


            record_dom_mode_95[k] = dom_mode(mundo.front);
            record_dom_mode_95CSC[k] = dom_mode(mundo.frontCSC);
            record_dom_mode_95TD[k] = dom_mode(mundo.frontTD);
            
            record_dom_mode_zeros[k] = dom_mode(mundo.front_zero);
            record_dom_mode_zerosCSC[k] = dom_mode(mundo.front_zeroCSC);
            record_dom_mode_zerosTD[k] = dom_mode(mundo.front_zeroTD);


            record_leght_poly_95[k] = long_curv(mundo.front);
            record_leght_poly_95CSC[k] = long_curv(mundo.front);
            record_leght_poly_95TD[k] = long_curv(mundo.front);

            record_leght_poly_zeros[k] = long_curv(mundo.front_zero);
            record_leght_poly_zerosCSC[k] = long_curv(mundo.front_zeroCSC);
            record_leght_poly_zerosTD[k] = long_curv(mundo.front_zeroTD);
        }

        // Register of information for bs=bt vs front(s) position(s) graphs
    
    mean_front_95[j]=avg(record_mean_95); 
    sd_front_95[j]=standar_dev(record_mean_95); 

    mean_front_95CSC[j]=avg(record_mean_95CSC); 
    sd_front_95CSC[j]=standar_dev(record_mean_95CSC); 

    mean_front_95TD[j]=avg(record_mean_95TD);
    sd_front_95TD[j]=standar_dev(record_mean_95TD); 

    mean_front_Naive[j]=avg(record_mean_Naive); 
    sd_front_Naive[j]=standar_dev(record_mean_Naive); 

    mean_front_NaiveCSC[j]=avg(record_mean_NaiveCSC); 
    sd_front_NaiveCSC[j]=standar_dev(record_mean_NaiveCSC); 

    mean_front_NaiveTD[j]=avg(record_mean_NaiveTD);
    sd_front_NaiveTD[j]=standar_dev(record_mean_NaiveTD); 

    mean_front_zeros[j]=avg(record_mean_zeros); 
    sd_front_zeros[j]=standar_dev(record_mean_zeros); 

    mean_front_zerosCSC[j]=avg(record_mean_zerosCSC); 
    sd_front_zerosCSC[j]=standar_dev(record_mean_zerosCSC); 

    mean_front_zerosTD[j]=avg(record_mean_zerosTD);
    sd_front_zerosTD[j]=standar_dev(record_mean_zerosTD); 

    // Register of information for bs=bt vs front(s) form(s) graphs (dom mode)

    mean_dom_mode_95[j]=avg(record_dom_mode_95); 
    sd_dom_mode_95[j]=standar_dev(record_dom_mode_95); 

    mean_dom_mode_95CSC[j]=avg(record_dom_mode_95CSC); 
    sd_dom_mode_95CSC[j]=standar_dev(record_dom_mode_95CSC); 

    mean_dom_mode_95TD[j]=avg(record_dom_mode_95TD);
    sd_dom_mode_95TD[j]=standar_dev(record_dom_mode_95TD); 

    mean_dom_mode_zeros[j]=avg(record_dom_mode_zeros); 
    sd_dom_mode_zeros[j]=standar_dev(record_dom_mode_zeros); 

    mean_dom_mode_zerosCSC[j]=avg(record_dom_mode_zerosCSC); 
    sd_dom_mode_zerosCSC[j]=standar_dev(record_dom_mode_zerosCSC); 

    mean_dom_mode_zerosTD[j]=avg(record_dom_mode_zerosTD);
    sd_dom_mode_zerosTD[j]=standar_dev(record_dom_mode_zerosTD); 

    // Register of information for bs=bt vs front(s) form(s) graphs (leght of polygonal)

    mean_leght_poly_95[j]=avg(record_leght_poly_95); 
    sd_leght_poly_95[j]=standar_dev(record_leght_poly_95); 

    mean_leght_poly_95CSC[j]=avg(record_leght_poly_95CSC); 
    sd_leght_poly_95CSC[j]=standar_dev(record_leght_poly_95CSC); 

    mean_leght_poly_95TD[j]=avg(record_leght_poly_95TD);
    sd_leght_poly_95TD[j]=standar_dev(record_leght_poly_95TD); 

    mean_leght_poly_zeros[j]=avg(record_leght_poly_zeros); 
    sd_leght_poly_zeros[j]=standar_dev(record_leght_poly_zeros); 

    mean_leght_poly_zerosCSC[j]=avg(record_leght_poly_zerosCSC); 
    sd_leght_poly_zerosCSC[j]=standar_dev(record_leght_poly_zerosCSC); 

    mean_leght_poly_zerosTD[j]=avg(record_leght_poly_zerosTD);
    sd_leght_poly_zerosTD[j]=standar_dev(record_leght_poly_zerosTD); 
        }
    
    //Publish of results
    
    ofstream data_info (path+"sim003/sim003b.py", ios_base::app);

    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_front_95 = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_front_95[i] << ",";
    }
    data_info << mean_front_95[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_front_95 = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_front_95[i] << ",";
    }
    data_info << sd_front_95[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_front_95CSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_front_95CSC[i] << ",";
    }
    data_info << mean_front_95CSC[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_front_95CSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_front_95CSC[i] << ",";
    }
    data_info << sd_front_95CSC[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_front_95TD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_front_95TD[i] << ",";
    }
    data_info << mean_front_95TD[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_front_95TD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_front_95TD[i] << ",";
    }
    data_info << sd_front_95TD[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

    //*********************************************************

    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_front_Naive = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_front_Naive[i] << ",";
    }
    data_info << mean_front_Naive[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_front_Naive = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_front_Naive[i] << ",";
    }
    data_info << sd_front_Naive[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_front_NaiveCSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_front_NaiveCSC[i] << ",";
    }
    data_info << mean_front_NaiveCSC[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_front_NaiveCSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_front_NaiveCSC[i] << ",";
    }
    data_info << sd_front_NaiveCSC[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_front_NaiveTD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_front_NaiveTD[i] << ",";
    }
    data_info << mean_front_NaiveTD[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_front_NaiveTD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_front_NaiveTD[i] << ",";
    }
    data_info << sd_front_NaiveTD[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//*********************************************************

    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_front_zeros = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_front_zeros[i] << ",";
    }
    data_info << mean_front_zeros[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_front_zeros = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_front_zeros[i] << ",";
    }
    data_info << sd_front_zeros[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_front_zerosCSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_front_zerosCSC[i] << ",";
    }
    data_info << mean_front_zerosCSC[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_front_zerosCSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_front_zerosCSC[i] << ",";
    }
    data_info << sd_front_zerosCSC[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_front_zerosTD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_front_zerosTD[i] << ",";
    }
    data_info << mean_front_zerosTD[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_front_zerosTD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_front_zerosTD[i] << ",";
    }
    data_info << sd_front_zerosTD[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//*********************************************************
//*********************************************************
//*********************************************************


    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_dom_mode_95 = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_dom_mode_95[i] << ",";
    }
    data_info << mean_dom_mode_95[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_dom_mode_95 = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_dom_mode_95[i] << ",";
    }
    data_info << sd_dom_mode_95[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_dom_mode_95CSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_dom_mode_95CSC[i] << ",";
    }
    data_info << mean_dom_mode_95CSC[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_dom_mode_95CSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_dom_mode_95CSC[i] << ",";
    }
    data_info << sd_dom_mode_95CSC[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_dom_mode_95TD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_dom_mode_95TD[i] << ",";
    }
    data_info << mean_dom_mode_95TD[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_dom_mode_95TD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_dom_mode_95TD[i] << ",";
    }
    data_info << sd_dom_mode_95TD[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

    //*********************************************************

    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_dom_mode_zeros = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_dom_mode_zeros[i] << ",";
    }
    data_info << mean_dom_mode_zeros[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_dom_mode_zeros = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_dom_mode_zeros[i] << ",";
    }
    data_info << sd_dom_mode_zeros[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_dom_mode_zerosCSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_dom_mode_zerosCSC[i] << ",";
    }
    data_info << mean_dom_mode_zerosCSC[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_dom_mode_zerosCSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_dom_mode_zerosCSC[i] << ",";
    }
    data_info << sd_dom_mode_zerosCSC[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_dom_mode_zerosTD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_dom_mode_zerosTD[i] << ",";
    }
    data_info << mean_dom_mode_zerosTD[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_dom_mode_zerosTD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_dom_mode_zerosTD[i] << ",";
    }
    data_info << sd_dom_mode_zerosTD[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//*********************************************************
//*********************************************************
//*********************************************************

    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_leght_poly_95 = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_leght_poly_95[i] << ",";
    }
    data_info << mean_leght_poly_95[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_leght_poly_95 = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_leght_poly_95[i] << ",";
    }
    data_info << sd_leght_poly_95[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_leght_poly_95CSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_leght_poly_95CSC[i] << ",";
    }
    data_info << mean_leght_poly_95CSC[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_leght_poly_95CSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_leght_poly_95CSC[i] << ",";
    }
    data_info << sd_leght_poly_95CSC[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_leght_poly_95TD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_leght_poly_95TD[i] << ",";
    }
    data_info << mean_leght_poly_95TD[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_leght_poly_95TD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_leght_poly_95TD[i] << ",";
    }
    data_info << sd_leght_poly_95TD[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

    //*********************************************************

    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_leght_poly_zeros = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_leght_poly_zeros[i] << ",";
    }
    data_info << mean_leght_poly_zeros[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_leght_poly_zeros = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_leght_poly_zeros[i] << ",";
    }
    data_info << sd_leght_poly_zeros[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_leght_poly_zerosCSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_leght_poly_zerosCSC[i] << ",";
    }
    data_info << mean_leght_poly_zerosCSC[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_leght_poly_zerosCSC = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_leght_poly_zerosCSC[i] << ",";
    }
    data_info << sd_leght_poly_zerosCSC[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    data_info << "mean_leght_poly_zerosTD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << mean_leght_poly_zerosTD[i] << ",";
    }
    data_info << mean_leght_poly_zerosTD[vecbS.size()-1] << " ]" <<endl;

    data_info << "sd_leght_poly_zerosTD = [ ";
    for (int i = 0; i < vecbS.size()-1; i++)
    {
        data_info << sd_leght_poly_zerosTD[i] << ",";
    }
    data_info << sd_leght_poly_zerosTD[vecbS.size()-1] << " ]" <<endl;
    //-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
}

#endif /* sim003_h */

