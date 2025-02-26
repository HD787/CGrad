#include <stdarg.h>
nn* createNn(){
    nn* newnn = malloc(sizeof(nn));
    newnn->length = 0;
    newnn->graph = malloc(sizeof(layer) * newnn->length);
    return newnn;
}

void showNn(nn* n){
    for(int i = 0; i < n->length; i++){
        showLayer(&n->graph[i]);
    }
}

void randomizeGraphWeights(nn* n){
    for(int i = 0; i < n->length; i++){
        randomize(n->graph[i].weight);
    };
}

void addLayer(nn* n, layer* lay){
    n->graph = realloc(n->graph, sizeof(layer) * (n->length + 1));
    n->graph[n->length] = *lay;
    n->length++;
}

void conv2dActivation(layer* prev, layer* curr){
    if(prev->activation->ndim < 4){
        printf("convolution input layer is the wrong shape");
        return;
    }
    if(prev->activation->shape[0] != curr->weight->shape[0]){
        printf("batch count mismatch between input and current layer got %i, expected %i", prev->activation->shape[0], curr->weight->shape[0]); 
        return;
    }
    if(prev->activation->shape[1] != curr->weight->shape[1]){
        printf("channel count mismatch between input and current layer got %i, expected %i", prev->activation->shape[1], curr->weight->shape[1]); 
        return;
    }
    tensor* nt = pad(prev->activation, curr->padShape, curr->padDimCount);
    //consider referring to x and y and width and height from now on
    int outIndex = 0;
    for(int i = 0; i < nt->shape[0]; i++){//input tensor batch 
        for(int j = 0; j < nt->shape[1]; j++){//input tensor channel dim
            for(int k = 0; k < nt->shape[2] - curr->kernelShape[0] - 1; k += curr->kernelStride){//input tensor y dim
                for(int l = 0; l < nt->shape[3] - curr->kernelShape[1] - 1; l += curr->kernelStride){//input tensor x dim
                    float sum = 0;
                    for(int m = 0; m < curr->kernelShape[0]; m++){ //kernel y dim
                        for(int n = 0; n < curr->kernelShape[1]; n++){ //kernel x dim
                            //multiply the weight value by the previous activation
                            sum += (curr->weight->data[findIndex(curr->weight, (int[]){i, j, m, n})] * nt->data[findIndex(nt, (int[]){i, j, k+m, l+n})]);
                        }
                    }
                    //write sum to output activation tensor
                    curr->activation->data[outIndex++] = sum;
                }
            }
        }
    }
}

void linearActivation(layer* prev, layer* curr){
    //iterate
    for(int i = 0; i < curr->weight->shape[0]; i++){
        int sum = 0;
        for(int j = 0; j < curr->weight->shape[1]; j++){
            //multiply all the value of the input tensor activation by the rows(columns) of the wight tensor
            //this is commutative so dont worry about input tensor shape
            sum = curr->weight->data[findIndex(curr->weight, (int[]){i, j})] * prev->activation->data[j];
        }
        curr->activation->data[i] = sum;
    }
}

void maxPool2dActivation(layer* prev, layer* curr){
    // consider adding error checks
    tensor* nt = pad(prev->activation, curr->padShape, curr->padDimCount);
    int outIndex = 0;
    for(int i = 0; i < nt->shape[0]; i++){//input tensor batch 
        for(int j = 0; j < nt->shape[1]; j++){//input tensor channel dim
            for(int k = 0; k < nt->shape[2] - curr->kernelShape[0] - 1; k += curr->kernelStride){//input tensor y dim
                for(int l = 0; l < nt->shape[3] - curr->kernelShape[1] - 1; l += curr->kernelStride){//input tensor x dim
                    float currMax = -INFINITY;
                    for(int m = 0; m < curr->kernelShape[0]; m++){ //kernel y dim
                        for(int n = 0; n < curr->kernelShape[1]; n++){ //kernel x dim
                            //find the largest value within the kernel frame and set it to currMax
                            if(nt->data[findIndex(nt, (int[]){i, j, k+m, l+n})] > currMax) currMax = nt->data[findIndex(nt, (int[]){i, j, k+m, l+n})]; 
                        }
                    }
                    //write sum to output activation tensor
                    curr->activation->data[outIndex++] = currMax;
                }
            }
        }
    }
}

void forward(nn* n){
    if(n->length < 1) { printf("neural net has less than one layer"); return; }
    for(int i = 0; i < n->length; i++){
        switch(n->graph[i].layerType){
            case NO_TYPE:{
                break;
            }
            case INPUT:{
                break;
            }
            case LINEAR:{
                if(i == 0) { printf("tried to perform linear forward pass zeroeth layer"); break; }
                linearActivation(&n->graph[i - 1], &n->graph[i]);
                break;
            }
            case CONV:{
                if(i == 0) { printf("tried to perform convolution on zeroeth layer"); break; }
                conv2dActivation(&n->graph[i - 1], &n->graph[i]);
                break;
            }
            case MAX_POOL:{
                if(i == 0) { printf("tried to perform max pool on zeroeth layer"); break; }
                // maxPool2dActivation(&n->graph[i - 1], &n->graph[i]);
                break;
            }
        }
        if(n->graph[i].activationType != NO_ACTIVATION){
            n->graph[i].activationFunction(n->graph[i].activation);
        }
    }
}

//TODO: lowkey the name CGrad is innapropriate until this gets implemented
void backward(nn* n){

}