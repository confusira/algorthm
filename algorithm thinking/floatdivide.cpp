//
// Created by lenovo on 2024/12/22.
//
#include <iostream>

using namespace std;

int main(){
    double x;
    cin >> x;

    double l=0,r=x;

    /*
     * 保留四位小数 e-6
     * 保留五位小数 e-7
     * 保留六位小数 e-8
     */
    while(r-l>1e-8){
        double mid=(l+r)/2;

        if(mid*mid>=x)r=mid;
        else l=mid;
    }

    printf("%lf\n",l);

    return 0;
}