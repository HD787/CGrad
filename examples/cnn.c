#include "../CGrad.h"
#define PREV_ACT n->graph[n->length - 1].activation 


int main(){
    int shape[] = {1, 1, 9, 9};
    tensor* first = createTensor(shape, 4);
    float data[] = {
        1.0, 2.0, 3.0, 
        4.0, 5.0, 6.0, 
        7.0, 8.0, 9.0, 
        10.0, 11.0, 16.0,
        1.0, 2.0, 3.0, 
        4.0, 5.0, 6.0, 
        7.0, 8.0, 9.0, 
        10.0, 11.0, 16.0,
        1.0, 2.0, 3.0, 
        4.0, 5.0, 6.0, 
        7.0, 8.0, 9.0, 
        10.0, 11.0, 16.0,
        1.0, 2.0, 3.0, 
        4.0, 5.0, 6.0, 
        7.0, 8.0, 9.0, 
        10.0, 11.0, 16.0,
        1.0, 2.0, 3.0, 
        4.0, 5.0, 6.0, 
        7.0, 8.0, 9.0, 
        10.0, 11.0, 16.0,
        1.0, 2.0, 3.0, 
        4.0, 5.0, 6.0, 
        7.0, 8.0, 9.0, 
        10.0, 11.0, 16.0,
        1.0, 2.0, 3.0, 
        4.0, 5.0, 6.0, 
        7.0, 8.0, 9.0
    };
    memcpy(first->data, data, sizeof(float)*81);
    nn* n = createNn();
    addLayer(n, input(first));
    addLayer(n, conv2d(PREV_ACT, (int[]){4, 4}, (int[]){3,3}, 1, 1, 1, RELU));
    addLayer(n, maxPool2d(PREV_ACT, (int[]){3, 3}, (int[]){0, 0}, 2, NO_ACTIVATION));
    // showShape(first);

    
    
    // randomize(n->graph[0].activation);
    randomizeWeights(&n->graph[1]);
    forward(n);

    
    // showShape(n->graph[1].weight);
    // showFlatArray(n->graph[1].weight);
    // showShape(n->graph[1].activation);
    // repr(n->graph[1].activation);
    // repr(n->graph[0].activation);
    // repr(n->graph[1].weight);
    // repr(n->graph[1].activation);
    // repr(n->graph[2].activation);
    showNn(n);
    
    return 1;
}