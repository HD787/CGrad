void testCoords(){
    int shape[3] = {8, 2, 2};
    tensor* first = createTensor(shape, 3);
    float data[] = {
        1.0, 2.0, 3.0, 
        4.0, 5.0, 6.0, 
        7.0, 8.0, 9.0, 
        10.0, 11.0, 16.0,
        1.0, 2.0, 3.0, 
        4.0, 5.0, 6.0, 
        7.0, 8.0, 9.0, 
        10.0, 11.0, 16.0
    };
    memcpy(first->data, data, sizeof(float)*32);
    int pad[] = {2, 2};
    // pad(pad, first);
    // coord* coords = findCoords(11, first); printf("%d, %d\n", coords->coords[0],coords->coords[1]);
    repr()
}

void testIndex(){}

void testPadding(){}

int main(){}