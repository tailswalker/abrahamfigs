//
//  lgca.h
//  lgca-feedback
//
//  Created by Muon02 on 4/12/21.
//  Copyright © 2021 Muon02. All rights reserved.
//

#ifndef lgca_h
#define lgca_h


class LGCA
{
public:
    vector<vector<Node> > Lattice;
    vector<int> front, frontCSC, frontTD;
    int front_Naive, front_NaiveCSC, front_NaiveTD;
    vector<int> front_zero, front_zeroCSC, front_zeroTD;
    int left_front;
    int right_front;
    int Time = 0;
    int height;
    int width;
    int N;
    vector<int> bulk;

    //Node parameters
    int chS;
    int chT;
    double nu;
    int alpha;
    double pT;
    double d;
    
    LGCA(int alto, int largo, int bS, int bT, double v, int a, double p, double death)
    {
        height = alto;
        width = largo;
        chS = bS;
        chT = bT;
        N = bS +bT;
        nu = v;
        alpha = a;
        pT = p;
        d = death;

        for (int i = 0; i < alto; i++)
        {
            vector<Node> temp;
            for (int j = 0; j < largo; j++)
            {
                temp.push_back(Node());
            }
            Lattice.push_back(temp);
        }
        front.resize(height, 4);
        frontCSC.resize(height, 4);
        frontTD.resize(height, 4);
        front_zero.resize(height, 4);
        front_zeroCSC.resize(height, 4);
        front_zeroTD.resize(height, 4);
    }
    
    void putstrip()
    {
    for(int i=0; i<height; i++)
    {
        for(int j=0; j < 4; j++)
        {
            Lattice[i][j].inicializar(chS);
        }
    }
    }
    
    bool isbig()
    {
        for(int i=0; i<height; i++)
        {
            if((bool)(Lattice[i][width-3].ncellS + Lattice[i][width-3].ncellT))
            {
            return 0;
            }
        }
        return 1;
    }
    
    void makebig()
    {
        width += 5;
        for(int j=0; j<height; j++)
        {
            for(int k = 0; k<5; k++)
            {
                Lattice[j].push_back(Node());
            }
        }
    }
    
