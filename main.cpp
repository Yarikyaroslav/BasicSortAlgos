#include <iostream>
#include <random>
#include <vector>

using namespace std;

int N = 50;

int main() {
    random_device rd;
    mt19937 mt(rd());
    int V[N][2*N+1];
    for(int i=0;i<N;i++){ V[i][N] = mt()%(N);}
    for(int j=N+1;j<2*N+1;j++){
        V[0][j] = V[0][j-1];
        for(int i=1;i<N;i++){
            if(V[i][j-1]>V[i-1][j]){
                V[i][j] = V[i][j-1];
            }
            else{
                V[i][j] = V[i-1][j];
                V[i-1][j] = V[i][j-1];
            }
        }
    }

    for(int j=N-1;j>-1;j--){
        V[N-1][j] = V[N-1][j+1];
        for(int i=N-2;i>-1;i--){
            if(V[i][j+1]>V[i+1][j]){
                V[i][j] = V[i][j+1];
            }
            else{
                V[i][j] = V[i+1][j];
                V[i+1][j] = V[i][j+1];
            }
        }
    }

    int count1[2*N+1];
    int count2[2*N+1];
    int count3[2*N+1];

    for(int k=0;k<2*N+1;k++){
        count1[k]=0;
        count2[k]=0;
        count3[k]=0;
        int tmp1[N];
        int tmp2[N];
        int tmp3[N];

        for(int i=0;i<N;i++){
            tmp1[i] = V[i][k];
            tmp2[i] = V[i][k];
            tmp3[i] = V[i][k];
        }

        for (int i = 0; i < N - 1; i++) {
            count1[k]+=4; //сравнение в for,инкремент в for,создание bool f, создание int j
            bool f = true;
            for (int j = 0; j < N - i - 1; j++) {
                count1[k]+=3; //сравнение в for, инкремент в for, сравнение в if
                if (tmp1[j] > tmp1[j + 1]) {
                    count1[k]+=4; // 4 присваивания
                    int temp = tmp1[j];
                    tmp1[j] = tmp1[j + 1];
                    tmp1[j + 1] = temp;
                    f=false;
                }
            }
            if(f) break;
        }

        for(int i = 1;i<N;i++){
            count2[k]+=4; //сравнение в for, инкремент в for, создание int temp, создание int j
            int temp = tmp2[i];
            int j = i;
            while((j>0)&&(tmp2[j-1]>temp)){
                count2[k]+=5; //2 сравнения + &&, присваивание, декремент
                tmp2[j] = tmp2[j-1];
                j--;
            }
            count2[k]+=4; //2 сравнения + &&, присваивание
            tmp2[j] = temp;
        }

        for(int i = 0;i<N-1;i++){
            count3[k]+=4; //сравнение в for, инкремент в for, создание int nmin, создание int j
            int nmin = i;
            for(int j = i;j<N;j++){
                count3[k]+=3; //сравнение в for, инкремент в for, сравнение в if
                if(tmp3[j]<tmp3[nmin]){
                    count3[k]+=1; //присваивание
                    nmin = j;
                }
            }
            count3[k]+=1; //сравнение в if
            if(nmin!=i){
                count3[k]+=3; //обмен (3 присваивания)
                int temp = tmp3[nmin];
                tmp3[nmin] = tmp3[i];
                tmp3[i] = temp;
            }
        }
        cout<<k<<'\t'<<count1[k]<<'\t'<<count2[k]<<'\t'<<count3[k]<<'\n';
    }

    for(int N=10;N<201;N+=10){
        cout<<'\n';
        int count1=0;
        int count2=0;
        int count3=0;
        vector<int> tmp1(N);
        for(int i=0;i<N;i++){ tmp1[i] = mt()%(N);}
        auto tmp2 = tmp1;
        auto tmp3 = tmp1;

        for (int i = 0; i < N - 1; i++) {
            count1+=4; //сравнение в for,инкремент в for,создание bool f, создание int j
            bool f = true;
            for (int j = 0; j < N - i - 1; j++) {
                count1+=3; //сравнение в for, инкремент в for, сравнение в if
                if (tmp1[j] > tmp1[j + 1]) {
                    count1+=4; // 4 присваивания
                    int temp = tmp1[j];
                    tmp1[j] = tmp1[j + 1];
                    tmp1[j + 1] = temp;
                    f=false;
                }
            }
            if(f) break;
        }

        for(int i = 1;i<N;i++){
            count2+=4; //сравнение в for, инкремент в for, создание int temp, создание int j
            int temp = tmp2[i];
            int j = i;
            while((j>0)&&(tmp2[j-1]>temp)){
                count2+=5; //2 сравнения + &&, присваивание, декремент
                tmp2[j] = tmp2[j-1];
                j--;
            }
            count2+=4; //2 сравнения + &&, присваивание
            tmp2[j] = temp;
        }

        for(int i = 0;i<N-1;i++){
            count3+=4; //сравнение в for, инкремент в for, создание int nmin, создание int j
            int nmin = i;
            for(int j = i;j<N;j++){
                count3+=3; //сравнение в for, инкремент в for, сравнение в if
                if(tmp3[j]<tmp3[nmin]){
                    count3+=1; //присваивание
                    nmin = j;
                }
            }
            count3+=1; //сравнение в if
            if(nmin!=i){
                count3+=3; //обмен (3 присваивания)
                int temp = tmp3[nmin];
                tmp3[nmin] = tmp3[i];
                tmp3[i] = temp;
            }
        }
        cout<<N<<'\t'<<count1<<'\t'<<count2<<'\t'<<count3;
    }

}