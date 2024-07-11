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
    int Time = 0;
    int height;
    int width;

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
            //get_ydata();
        }
    }
    
    void take_picture()
    {
        int pixelxloc = 25;
        cv::Mat img(height*pixelxloc,width*pixelxloc,CV_8UC3, cv::Scalar(0,0, 0));
        for (int y=0; y<height; y++) {
            for (int x=0; x<width; x++) {
                    for (int incy=1; incy < pixelxloc; incy++) {
                        for (int incx=1; incx < pixelxloc; incx++) {
                            img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[0]=255;
                            img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[1]=255;
                            img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[2]=255;
                        }
                    }
                    for (int incy=1; incy < pixelxloc/2; incy++) {
                        //Steam cells
                        int densityS_h =((int) Lattice[y][x].densityS()*(pixelxloc/((float) chS)));
                        for (int incx=1; incx < densityS_h; incx++) {
                            img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[0]=255;
                            img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[1]=0;
                            img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[2]=0;
                        }
                    }
                    for (int incy=pixelxloc/2; incy < pixelxloc; incy++) {
                        //TD cells
                        int densityT_h =((int) Lattice[y][x].densityT()*(pixelxloc/((float) chT)));
                        for (int incx=1; incx < densityT_h; incx++) {
                            img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[0]=0;
                            img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[1]=255;
                            img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[2]=0;
                        }
                    }
            }
        }
        cv::namedWindow("Example", cv::WINDOW_FREERATIO);
        cv::imshow("Example", img);
        cv::waitKey(0);
        cv::destroyWindow("Example");
    }
    
    void take_live(){
        
        string WINDOWNAME = " bS: " + to_string(chS) + ", bT: " + to_string(chT) + ", nu: " + to_string(nu) + ", alpha: " + to_string(alpha) + ", psym: " + to_string(pT) +", death: " + to_string(d)  ;
        
        for(int t=0; t < 1000; t++){
            int pixelxloc = 50;
            cv::Mat img(height*pixelxloc,width*pixelxloc,CV_8UC3, cv::Scalar(0,0, 0));
            //for cells
            for (int y=0; y<height; y++) {
                for (int x=0; x<width; x++) {
                        for (int incy=1; incy < pixelxloc; incy++) {
                            for (int incx=1; incx < pixelxloc; incx++) {
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[0]=255;
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[1]=255;
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[2]=255;
                            }
                        }
                        for (int incy=1; incy < pixelxloc/2; incy++) {
                            //Steam cells
                            int densityS_h =2*((int) Lattice[y][x].densityS()*(pixelxloc/((float) 3*chS)))+pixelxloc/3;
                            for (int incx=pixelxloc/3; incx < densityS_h; incx++) {
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[0]=255;
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[1]=0;
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[2]=0;
                            }
                            if(Lattice[y][x].densityS()!=0){
                                for (int incx=1; incx < pixelxloc/3; incx++) {
                                    img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[0]=255;
                                    img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[1]=0;
                                    img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[2]=0;
                                }
                            }
                        }
                        for (int incy=pixelxloc/2; incy < pixelxloc; incy++) {
                            //TD cells
                            int densityT_h =2*((int) Lattice[y][x].densityT()*(pixelxloc/((float) 3*chT)))+pixelxloc/3;
                            for (int incx=pixelxloc/3; incx < densityT_h; incx++) {
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[0]=0;
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[1]=255;
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[2]=0;
                            }
                            if(Lattice[y][x].densityT()!=0){
                                for (int incx=1; incx < pixelxloc/3; incx++) {
                                    img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[0]=0;
                                    img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[1]=255;
                                    img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[2]=0;
                                }
                            }
                        }
                }
            }
            //for drawing the frontier
            for (int y=0; y<height; y++) {
                for (int incy=1; incy < pixelxloc; incy++) {
                    
                    //CSC
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc)[0]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc )[1]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc )[2]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc-1 )[0]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc-1 )[1]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc-1 )[2]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc+1 )[0]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc+1 )[1]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc+1 )[2]=255;
                    //TD
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc)[0]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc )[1]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc )[2]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc-1 )[0]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc-1 )[1]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc-1 )[2]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc+1 )[0]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc+1 )[1]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc+1 )[2]=255;
                    //general
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc)[0]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc )[1]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc )[2]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc-1 )[0]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc-1 )[1]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc-1 )[2]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc+1 )[0]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc+1 )[1]=0;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc+1 )[2]=255;
                }
                
            }
            cv::namedWindow(WINDOWNAME, cv::WINDOW_AUTOSIZE);
            cv::imshow(WINDOWNAME, img);
            cv::waitKey(43);
            walk(1);
            draw_line();
            if(t%100==0){
                cout << "Frente promedio: " << avg(front) << ", desviación standar del frente " << standar_dev(front) << endl;
                cout << "Modo dominante: " << dom_mode(front) << endl;
                cv::waitKey(0);
            }
            
        }
        cv::destroyWindow("Animation");
    }
    
    void take_live_2_mech(int time){
        
        for(int t=0; t < time; t++){
            int pixelxloc = 20;
            cv::Mat img(height*pixelxloc,width*pixelxloc,CV_8UC3, cv::Scalar(0,0, 0));
            //for cells
            for (int y=0; y<height; y++) {
                for (int x=0; x<width; x++) {
                        for (int incy=1; incy < pixelxloc; incy++) {
                            for (int incx=1; incx < pixelxloc; incx++) {
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[0]=255;
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[1]=255;
                                img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[2]=255;
                            }
                        }
                        for (int incy=1; incy < pixelxloc; incy++) {
                            //Steam cells
                            if (Lattice[y][x].density()!=0) {
                                if(Lattice[y][x].densityS()>=Lattice[y][x].densityT()){
                                    for (int incx=1; incx < pixelxloc; incx++) {
                                        img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[0]=255;
                                        img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[1]=0;
                                        img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[2]=0;
                                    }
                                }else{
                                    for (int incx=1; incx < pixelxloc; incx++) {
                                        img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[0]=0;
                                        img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[1]=0;
                                        img.at<cv::Vec3b>(y*pixelxloc+incy, x*pixelxloc+incx)[2]=255;
                                    }
                                }
                            }
                        }
                }
            }
            //for drawing the frontier
            for (int y=0; y<height; y++) {
                for (int incy=1; incy < pixelxloc; incy++) {
                    
                    //CSC
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc)[0]=13;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc )[1]=232;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc )[2]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc-1 )[0]=13;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc-1 )[1]=232;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc-1 )[2]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc+1 )[0]=13;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc+1 )[1]=231;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontCSC[y]*pixelxloc+1 )[2]=251;
                    //TD
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc)[0]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc )[1]=239;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc )[2]=41;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc-1 )[0]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc-1 )[1]=239;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc-1 )[2]=41;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc+1 )[0]=255;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc+1 )[1]=239;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, frontTD[y]*pixelxloc+1 )[2]=41;
                    //general
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc)[0]=70;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc )[1]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc )[2]=75;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc-1 )[0]=70;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc-1 )[1]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc-1 )[2]=75;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc+1 )[0]=70;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc+1 )[1]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, front[y]*pixelxloc+1 )[2]=75;
                    //general
                    int avg_front = avg(front);
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc)[0]=70;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc )[1]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc )[2]=75;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc-1 )[0]=70;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc-1 )[1]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc-1 )[2]=75;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc+1 )[0]=70;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc+1 )[1]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc+1 )[2]=75;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc+2 )[0]=70;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc+2 )[1]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc+2 )[2]=75;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc+3 )[0]=70;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc+3 )[1]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front*pixelxloc+3 )[2]=75;
                    int avg_front2 = avg(front_zero);
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc)[0]=230;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc )[1]=18;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc )[2]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc-1 )[0]=230;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc-1 )[1]=18;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc-1 )[2]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc+1 )[0]=230;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc+1 )[1]=18;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc+1 )[2]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc+2 )[0]=230;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc+2 )[1]=18;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc+2 )[2]=251;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc+3 )[0]=230;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc+3 )[1]=18;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front2*pixelxloc+3 )[2]=251;
                    int avg_front3 = front_Naive+1;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc)[0]=43;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc )[1]=91;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc )[2]=250;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc-1 )[0]=43;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc-1 )[1]=91;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc-1 )[2]=250;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc+1 )[0]=43;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc+1 )[1]=91;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc+1 )[2]=250;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc+2 )[0]=93;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc+2 )[1]=41;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc+2 )[2]=250;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc+3 )[0]=93;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc+3 )[1]=41;
                    img.at<cv::Vec3b>(y*pixelxloc+incy, avg_front3*pixelxloc+3 )[2]=250;
                    
                }
                
            }
            cv::namedWindow("Simulation", cv::WINDOW_AUTOSIZE);
            cv::imshow("Simulation", img);
            cv::waitKey(33);
            walk(1);
            draw_line();
            //cv::imwrite(IMGNAME, img);
        }
        cv::destroyWindow("Simulation");
    }

    void take_live_chS(int time){
        
        string WINDOWNAME;
        int pixelxloc;
        int M,N, Normalizator;
        float rCSC,rTD;
        float rleftS,rupS, rrightS, rdownS;
        float rleftT,rupT, rrightT, rdownT;
        
        WINDOWNAME = "Program";
        pixelxloc = 56;
        
        
        for(int t=0; t < time; t++){

            /*kind of walk
            if(!(isbig())) makebig();
            Time++;
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < (width-2); j++)
                {
                    Lattice[i][j].OR(chS, chT, nu, alpha, pT, d);
                }
            }
            */
            
            M = height;
            N = width;
            Normalizator = min(chS,chT);

            cv::Mat img((M+1)*pixelxloc,(N+1)*pixelxloc+2,CV_8UC3, cv::Scalar(0,0,0));
            for (int m=0; m<M; m++) {
                for (int n=0; n<N; n++) {
                    /* Inside each cell */
                    /* Calculating each r*/
                    rCSC = ( (pixelxloc/12) * ((float) Lattice[m][n].densitySrest())/Normalizator) + (pixelxloc/12)*((float) Lattice[m][n].densitySrest()>0);
                    rTD  = ( (pixelxloc/12) * ((float) Lattice[m][n].densityTrest())/Normalizator) + (pixelxloc/12)*((float) Lattice[m][n].densityTrest()>0);
                    rleftS = (pixelxloc/6) * Lattice[m][n].leftS;
                    rupS = (pixelxloc/6) * Lattice[m][n].upS;
                    rrightS = (pixelxloc/6) * Lattice[m][n].rightS;
                    rdownS = (pixelxloc/6) * Lattice[m][n].downS;
                    rleftT = (pixelxloc/6) * Lattice[m][n].leftT;
                    rupT = (pixelxloc/6) * Lattice[m][n].upT;
                    rrightT = (pixelxloc/6) * Lattice[m][n].rightT;
                    rdownT = (pixelxloc/6) * Lattice[m][n].downT;
                    for (int y = -pixelxloc/2+2; y < pixelxloc/2-2; y++) {
                        for (int x = -pixelxloc/2+2; x < pixelxloc/2-2; x++) {
                            /* Coloring pixels */
                            /* Center: */
                            //max(abs(x),abs(y))<rCSC
                            if ( sqrt(pow(x,2)+pow(y,2))<rCSC) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0]+=250;
                            }
                            //max(abs(x),abs(y))<rTD
                            if ( sqrt(pow(x,2)+pow(y,2))<rTD) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]+=250;
                            }
                            
                            
                            /*  Channels*/
                            
                            /*left*/
                            if ( sqrt(pow(x+pixelxloc/3,2)/2+pow(y,2))<rleftS/2) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0]+=250;
                            }
                            if ( sqrt(pow(x+pixelxloc/3,2)/2+pow(y,2))<rleftT/2) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]+=250;
                            }

                            /*right*/
                            if ( sqrt(pow(x-pixelxloc/3,2)/2+pow(y,2))<rrightS/2) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0]+=250;
                            }
                            if ( sqrt(pow(x-pixelxloc/3,2)/2+pow(y,2))<rrightT/2) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]+=250;
                            }

                            /*up*/
                            if ( sqrt(pow(x,2)+pow(y+pixelxloc/3,2)/2)<rupS/2) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0]+=250;
                            }
                            if ( sqrt(pow(x,2)+pow(y+pixelxloc/3,2)/2)<rupT/2) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]+=250;
                            }

                             /*down*/
                            if ( sqrt(pow(x,2)+pow(y-pixelxloc/3,2)/2)<rdownS/2) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0]+=250;
                            }
                            if ( sqrt(pow(x,2)+pow(y-pixelxloc/3,2)/2)<rdownT/2) {
                                img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]+=250;
                            }

                            /*Node background*/
                            if (Lattice[m][n].density()==0) {
                                if ( (img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0] + img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[1] + img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]) == 0){
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0] = 255;
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[1] = 255;
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]  = 255;
                                }
                            } else if (Lattice[m][n].densityS()>Lattice[m][n].densityT()) {
                                if ( (img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0] + img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[1] + img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]) == 0){
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0] = 250;
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[1] = 160;
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]  = 140;
                                }

                            } else if (Lattice[m][n].densityS()<Lattice[m][n].densityT()) {
                                if ( (img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0] + img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[1] + img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]) == 0){
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0] = 140;
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[1] = 160;
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]  = 250;
                                }
                                
                            } else if (Lattice[m][n].densityS()==Lattice[m][n].densityT()) {
                                if ( (img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0] + img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[1] + img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]) == 0){
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[0] = 255;
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[1] = 145;
                                    img.at<cv::Vec3b>(m*pixelxloc+y+pixelxloc/2, n*pixelxloc+x+pixelxloc/2)[2]  = 255;
                                }
                                
                            }
                        }
                    }
                }
            }
            cv::namedWindow(WINDOWNAME, cv::WINDOW_AUTOSIZE);
            cv::imshow(WINDOWNAME, img);
            cv::waitKey(0);

            /*Propagation part*/
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
            if(
            (t == 0) || (t == 10) || (t == 20) || (t == 30) || (t == 40) || (t == 50) || (t == 60)
        ){
            cv::imwrite("2Time"+to_string(t)+".png", img);
        }
        }
    }

    void take_live_big(int time){

        cv::Size frame_size(width, height);
        
        for(int t=0; t < time; t++){

            /*kind of walk*/
            Time++;
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < (width-2); j++)
                {
                    Lattice[i][j].OR(chS, chT, nu, alpha, pT, d);
                }
            }

        if(
            (t == 15000) || (t == 15050) || (t == 15100) || (t == 15150) || (t == 15200) || (t == 15250) || (t == 15300)
        ){

            cv::Mat img(height, width,CV_8UC3, cv::Scalar(255,255,255));
            for (int m=0; m<height; m++) {
                for (int n=0; n<width; n++) {
                    /* Inside each cell */
                    /*Node background*/
                    if (Lattice[m][n].densityS()>Lattice[m][n].densityT()) {
                            img.at<cv::Vec3b>(m, n)[0] = 250;
                            img.at<cv::Vec3b>(m, n)[1] = 0;
                            img.at<cv::Vec3b>(m, n)[2]  = 0;
                    } else if (Lattice[m][n].densityS()<Lattice[m][n].densityT()) {
                            img.at<cv::Vec3b>(m, n)[0] = 250;
                            img.at<cv::Vec3b>(m, n)[1] = 0;
                            img.at<cv::Vec3b>(m, n)[2]  = 0;
                    } else if ((Lattice[m][n].densityS()==Lattice[m][n].densityT())
                                    &(Lattice[m][n].density()!=0)) {
                            img.at<cv::Vec3b>(m, n)[0] = 250;
                            img.at<cv::Vec3b>(m, n)[1] = 0;
                            img.at<cv::Vec3b>(m, n)[2]  = 250;
                    }
                }
                
            }
            cv::imwrite("2Time"+to_string(t)+".png", img);

        }


            /*Propagation part*/
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
    }

    void get_ydata(){
        ofstream data_info ("ydata.csv", ios_base::app);
        ofstream data_infoS ("ydataS.csv", ios_base::app);
        ofstream data_infoT ("ydataT.csv", ios_base::app);
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
    
    void draw_line_all(){
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
                        front_NaiveCSC = y;
                    }else if (flag_zeroCSC==0){
                        front_zeroCSC[x];
                        flag_zeroCSC=1;
                    }
                    if(dT != 0){
                        front_NaiveTD = y;
                    }else if (flag_zeroTD==0){
                        front_zeroCSC[x] = y;
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
        N = bS +bT;
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
            Lattice[j].inicializar(chS);
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
            if(!(isbig())) makebig();
            Time++;
            step();
            add_history();
            //get_ydata();
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