    void step()
    {
    // Applying Reproduction and orientation over the whole Lattice
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width-2); j++)
        {
            Lattice[i][j].OR(chS, chT, nu, alpha, pT, d);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width-2); j++)
        {
            if(j==0)
            {
                if(i==0)
                    Lattice[i][j].Pbound(Lattice[height-1][j], Lattice[i][j+1], Lattice[i+1][j]);
                else if(i== (height-1))
                    Lattice[i][j].Pbound(Lattice[i-1][j],Lattice[i][j+1],Lattice[0][j]);
                else
                    Lattice[i][j].Pbound(Lattice[i-1][j],Lattice[i][j+1],Lattice[i+1][j]);
            }
            else
            {
                if(i==0)
                    Lattice[i][j].P(Lattice[i][j-1], Lattice[height-1][j], Lattice[i][j+1], Lattice[i+1][j]);
                else if(i== (height-1))
                    Lattice[i][j].P(Lattice[i][j-1],Lattice[i-1][j],Lattice[i][j+1],Lattice[0][j]);
                else
                    Lattice[i][j].P(Lattice[i][j-1],Lattice[i-1][j],Lattice[i][j+1],Lattice[i+1][j]);
            }
        }
    }
    }
    
    void walk(int t)
    {
        for(int k=0; k<t; k++)
        {
            if(!(isbig())) makebig();
            Time++;
            step();
        }
    }

    void get_ydata(string capeta_extra  = ""){
        ofstream data_info (path+capeta_extra+"ydata.csv", ios_base::app);
        ofstream data_infoS (path+capeta_extra+"ydataCSC.csv", ios_base::app);
        ofstream data_infoT (path+capeta_extra+"ydataTD.csv", ios_base::app);
            for(int y=0; y<width;y++){
                int sumS = 0;
                int sumT = 0;
                for(int x=0;x<height;x++){
                    sumS += Lattice[x][y].densityS();
                    sumT += Lattice[x][y].densityT();
                }
            data_info << (sumS+sumT)<< " ";
            data_infoS << sumS<< " ";
            data_infoT << sumT<< " ";
            }
            data_info << endl;
            data_infoS << endl;
            data_infoT << endl;
    }
            

    void draw_line(){
        front_NaiveCSC=0;
        front_NaiveTD=0;
        for(int x=0;x<height;x++){
            int sumS = 0;
            int sumT = 0;
            vector<int> Ccell;
            vector<int> CcellS;
            vector<int> CcellT;
            int dS = 0;
            int dT = 0;
            int flag_zeroCSC = 0; //line for zero approche
            int flag_zeroTD = 0; //line for zero approche
            for(int y=0; y<width; y++){
                dS = Lattice[x][y].densityS();
                dT = Lattice[x][y].densityT();
                sumS += dS;
                sumT += dT;
                Ccell.push_back(sumS+sumT);
                CcellS.push_back(sumS);
                CcellT.push_back(sumT);
                //Init lines for Naive approche and zero approche
                if(dS != 0){
                    if(y >= front_NaiveCSC){
                        front_NaiveCSC = y;
                    }
                }else if (flag_zeroCSC==0){
                    front_zeroCSC[x] = y;
                    flag_zeroCSC=1;
                }
                if(dT != 0){
                    if( y >= front_NaiveTD){
                        front_NaiveTD = y;
                    }
                }else if (flag_zeroTD==0){
                    front_zeroTD[x] = y;
                    flag_zeroTD=1;
                }
                    //End lines for Naive approche and zero approche
            }
            front_Naive = max(front_NaiveCSC,front_NaiveTD); //line for Naive approche
            front_zero[x] = min(front_zeroCSC[x],front_zeroTD[x]); //line for zero approche
            int frontx=0;
            while(Ccell[frontx] < (0.95)*((double) (sumS+sumT))){frontx++;}
            
            int frontxS=0;
            while(CcellS[frontxS] < (0.95)*((double) (sumS))){frontxS++;}
            
            int frontxT=0;
            while(CcellT[frontxT] < (0.95)*((double) (sumT))){frontxT++;}
            
            front[x]=frontx;
            frontCSC[x]=frontxS;
            frontTD[x]=frontxT;
            }
    }

    void draw_line_95(){
            for(int x=0;x<height;x++){
                int sumS = 0;
                int sumT = 0;
                vector<int> Ccell;
                vector<int> CcellS;
                vector<int> CcellT;
                int dS = 0;
                int dT = 0;
                for(int y=0; y<width; y++){
                    dS = Lattice[x][y].densityS();
                    dT = Lattice[x][y].densityT();
                    sumS += dS;
                    sumT += dT;
                    Ccell.push_back(sumS+sumT);
                    CcellS.push_back(sumS);
                    CcellT.push_back(sumT);
                }
                int frontx=0;
                while(Ccell[frontx] < (0.95)*((double) (sumS+sumT))){frontx++;}
                int frontxS=0;
                while(CcellS[frontxS] < (0.95)*((double) (sumS))){frontxS++;}
                int frontxT=0;
                while(CcellT[frontxT] < (0.95)*((double) (sumT))){frontxT++;}
                front[x]=frontx;
                frontCSC[x]=frontxS;
                frontTD[x]=frontxT;
            }
    }

    void draw_line_Naive(){
            for(int x=0;x<height;x++){
                int dS = 0;
                int dT = 0;
                int flag_zeroCSC = 0; //line for zero approche
                int flag_zeroTD = 0; //line for zero approche
                for(int y=0; y<width; y++){
                    dS = Lattice[x][y].densityS();
                    dT = Lattice[x][y].densityT();
                    //Init lines for Naive approche and zero approche
                    if(dS != 0){
                        front_NaiveCSC = y;
                    }
                    if(dT != 0){
                        front_NaiveTD = y;
                    }
                    //End lines for Naive approche and zero approche
                }
                front_Naive = max(front_NaiveCSC,front_NaiveTD); //line for Naive approche
            }
    }

    void draw_line_zeros(){
            for(int x=0;x<height;x++){
                int sumS = 0;
                int sumT = 0;
                vector<int> Ccell;
                vector<int> CcellS;
                vector<int> CcellT;
                int dS = 0;
                int dT = 0;
                int flag_zeroCSC = 0; //line for zero approche
                int flag_zeroTD = 0; //line for zero approche
                for(int y=0; y<width; y++){
                    dS = Lattice[x][y].densityS();
                    dT = Lattice[x][y].densityT();
                    sumS += dS;
                    sumT += dT;
                    Ccell.push_back(sumS+sumT);
                    CcellS.push_back(sumS);
                    CcellT.push_back(sumT);
                    //Init lines for Naive approche and zero approche
                    if((dS == 0) && (flag_zeroCSC==0)){
                        front_zeroCSC[x] = y;
                        flag_zeroCSC=1;
                    }
                    if((dT == 0)&&(flag_zeroTD==0)){
                        front_zeroTD[x] = y;
                        flag_zeroTD=1;
                    }
                    //End lines for Naive approche and zero approche
                }
                front_zero[x] = min(front_zeroCSC[x],front_zeroTD[x]); //line for zero approche
                int frontx=0;
                while(Ccell[frontx] < (0.95)*((double) (sumS+sumT))){frontx++;}
                int frontxS=0;
                while(CcellS[frontxS] < (0.95)*((double) (sumS))){frontxS++;}
                int frontxT=0;
                while(CcellT[frontxT] < (0.95)*((double) (sumT))){frontxT++;}
                front[x]=frontx;
                frontCSC[x]=frontxS;
                frontTD[x]=frontxT;
            }
    }

    void limit_frontier(){
        left_front = height;
        for(int elem: front){
            if(elem <= left_front){
                left_front = elem;
            }
        }
        right_front = front_Naive;
    }
    void extract_bulk(){

    }
    
    void record_frontier_95(){
            ofstream data_info ("frontier.csv", ios_base::app);
            ofstream data_infoS ("frontierS.csv", ios_base::app);
            ofstream data_infoT ("frontierT.csv", ios_base::app);
            for(int x=0;x<height;x++){
                int sumS = 0;
                int sumT = 0;
                vector<int> Ccell;
                vector<int> CcellS;
                vector<int> CcellT;
                int dS = 0;
                int dT = 0;
                for(int y=0; y<width; y++){
                    dS = Lattice[x][y].densityS();
                    dT = Lattice[x][y].densityT();
                    sumS += dS;
                    sumT += dT;
                    Ccell.push_back(sumS+sumT);
                    CcellS.push_back(sumS);
                    CcellT.push_back(sumT);
                }
                int frontx=0;
                while(Ccell[frontx] < (0.95)*((double) (sumS+sumT))){frontx++;}
                int frontxS=0;
                while(CcellS[frontxS] < (0.95)*((double) (sumS))){frontxS++;}
                int frontxT=0;
                while(CcellT[frontxT] < (0.95)*((double) (sumT))){frontxT++;}
                data_info << frontx << " ";
                data_infoS << frontxS << " ";
                data_infoT << frontxT << " ";
            }
            data_info << endl;
            data_infoS << endl;
            data_infoT << endl;
    }


    
    
};




#endif /* lgca_h */
