#ifndef sim005_h
#define sim005_h

vector<int> W(int ns, int nt, double N_s, double N_t, double nu, int alpha, double p_asym, double d){

    double N = N_s + N_t;

    vector<int> next = {ns,nt};

    // Prob. de div. asimétrica
    double pbar = p_asym*pow(1-(double)(nt)/N,alpha);

    // Definimos las probabilidades
    double p_S1 = (1/N)*nu*((double)(ns)/N)*((N_s-(double)(ns))/N_s)*pbar;
    double p_S2 = (1/N)*nu*((double)(ns)/N)*((N_t-(double)(nt))/N_t)*((N_t-(double)(nt)+1)/(N_t-1))*(1-pbar);
    double p_Td = (1/N)*((double)(nt)/N)*d;

    // Lanzamos la moneda
    double r;
    r = ((double) rand() / (RAND_MAX));

    // Escogemos el escenario
    if(r < p_S1){
        // División simétrica
        ++next[0];
    } 
    else if(r < (p_S1+p_S2)){
        // División asimétrica
        --next[0];
        next[1] = next[1]+2;
    }
    else if(r < (p_S1+p_S2+p_Td)){
        // Se muere una célula diferenciada
        --next[1]; 
    }
    else{
        // No pasa nada
    }

    return next;
}

//N_s,N_t,nu,d,p_asym,alpha = [8,12,1.0,0.0,0.5,2]
//1000 8 12 1 2 0.0 0.0 0.5 8 0 10

void experimento_5(int tiempo, double N_s, double N_t, double nu, int alpha, double p_asym, double d, int ns0, int nt0, int rep){
    
    double N = N_s + N_t;

    // Iniciamos donde guardamos nuestros datos
    vector<vector<int>> data_ns;
    vector<vector<int>> data_nt;
    
    // Corremos nuestras simulaciones
    for(int i=0;i<rep;i++){
        vector<int> simu_ns = {ns0};
        vector<int> simu_nt = {nt0};
        // Corremos el tiempo
        for(int t=0; t < tiempo; t++){
            vector<int> Sig = W(simu_ns[t],simu_nt[t], N_s, N_t, nu, alpha, p_asym, d);
            simu_ns.push_back(Sig[0]);
            simu_nt.push_back(Sig[1]);
        }
        data_ns.push_back(simu_ns);
        data_nt.push_back(simu_nt);
    }

    // Obtener por tiempo el avarage y el std. Y recuperarlo

    ofstream ns_info (path+"ns_info.py");
    ofstream nt_info (path+"nt_info.py");

    ns_info << "ns_info = [ ";
    nt_info << "nt_info = [ ";

    for(int t=0; t < tiempo; t++)
    {
        vector<int> column_time_s;
        vector<int> column_time_t;
        for(int n=0; n < rep; n++){
            column_time_s.push_back(data_ns[n][t]);
            column_time_t.push_back(data_nt[n][t]);
        }
        if(t==(tiempo-1)){
            ns_info << " ( " << avg(column_time_s) << " , " << standar_dev(column_time_s) << " ) ";
            nt_info << " ( " << avg(column_time_t) << " , " << standar_dev(column_time_t) << " ) ";
            ns_info << " ] ";
            nt_info << " ] ";
        }else{
            ns_info << "( " << avg(column_time_s) << " , " << standar_dev(column_time_s) << " ), ";
            nt_info << "( " << avg(column_time_t) << " , " << standar_dev(column_time_t) << " ), ";
        }

    }
    ns_info.close();
    nt_info.close();
}



#endif