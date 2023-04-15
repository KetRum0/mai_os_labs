double Derivative(double x, double delta){
    double dif = (cos(x+delta) - cos(x))/delta;
    return dif;
}

int GCF(int a, int b){
    while(b != 0) {
        a = a % b;
        int tmp = a;
        a = b;
        b = tmp;
    }
    return a;
}
