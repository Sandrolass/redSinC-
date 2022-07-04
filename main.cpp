#include <iostream>
#include <math.h>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>

//typedef ap_fixed<32,8,AP_RND,AP_SAT> apfixed;
using namespace std;

//--



double activationFunctionRelu(double x){
    return max(0.0,x);
}

double activationFunctionSigmoid(double x){
    return (1/(1+exp(-x)));
}
void forwardInput(double in ,double out[6],const double weights[6],double bias[6]){
    for(unsigned i =0;i<6;i++){
        out[i]= activationFunctionRelu(in*weights[i]+bias[i]);
    }

}
void forwardh1(double in[6] ,double out[5],const double weights[5][6],double bias[5]){
    for(unsigned i =0;i<5;i++){
        out[i] = 0.0;
        for(unsigned j =0 ; j<6;j++){
            out[i] +=in[j]*weights[i][j];
        }
        out[i] = activationFunctionRelu(out[i]+bias[i]);
        
    }
}
void forwardh2(double in[5] ,double out[4],const double weights[4][5],double bias[4]){
    for(unsigned i =0;i<4;i++){
        out[i] = 0.0;
        for(unsigned j =0 ; j<5;j++){
            out[i] +=in[j]*weights[i][j];
        }
        out[i] = activationFunctionRelu(out[i]+bias[i]);
        
    }
}
double  forwardOut(double in[4],double out,const double weights[4],double bias){
    out = 0.0;
    for(unsigned i =0;i<4;i++){
        out+= in[i]*weights[i];
    }
    out = activationFunctionSigmoid(out+bias);

    return out;
}
//--

double  loadData(double ilayer[6],double hlayer1[5][6],double hlayer2[4][5], double olayer[4],
double biasI[6],double biash1[5], double biash2[4]){
    ifstream newfile("data.txt");
    int i , j;
    string nums;
    double num,biasO;
    for( i=0;i<6;i++){
           newfile >> nums;
           num = stod(nums);
           ilayer[i]= num;
    }
    for( i =0;i<5;i++){
        for( j=0;j<6;j++){
            newfile >> nums;
            num = stod(nums);
            hlayer1[i][j] = num;
        }
    }
    for( i =0;i<4;i++){
        for(j=0;j<5;j++){
            newfile >> nums;
            num = stod(nums);
            hlayer2[i][j] = num;
        }
    }
    for( i=0;i<4;i++){
           newfile >> nums;
           num = stod(nums);
           olayer[i]= num;
    }
    for(i=0;i<6;i++){
            newfile >> nums;
           num = stod(nums);
           biasI[i]= num;
    }
    for(i=0;i<5;i++){
            newfile >> nums;
           num = stod(nums);
           biash1[i]= num;
    }
    for(i=0;i<4;i++){
            newfile >> nums;
           num = stod(nums);
           biash2[i]= num;
    }
    newfile >> nums;
    num = stod(nums);
    biasO = num;
    
    
   
   newfile.close();
   return biasO;
}


/*  double void  red(){
    forwardInput(inputValsI,outputValsI,inputLayer,bias1);
    forwardh1(outputValsI,outputValsH1,hiddenLayer1,bias2);
    forwardh2(outputValsH1,outputValsH2,hiddenLayer2,bias3);
   return  res = forwardOut(outputValsH2,output,outputLayer,bias4);
} */ 

double runAll(double in , double inputWeights[6],double bias1[6],double hiddenLayer1[5][6],double bias2[5],
            double hiddenLayer2[4][5],double bias3[4],double outputLayer[4], double bias4 ){
                double outputValsI[6],outputValsH1[5],outputValsH2[4];
                double output;
                forwardInput(in,outputValsI,inputWeights,bias1);
                forwardh1(outputValsI,outputValsH1,hiddenLayer1,bias2);
                forwardh2(outputValsH1,outputValsH2,hiddenLayer2,bias3);
                return  forwardOut(outputValsH2,output,outputLayer,bias4);

            }



int main(){
    /*double inputLayer[6] = {-0.27780336 ,-0.17232049  ,0.9181395 , -0.72189707,  0.606778,   -0.02868599};
    double hiddenLayer1[5][6] = {{-0.0886485  ,-0.15085012 ,-0.28952578 ,-0.53803086, -0.6289699,  -0.2742702 },
                                 {0.01574647,-0.22231227,0.3699188 ,0.42089623,0.17074184,0.583399 },
                                {-0.19185388,-0.63338447, 0.9867357 , 0.27087528,-0.78941923,0.35257977},
                                { 0.52712554,-0.47726664,-1.3614067 ,0.281215  ,0.98959255,0.4705966 },
                                 {-0.1981777, -0.5740007 ,0.8039098 ,-0.30836532,-0.5937497 ,0.125431 }};
    double hiddenLayer2[4][5] = {{-0.5868013 ,-0.5499852 ,0.198586  ,1.2795537 ,-0.16722222},
                                {-0.3756416 ,-0.7976374 ,-0.6030721 ,0.07465453,-0.35262778},
                                { 0.6803715, 0.43162057,-1.0743827 ,0.8904137 ,0.5677792},
                                {0.22692406,0.7371461 ,0.71797633,1.052458,  1.038114  }};
    double outputLayer[4] = {1.3640026, 0.81184673,1.3261917, 2.1023002 };*/
    double bias1[6]={-1.0661598,0.0,0.0,0.0,0.0,0.10200185};
    double bias2[5]={-1.8157208,0.82531506,0.78921926,0.44062296,0.7459145};
    double bias3[4]={-1.6017522,1.4491416,0.0,-0.03135741};
    double bias4 =-1.3076416;
    double inputLayer[6], hiddenLayer1[5][6],hiddenLayer2[4][5],outputLayer[4];
    bias4 = loadData(inputLayer,hiddenLayer1,hiddenLayer2,outputLayer,bias1,bias2,bias3);
    //double inputValsI;
    //double outputValsI[6],outputValsH1[5],outputValsH2[4];
    //double output,res;
    double res;
    string cadena;
    ifstream newfile("x.txt");
    ofstream secondfile("res.txt");
    /*for(int i=0;i<1000;i++){
        newfile>>cadena;
        forwardInput(stod(cadena),outputValsI,inputLayer,bias1);
        forwardh1(outputValsI,outputValsH1,hiddenLayer1,bias2);
        forwardh2(outputValsH1,outputValsH2,hiddenLayer2,bias3);
        res = forwardOut(outputValsH2,output,outputLayer,bias4);
        secondfile << res;
        secondfile << endl;
        cout<<res*2-1<<endl;
    }*/
   for(int i=0;i<1000;i++){
       newfile>>cadena;
       res =  runAll(stod(cadena),inputLayer,bias1,hiddenLayer1,bias2,hiddenLayer2,bias3,outputLayer,bias4);
       secondfile << res;
       secondfile << endl;
       cout<<res*2-1<<endl;
   }

    

    






    return 0;
}