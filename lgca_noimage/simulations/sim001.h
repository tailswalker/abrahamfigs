

#ifndef sim001_h
#define sim001_h

void experimento_1(){
    int altura=1000; //height of the Lattice //WARNINGGGG: original is 1000
    double nu=1;

    int Time = 3000; //WARNINGGGG: original is 3000
                    //Arti 15000
    float psym = 0.7;
    float death = 0.05;
    int alpha = 3;
    
    int rep = 15;
    
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

        for(int k = 0; k < rep; k++){
            LGCA mundo = LGCA(altura, 50, vecbS[j], vecbS[j], nu, alpha, psym, death);
            mundo.putstrip();
            mundo.walk(Time);
            mundo.draw_line();

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
            record_leght_poly_95CSC[k] = long_curv(mundo.frontCSC);
            record_leght_poly_95TD[k] = long_curv(mundo.frontTD);

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
    
    ofstream data_info (path+"sim001/sim001.py", ios_base::app);

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

#endif /* sim001_h */

