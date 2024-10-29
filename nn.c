#include <stdarg.h>
nn* createNn(){
    nn* newnn = malloc(sizeof(nn));
    newnn->graph = malloc(sizeof(layer));
    newnn->length = 0;
    return newnn;
}

void addLayer(nn* n, layer* lay){
    n->length++;
    n->graph = realloc(n->graph, sizeof(layer)* n->length);
    n->graph[n->length] = *lay;
}

void conv2dActivation(layer* prev, layer* curr){
    tensor* nt = pad(prev->activation, curr->padding, curr->padDimCount);
    int shape[4];
    shape[0] = (curr->padDimCount > 3)? nt->shape[0] : 1;
    shape[1] = (curr->padDimCount > 2)? nt->shape[1] : 1;
    shape[2] = nt->shape[2];
    shape[3] = nt->shape[3];
    for(int i = 0; i < shape[0]; i++){//input tensor batch
        for(int j = 0; j < shape[1]; j++){//input tensor channel dim
            for(int k = 0; k < shape[3]; k += curr->kernelStride){//input tensor y dim
                for(int l = 0; l < shape[2]; l += curr->kernelStride){//input tensor x dim
                    float sum = 0;
                    for(int m = 0; m < curr->kernelShape[1]; m++){ //kernel y dim
                        for(int n = 0; n < curr->kernelShape[0]; n++){ //kernel x dim
                            //multiply the weight value by the previous activation
                            //also how do we know the prev layer activation tensor is 4 dims, need to make this extensible
                            sum += (curr->weight[findIndex(curr->weight, (int[]){i, j, k+m, l+n})] * prev->activation[findIndex(prev->activation, (int[]){i, j, k+m, l+n})]);
                        }
                    }
                    //write sum to output activation tensor
                    curr->activation[findIndex(i, j, k+m, l+n)] = sum;
                }
            }
        }
    }
    curr->activation = nt;
}

void linearActivation(layer* prev, layer* curr){}

void poolActivation(layer* prev, layer* curr){}

void forward(nn* n){
    if(n->length < 1) { printf("neural net has less than one layer"); return; }
    for(int i = 1; i < n->length; i++){
        switch(n->graph[i].layerType){
            case NO_TYPE:{
                break;
            }
            case LINEAR:{
                //linear function
                break;
            }
            case CONV:{
                conv2dActivation(&n->graph[i - 1], &n->graph[i]);
                break;
            }
            case POOL:{
                //pool function
                break;
            }
        }
        n->graph[i].activationFunction(&n->graph[i]);
    }
}

void backward(nn* n){

}