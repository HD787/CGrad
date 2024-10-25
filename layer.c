layer* conv2d(tensor* t, int* padding, int* filterShape, int kernelShape, int stride, int channelCount){
    layer* lay = malloc(sizeof(layer));
    lay->layerType = CONV;
    lay->padding = malloc(sizeof(int)*2);
    memcpy(lay->padding, padding, 2);
    //{filters, channels, input X, input Y}
    int weightShape[4] = {kernelShape, channelCount, filterShape[0], filterShape[1]};
    //{batch size, filter, input X, input Y}
    int activationShape[4] = {t->shape[0], kernelShape, t->shape[2], t->shape[3]};
    return lay;
}

layer* linear(tensor* t, int* outputShape, int outputLength, int channelCount){ 
    
    layer* lay = malloc(sizeof(layer));
    lay->layerType = LINEAR;
    int weightShape[2] = {outputLength, t->length};
    lay->weight = createTensor(weightShape, 4);
    lay->activation = createTensor(outputShape, 4)
    return lay;
}

layer* maxPool2d(tensor* t, int* kernelShape, int* padding, int padDimCount){

    
    layer* lay = malloc(sizeof(layer));
    tensor* nt = ntaddPadding(t, padding, padDimCount);
    


    //move this code to the forward pass activation when it exists
    // if(padDimCount > 4 || padDimCount < 2) {printf("invalid dimension count for pool"); return NULL;}
    // int shape[4];
    // shape[0] = (padDimCount > 3): nt->shape[0] ? 1;
    // shape[1] = (padDimCount > 2): nt->shape[1] ? 1;
    // shape[2] = nt->shape[2];
    // shape[3] = nt->shape[3];
    // for(int i = 0; i < shape[0]; i++){
    //     for(int j = 0; j < shape[1]; j++){
    //         for(int k = 0; k < shape[2]; k++){
    //             //increment by k * ykernel
    //             for(int l = 0; l < shape[3]; l++)
    //             //increment by l * xkernel
    //         }
    //     }
    // }

    lay->activation = 
    lay->layerType = POOL;
    return lay;
}