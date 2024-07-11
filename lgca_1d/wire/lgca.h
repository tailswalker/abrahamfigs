//
//  lgca.h
//  lgca-feedback
//
//  Created by Muon02 on 4/12/21.
//  Copyright © 2021 Muon02. All rights reserved.
//

#ifndef lgca_h
#define lgca_h

class LGCA_uni{
    public:
    vector<Node> Lattice;
    vector<int> front, frontCSC, frontTD;
    int front_Naive, front_NaiveCSC, front_NaiveTD;
    vector<int> front_zero, front_zeroCSC, front_zeroTD;
    int Time = 0;
    
    int width;
    int N;

    //Node parameters
    int chS;
    int chT;
    double nu;
    int alpha;
    double pT;
    double d;
    
    //For output
    vector<vector<int>> HistoryCSC, HistoryTD; //time x 50
    
    LGCA_uni(int largo, int bS, int bT, double v, int a, double p, double death)
    {
        width = largo;
        chS = bS;
        chT = bT;
        N = min(bS,bT);
        nu = v;
        alpha = a;
        pT = p;
        d = death;

        for (int k=0; k<largo; k++) {
            Lattice.push_back(Node());
        }
        
        front.resize(1, 4);
        frontCSC.resize(1, 4);
        frontTD.resize(1, 4);
        front_zero.resize(1, 4);
        front_zeroCSC.resize(1, 4);
        front_zeroTD.resize(1, 4);
        
        HistoryCSC.resize(51, vector<int>(50,0));
        HistoryTD.resize(51, vector<int>(50,0));
    }
    
    void putstrip()
    {
        for(int j=0; j < 4; j++)
        {
            Lattice[j].inicializar(N);
            add_history();
        }
    }
    
    bool isbig()
    {
        if((bool)(Lattice[width-3].ncellS + Lattice[width-3].ncellT))
        {
            return 0;
        }
        return 1;
    }
    
    void makebig()
    {
        width += 5;
        for(int k = 0; k<5; k++)
        {
            Lattice.push_back(Node());
        }
    }
    
    void step()
    {
        for (int j = 0; j < (width-2); j++)
        {
            Lattice[j].OR(chS, chT, nu, alpha, pT, d);
        }
        for (int j = 0; j < (width-2); j++)
        {
            if(j==0)
            {
                Lattice[j].Pbound(Lattice[j], Lattice[j+1], Lattice[j]);
            }
            else
            {
                Lattice[j].P(Lattice[j-1],Lattice[j],Lattice[j+1],Lattice[j]);
            }
        }
    }
    
    void walk(int t)
    {
        for(int k=0; k<t; k++)
        {
            get_ydata();
            if(!(isbig())) makebig();
            Time++;
            step();
        }
    }
    
    void add_history(){
        for (int n=0; n < 50; n++) {
            HistoryCSC[Time%50][n] = Lattice[n].ncellS;
            HistoryTD[Time%50][n] = Lattice[n].ncellT;
        }
    }
    
    void checklivefunction(){
        for (int n=0; n < 50; n++) {
            cout << Lattice[n].ncellS << ' ';
        }
        cout<< '\n';
    }

    void get_ydata(){
        string name = to_string(chS)+to_string(chT)+to_string(int(pT*10));
        ofstream data_infoS ("ydataS"+name+".csv", ios_base::app);
        ofstream data_infoT ("ydataT"+name+".csv", ios_base::app);
        int NcellCSC = 0;
        int NCellTD = 0;
        for(int y=0; y<width;y++){
            NcellCSC = Lattice[y].densityS();
            NCellTD = Lattice[y].densityT();
            data_infoS << NcellCSC<< " ";
            data_infoT << NCellTD<< " ";
        }
        data_infoS << endl;
        data_infoT << endl;
    }
    
    void take_live(){
        
        string WINDOWNAME;
        int pixelxloc;
        int M,N;
        float rCSC,rTD;
        
        WINDOWNAME = "Program";
        pixelxloc = 20;
        M = 51;
        N = 50;
        
        
        for(int t=0; t < 200; t++){
            
            cv::Mat img((M+1)*pixelxloc,(N+1)*pixelxloc+2,CV_8UC3, cv::Scalar(0,0,0));
            for (int m=0; m<M; m++) {
                for (int n=0; n<N; n++) {
                    /* Inside each cell */
                    for (int y = -pixelxloc/2+1; y < pixelxloc/2; y++) {
                        for (int x = -pixelxloc/2; x <= pixelxloc/2; x++) {
                            /* Calculating each r*/
                            rCSC = (pixelxloc/2) * ((float) HistoryCSC[m][n])/chS;
                            rTD  = (pixelxloc/2) * ((float) HistoryTD[m][n])/chT;
                            /* Coloring pixels */
                            //max(abs(x),abs(y))<rCSC
                            if ( sqrt(pow(x,2)+pow(y,2))<rCSC) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0]+=250;
                            }
                            //max(abs(x),abs(y))<rTD
                            if ( sqrt(pow(x,2)+pow(y,2))<rTD) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]+=250;
                            }
                            if ( (img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0] + img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[1] + img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]) == 0){
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0] = 255;
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[1] = 255;
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]  = 255;
                                
                            }
                        }
                    }
                }
            }
            cv::namedWindow(WINDOWNAME, cv::WINDOW_AUTOSIZE);
            cv::imshow(WINDOWNAME, img);
            cv::waitKey(43);
            if (t==49   ) {
                cv::imwrite("final.png", img);
            }
            walk(1);
            
        }
    }
    
};

#endif /* lgca_h */

