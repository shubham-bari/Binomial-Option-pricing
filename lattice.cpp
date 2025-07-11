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

double americanBiPrice(double S, double K, double sigma, double r, int T, int N, bool call)
{
    double dt = T/N;
    double u = std::exp(sigma * (std::sqrt(dt)));
    double d = 1/u;
    double p = (std::exp(r * dt) - d) / (u - d);
    double discount = std::exp(r * -dt);
    
    vector<double> assetp(N+1);

    for(int i=0; i<N+1; i++)
    {
        assetp[i] = S * (std::pow(u, N-i)) * (std::pow(d, i));
    }

    // Terminal values (same as European)
    vector<double> optionval(N+1);
    for(int i=0; i<=N; i++)
    {
        if(call)
        {
            optionval[i] = std::max(assetp[i] - K, 0.0);
        }
        else
        {
            optionval[i] = std::max(K - assetp[i], 0.0);
        }
    }

    // Backward induction with early exercise check
    for(int step=N-1; step>=0; step--)
    {
        for(int i=0; i<=step; i++)
        {
            // Calculate continuation value
            double continuation = ((p * optionval[i]) + ((1-p) * optionval[i+1])) * discount;
            
            // Calculate early exercise value
            double earlyExercise;
            if(call)
            {
                earlyExercise = std::max(assetp[i] - K, 0.0);
            }
            else
            {
                earlyExercise = std::max(K - assetp[i], 0.0);
            }
            
            // Take the maximum of continuation and early exercise
            optionval[i] = std::max(continuation, earlyExercise);
        }
    }

    return optionval[0];
}

int main()
{
    double S; double K; double sigma; double r; double T; double N; 
    cout<<"Enter the Stock price, Strike price, risk free rate, volatility, Maturity, Number of steps: "<<endl;
    cin>>S;
    cin>>K;
    cin>>r;
    cin>>sigma;
    cin>>T;
    cin>>N;

    // European options
    double europeanCall = biPrice(S, K, sigma, r, T, N, true);
    double europeanPut = biPrice(S, K, sigma, r, T, N, false);
    
    // American options
    double americanCall = americanBiPrice(S, K, sigma, r, T, N, true);
    double americanPut = americanBiPrice(S, K, sigma, r, T, N, false);

    cout << "\n=== Option Prices ===" << endl;
    cout << "European Call: " << europeanCall << endl;
    cout << "European Put:  " << europeanPut << endl;
    cout << "American Call: " << americanCall << endl;
    cout << "American Put:  " << americanPut << endl;
    
    return 0;
}