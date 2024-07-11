#ifndef node_h
#define node_h

class Node{
public:
    // Definimos el nodo con celulas tipo S
    int ncellS = 0; //No. de celulas
    //Indicamos que canales están ocupados con un 1, y cuales no con un 0.
    int leftS = 0;
    int upS = 0;
    int rightS = 0;
    int downS = 0;

    // Definimos el nodo con celulas tipo T
    int ncellT = 0; //No. de celulas
    //Indicamos que canales están ocupados con un 1, y cuales no con un 0.
    int leftT = 0;
    int upT = 0;
    int rightT = 0;
    int downT = 0;

    Node()
    {

    }
    
    void R(int chS, int chT, double nu, int alpha, double pT, double d)
    {
        //Funcion de reaccion (muerte y crecimiento de celulas S-T)

    double N_s = (double) chS; //Canales totales
    double N_t = (double) chT; //Canales totales
    double N = min(N_s,N_t);
    double p_asym = pT;

    double ns = (double) ncellS; //Canales ocupados
    double nt = (double) ncellT; //Canales ocupados


    // Prob. de div. asimétrica
    double pbar = p_asym*pow(1-nt/N,alpha);

    // Definimos las probabilidades
    double p_S1 = (ns<=N)*(1/N)*nu*(ns/N)*((N-ns)/N)*pbar;
            p_S1 = p_S1*(p_S1>0);
                // † proba positiva
    double p_S2 = (nt<=(N-1))*(1/N)*nu*(ns/N)*((N-nt)/N)*((N-nt-1)/(N-1))*(1-pbar);
            p_S2 = p_S2*(p_S2>0);
                // † proba positiva
    double p_Td = (1/N)*(nt/N)*d;

    // Lanzamos la moneda
    double r;
    r = ((double) rand() / (RAND_MAX));

    // Escogemos el escenario
    if(r < p_S1){
        // División simétrica
        ++ncellS;
    }
    else if(r < (p_S1+p_S2)){
        // División asimétrica
        --ncellS;
        ++ncellT;
        ++ncellT;
    }
    else if(r < (p_S1+p_S2+p_Td)){
        // Se muere una célula diferenciada
        --ncellT;
    }
    else{
        // No pasa nada
    }
    }
        
    
    
    void O(int chS, int chT)
    {
    //Code for random
    double p;
    
    int spaces,bullets,bag;
    
    //Code for S cells---------------------------
    
    //Decide which r going to velocity channels(bag) or to rest channels
    spaces = chS;
    bullets = ncellS;
    bag = 0;
    
    while ((bag != 4)&&(bullets != 0))
    {
        p = ((double) rand() / (RAND_MAX));
        if (p < ((double) (4-bag)/spaces)) ++bag;
        --spaces;
        --bullets;
    }
    
    // Decide which velocity channels are going to be taken
    leftS=0;
    rightS=0;
    upS=0;
    downS=0;
    
    p = ((double) rand() / (RAND_MAX));
    if(p < (double)bag/4 )  leftS = 1;
    p = ((double) rand() / (RAND_MAX));
    if(p < (double)(bag-leftS)/3 )  upS = 1;
    p = ((double) rand() / (RAND_MAX));
    if(p < (double)(bag-leftS-upS)/2 )  rightS = 1;
    p = ((double) rand() / (RAND_MAX));
    if(p < (double)(bag-leftS-upS-rightS) )  downS = 1;

    
    //Code for T cells---------------------------
    
    //Decide which r going to velocity channels(bag) or to rest channels
    spaces = chT;
    bullets = ncellT;
    bag = 0;
    
    while ((bag != 4)&&(bullets != 0))
    {
        p = ((double) rand() / (RAND_MAX));
        if (p < ((double) (4-bag)/spaces)) ++bag;
        --spaces;
        --bullets;
    }

    // Decide which velocity channels are going to be taken
    leftT=0;
    rightT=0;
    upT=0;
    downT=0;
    
    p = ((double) rand() / (RAND_MAX));
    if(p < (double)bag/4 ){
        leftT = 1;
    }
    p = ((double) rand() / (RAND_MAX));
    if(p < (double)(bag-leftT)/3 ){
        upT = 1;
    }
    p = ((double) rand() / (RAND_MAX));
    if(p < (double)(bag-leftT-upT)/2 ){
        rightT = 1;
    }
    p = ((double) rand() / (RAND_MAX));
    if(p < (double)(bag-leftT-upT-rightT) ){
        downT = 1;
    }
    }
    
    
    void P(Node nL, Node nU, Node nR, Node nD)
    {
    //La migracion se caracteriza por flujo entrante menos saliente
        int InS = nL.rightS +  nU.downS + nR.leftS + nD.upS;
        int OutS = rightS +  downS + leftS + upS;
        ncellS += InS - OutS;
    
        int InT = nL.rightT +  nU.downT + nR.leftT + nD.upT;
        int OutT = rightT +  downT + leftT + upT;
        ncellT += InT - OutT;
    }
    
    void Pbound( Node nU, Node nR, Node nD)
    {
        int InS =  nU.downS + nR.leftS + nD.upS;
        int OutS = downS + leftS + upS;
        ncellS += InS - OutS;
    
        int InT = nU.downT + nR.leftT + nD.upT;
        int OutT = downT + leftT + upT;
        ncellT += InT - OutT;
    }
    
    void OR(int chS, int chT, double nu, int alpha, double pT, double d)
    {
        //La transicion de tiempo se caracteriza por la aplicacion POR
        R(chS, chT, nu, alpha, pT, d);
        O(chS, chT);
    }
    
    void inicializar(int chS)
    {
        //Pone de 0 a Capacidad maxima-1 de celulas aleatoriamente
        ncellS = chS;
    }

    int density()
    {
        //Devuelve el no. de celulas totales
        return (ncellS + ncellT);
    }
    int densityS()
    {
        //Devuelve el no. de celulas CSC
        return ncellS;
    }

    int densityT()
    {
        //Devuelve el no. de celulas DCC
        return ncellT;
    }

    int densitySrest()
    {
        //Devuelve el no. de celulas CSC
        return ncellS - (rightS +  downS + leftS + upS);
    }

    int densityTrest()
    {
        //Devuelve el no. de celulas DCC
        return ncellT - (rightT +  downT + leftT + upT);
    }
};

#endif /* node_h */