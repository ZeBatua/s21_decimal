int getBit(int decimal, int position) {
    char result = 0;
    decimal = decimal >> position;
    if (decimal & 1 == 1) {
        result = 1;
    } 
    return result;
}