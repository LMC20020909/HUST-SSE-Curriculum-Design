int main () {
    int i = 0;
    for(i = 1; i <= 10; i++) {
        if(i == 2) 
            continue;
        if(i == 7)
            break;
        write(i);
    }
    return 0;
}
