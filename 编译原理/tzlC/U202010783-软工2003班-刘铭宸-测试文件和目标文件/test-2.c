int main () {
    int a = 0;
    switch(a++) {
        case 0: write(0);
        case 1: write(1); break;
        case 2: write(2); break;
        default:write(a); break;
    }
    return 0;
}