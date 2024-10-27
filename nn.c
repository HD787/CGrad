#include <stdarg.h>
nn* createNn(){
    nn* newnn = malloc(sizeof(nn));
    newnn->layers = malloc(sizeof(layer))
    newnn->length = 0;
    return newnn;
}

void addLayer(nn* n, layer* lay){
    n->length++;
    realloc(n->layer, sizeof(layer)* n->length);
    n->layers[n->length] = lay;
}

void conv2dActivation(lay* prev; layer* curr){
    //maybe move this line out of here, checks should happen earlier
    if(curr->padDimCount > 4 || curr->padDimCount < 2) {printf("invalid dimension count for pool"); return;}
    tensor* nt = ntaddPadding(prev->activation, curr->padding, curr->padDimCount);
    int shape[4];
    shape[0] = (padDimCount > 3): nt->shape[0] ? 1;
    shape[1] = (padDimCount > 2): nt->shape[1] ? 1;
    shape[2] = nt->shape[2];
    shape[3] = nt->shape[3];
    for(int i = 0; i < shape[0]; i++){
        for(int j = 0; j < shape[1]; j++){
            for(int k = 0; k < shape[2]; k++){
                //increment by k * ykernel
                for(int l = 0; l < shape[3]; l++)
                    //increment by l * xkernel
            }
        }
    }
    curr->activation = nt;
}

void linearActivation(layer* prev, layer* curr){}

void poolActivation(layer* prev, prev* curr){}

void activate(nn* n){
    for(int i = 0; i < n->length; i++){
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
        n->graph[i].activationFunction(n->graph[i]);
    }
}

void gradient(nn* n){

}