#include <iostream>
#include <cmath>
#include <fstream>
#define USE_MATH_DEFINES
using namespace std;
#define FUNCTION 3*cos(6*M_PI*x)+7*sin(12*M_PI*x);

class complexNum
{
public:
    double Re, Im, freq;
    complexNum(){
        Re=Im=freq=0;
    }
    double getAbs(){
        return sqrt(Re*Re+Im*Im);
    }
    double getArg(){
        return atan(Im/Re);
    }
};

int main(){
    int N=100;
    double t0=0, T=1;
    double mu=(double)1/T;
    double* function=new double[N];
    for(int i=0; i<N; i++){
        double x=t0+T/(N-1)*i;
        function[i]=FUNCTION;
    }
    complexNum* FurieFunction=new complexNum[N+1];
    for (int i=0; i<N+1; i++){
        for (int j=0; j<N; j++){
            FurieFunction[i].Re+=function[j]*cos(2*M_PI*(double)i*(double)j/N);
            FurieFunction[i].Im+=function[j]*sin(2*M_PI*(double)i*(double)j/N);
        }
        FurieFunction[i].freq=mu*i;
    }
    ofstream fOutput("/home/qw/output.txt");
    cout<<"Вывод коэффициентов Ак и Вк, а также частота"<<endl;
    for (int i=0; i<(N+1)/2; i++){
        fOutput<<FurieFunction[i].getAbs()/N*2<<" "<<FurieFunction[i].freq<<'\n';
        cout<<FurieFunction[i].Re/N*2<<"  "<<FurieFunction[i].Im/N*2<<"  "<<FurieFunction[i].freq<<endl;
    }
    double* summKoeffs=new double[N];
    for(int i=0; i<N; i++)
        summKoeffs[i]=0;
    cout<<"Вывод значений функции по формуле и по расчетам, значения слева и справа должны совпадать"<<endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            summKoeffs[i]+=FurieFunction[j].Re*cos(2*M_PI*(double)i*(double)j/N)/N;
            summKoeffs[i]-=FurieFunction[j].Im*sin(2*M_PI*(double)i*(double)j/N)/N;
        }
    }
    printf("%.14f    %.14f\n", function[0], summKoeffs[0]);
    for (int i=1; i<N; i++)
        printf("%.14f    %.14f\n", function[i], summKoeffs[N-i]);
    return 0;
}
