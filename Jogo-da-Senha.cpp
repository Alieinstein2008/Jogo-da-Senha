#include <iostream>
#include <cmath>
#include <random>

using namespace std;

int recFunc(int s, int t){
    if(s/t >= 1){
        return s;
    }else{
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distrib(1,6);
        int digito = distrib(gen);
        s = s * t + recFunc(digito, t/10);
        return s;
    }
}



int geraSenha(){
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(1,6);
    
    int digito = distrib(gen);
    int senha = recFunc(digito, 1000);
    return senha;
    
}



int main(){
    int senha = geraSenha();
    cout << senha;
}