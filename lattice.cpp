#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

double biPrice(double S, double K, double sigma, double r, int T, int N, bool call)
{
    double dt = T/N;
    double u= std::exp(sigma* (std::sqrt(dt)));
    double d= 1/u;
    double p = (std::exp(r* dt)-d)/(u-d);
    double discount = std::exp(r* -dt);
    
    vector<double> assetp(N+1);

    for(int i=0;i<N+1;i++)
    {
        assetp[i]=S*(std::pow(u, N-i))*(std::pow(d,i));
    }

    //forward prop
    vector<double> optionval(N+1);
    for(int i=0;i<=N;i++)
    {
        if(call)
        {
            optionval[i] = std::max(assetp[i]-K, 0.0);
        }
        else{
            optionval[i] = std::max(K-assetp[i], 0.0);
        }
    }

    //backward prop
     for(int step=N-1;step>=0;step--)
     {
        for(int i=0;i<=step;i++)
        {
            optionval[i]= ((p*optionval[i]) + ((1-p)*optionval[i+1]))*discount;
        }
     }

    return optionval[0];
}

int main()
{
    double S; double K; double sigma; double r; double T; double N; 
    cout<<"Enter the Stock price, Strike price, risk free rate,volatility, Maturity, Number of steps: "<<endl;
    cin>>S;
    cin>>K;
    cin>>r;
    cin>>sigma;
    cin>>T;
    cin>>N;

    double call1 = biPrice(S, K, sigma, r, T, N, true);
    double put = biPrice(S, K, sigma, r, T, N, false);

    cout<<call1<<endl;
    return 0;
}