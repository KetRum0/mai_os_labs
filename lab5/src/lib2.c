double Derivative(double x, double delta){
    double dif = (cos(x+delta) - cos(x-delta))/(2*delta); 
    return dif;
}

int GCF(int a, int b){
    int m ; 
    int res=1;
    if (a < b) m = a;
    else m = b; 
    for (int i = m; i >= 1; --i) {
        if ((a % i == 0) && (b % i == 0)) {
            res = i;
            break;
        }
    }
    return res;
}