#include <iostream>
#include <math.h>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>

//typedef ap_fixed<32,8,AP_RND,AP_SAT> apfixed;
using namespace std;

//-- Este cpp solo sirve para realizar la operacion de la red de python de otro repositorio anterior
// data.txt contiene los pesos y bias de la red neuronal antes mencionada , cambiando los tamaños de los arrays podemos ser capaces de realizar
// los procesos de cualquier red de 4 capas , ( para más capas deberían hacerse los suso dichas funciones)



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
    
    double bias1[6],bias2[5],bias3[4],bias4;
    double inputLayer[6], hiddenLayer1[5][6],hiddenLayer2[4][5],outputLayer[4];
    bias4 = loadData(inputLayer,hiddenLayer1,hiddenLayer2,outputLayer,bias1,bias2,bias3);
    double res;
    string cadena;
    ifstream newfile("x.txt");
    ofstream secondfile("res.txt");
   for(int i=0;i<1000;i++){
       newfile>>cadena;
       res =  runAll(stod(cadena),inputLayer,bias1,hiddenLayer1,bias2,hiddenLayer2,bias3,outputLayer,bias4);
       secondfile << res;
       secondfile << endl;
       cout<<res*2-1<<endl;
   }

    

    






    return 0;
}