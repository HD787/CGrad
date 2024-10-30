/* layer operation functions */
void (*getActivation(int function))(tensor* t){
    switch(function){
        case NO_ACTIVATION:{
            return NULL;
        }
        case RELU:{
            return relu;
        }
        case SIGMOID:{
            return sigmoid;
        }
        default:{
            return NULL;
        }
    }
}


void randomizeWeights(layer* lay){
    randomize(lay->weight);
}

/* Layer generation functions */
layer* input(tensor* t){
    layer* lay = malloc(sizeof(layer)); 
    lay->layerType = INPUT;
    lay->activation = t;
    return lay;
}

layer* conv2d(tensor* t, int* padding, int* kernelShape, int kernelCount, int stride, int channelCount, int activationFunc){
    layer* lay = malloc(sizeof(layer));
    lay->layerType = CONV;
    lay->padding = malloc(sizeof(int)*2);
    lay->padDimCount = 2;
    memcpy(lay->padding, padding, 2);
    //{filters, channels, input X, input Y}
    int weightShape[4] = {kernelCount, channelCount, kernelShape[0], kernelShape[1]};
    //{batch count, filter, input X, input Y}
    int activationShape[4] = {t->shape[0], kernelCount, t->shape[2], t->shape[3]};
    lay->weight = createTensor(weightShape, 4);
    lay->activation = createTensor(activationShape, 4);
    lay->activationFunction = getActivation(activationFunc);
    return lay;
}

layer* linear(tensor* t, int* outputShape, int outputLength, int channelCount, int activationFunc){
    layer* lay = malloc(sizeof(layer));
    lay->layerType = LINEAR;
    int weightShape[2] = {outputLength, t->length};
    lay->weight = createTensor(weightShape, 4);
    lay->activation = createTensor(outputShape, 4);
    lay->activationFunction = getActivation(activationFunc);
    return lay;
}

layer* maxPool2d(tensor* t, int* kernelShape, int* padding, int padDimCount, int activationFunc){
    layer* lay = malloc(sizeof(layer));
    int x = (t->shape[t->ndim]);
    int y = (t->shape[t->ndim - 1]);
    if(t->ndim > 4){
        printf("invalid shape");
        return NULL; 
    }
    switch(t->ndim){
        case 1: {
            printf("invalid shape");
            return NULL;
        }
        case 2:{
            int shape[2] = { x, y };
            lay->activation = createTensor(shape, 2);
        }
        case 3:{
            int shape[3] = {
                t->shape[0],
                x,
                y
            };
            lay->activation = createTensor(shape, 3);
        }
        case 4:{
            int shape[4]= {
                t->shape[0], 
                t->shape[1],
                x,
                y
            };
            lay->activation = createTensor(shape, 4);
        }
    }
    memcpy(lay->padding, padding, padDimCount);
    lay->weight = NULL;
    lay->layerType = POOL;
    lay->activationFunction = getActivation(activationFunc);
    return lay;
}




