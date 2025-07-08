#include<iostream>
#include<vector>
using namespace std;

double callPrice(int S, int K, double sigma, double r, int T, int N)
{
    
}

int main()
{
    int S; int K; double sigma; double r; int T; int N; 
    cout<<"Enter the Stock price, Strike price, risk free rate,volatility, Maturity, Number of steps: "<<endl;
    cin>>S;
    cin>>K;
    cin>>r;
    cin>>sigma;
    cin>>T;
    cin>>N;

    double call = callPrice(S, K, sigma, r, T, N);
    cout<<call<<endl;



}