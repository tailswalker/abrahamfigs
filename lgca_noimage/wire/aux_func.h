//
//  aux_func.h
//  lgca-feedback
//
//  Created by Muon02 on 5/1/21.
//  Copyright © 2021 Muon02. All rights reserved.
//

#ifndef aux_func_h
#define aux_func_h

inline string i2s_format(int n, int len)
{
    string result(len--, '0');
    for (int val=(n<0)?-n:n; len>=0&&val!=0; --len,val/=10)
       result[len]='0'+val%10;
    if (len>=0&&n<0) result[0]='-';
    return result;
}

float avg(vector<int> numbers){
    float result = 0;
    for(int b: numbers){
        result += b;
    }
    return result/numbers.size();
}

float avg(vector<float> numbers){
    float result = 0;
    for(float b: numbers){
        result += b;
    }
    return result/numbers.size();
}

float standar_dev(vector<float> numbers){
    float result = 0;
    float mu = avg(numbers);
    for(float b: numbers){
        result += pow(b-mu,2);
    }
    return sqrt(result/numbers.size());
}

float standar_dev(vector<int> numbers){
    float result = 0;
    float mu = avg(numbers);
    for(float b: numbers){
        result += pow(b-mu,2);
    }
    return sqrt(result/numbers.size());
}


vector<complex<double> > computeDft(const vector<complex<double> > &input) {
    vector<complex<double> > output;
    size_t n = input.size();
    for (size_t k = 0; k < n; k++) {  // For each output element
        complex<double> sum(0, 0);
        for (size_t t = 0; t < n; t++) {  // For each input element
            double angle = 2 * M_PI * t * k / n;
            sum += input[t] * exp(complex<double>(0, -angle));
        }
        output.push_back(sum);
    }
    return output;
}

int dom_mode(vector<int> fronts){
    //First we normalize
    //Make vector into complex
    vector<complex<double> > frontsc(fronts.size(),0);
    int avg_front = avg(fronts);
    for (int k=0; k< fronts.size(); k++) {
        frontsc[k] = fronts[k]-avg_front;
    }
    vector<complex<double> > bombo = computeDft(frontsc);
    int max = 0;
    int max_val = 0;
    for (int k = 0; k < fronts.size()/2 +1; k++) {
        if (abs(bombo[k]) > max_val) {
            max = k;
            max_val = abs(bombo[k]);
        }
    }
    return max;
}

float long_curv(vector<int> front){
    float sum = 0;
    for(int i=0; i < front.size()-1; i++){
        sum += sqrt(pow(front[i]-front[i+1],2)+1);
    }
    return sum;
}

void quiz(vector<int> array){
    cout << dom_mode(array);
}

#endif /* aux_func_h */
