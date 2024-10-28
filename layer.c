layer* conv2d(tensor* t, int* padding, int* filterShape, int kernelShape, int stride, int channelCount){
    layer* lay = malloc(sizeof(layer));
    lay->layerType = CONV;
    lay->padding = malloc(sizeof(int)*2);
    lay->padDimCount = 2;
    memcpy(lay->padding, padding, 2);
    //{filters, channels, input X, input Y}
    int weightShape[4] = {kernelShape, channelCount, filterShape[0], filterShape[1]};
    //{batch size, filter, input X, input Y}
    int activationShape[4] = {t->shape[0], kernelShape, t->shape[2], t->shape[3]};
    lay->weight = createTensor(weightShape, 4);
    lay->activation = createTensor(activationShape, 4);
    return lay;
}

layer* linear(tensor* t, int* outputShape, int outputLength, int channelCount){
    layer* lay = malloc(sizeof(layer));
    lay->layerType = LINEAR;
    int weightShape[2] = {outputLength, t->length};
    lay->weight = createTensor(weightShape, 4);
    lay->activation = createTensor(outputShape, 4);
    return lay;
}

layer* maxPool2d(tensor* t, int* kernelShape, int* padding, int padDimCount){
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
    return lay;
}