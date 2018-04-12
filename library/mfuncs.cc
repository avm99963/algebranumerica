double e_mclaurin(double x, int N) {
    double sum = 1;
    for (int i = N; i > 0; --i) {
        sum *= x/i;
        sum += 1;
    }

    return sum;
}

