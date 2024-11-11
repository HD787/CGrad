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

void showLayer(layer* lay){
   if(lay->layerType != INPUT) showShape(lay->weight);
   showShape(lay->activation);
}

/* Layer generation functions */
layer* input(tensor* t){
    layer* lay = malloc(sizeof(layer)); 
    lay->layerType = INPUT;
    lay->activation = t;
    lay->activationType = NO_ACTIVATION;
    return lay;
}

//adjust this to handle paddings that arent "same"
layer* conv2d(tensor* input, int* padding, int* kernelShape, int kernelCount, int stride, int channelCount, int activationFunc){
    layer* lay = malloc(sizeof(layer));
    lay->layerType = CONV;
    lay->padding = malloc(sizeof(int)*2);
    lay->padDimCount = 2;
    
    memcpy(lay->padding, padding, sizeof(int) * 2);
    lay->kernelShape = malloc(sizeof(int)*2);
    memcpy(lay->kernelShape, kernelShape, sizeof(int)*2);
    lay->kernelDimCount = 2;
    lay->kernelStride = stride;
    //{filters, channels, input X, input Y}
    int weightShape[4] = {kernelCount, channelCount, kernelShape[0], kernelShape[1]};
    int paddedX = input->shape[2] + (padding[0]/2) - kernelShape[0];
    int paddedY = input->shape[3] + (padding[1]/2) - kernelShape[1];
    if (paddedX % stride != 0 || paddedY % stride != 0){
        printf("kernel does not fit evenly in input");
        free(lay);
        return NULL;
    }
    int xWidth = paddedX / stride + 1;
    int yWidth = paddedY / stride + 1;
    //{batch count, filter, x kernel positions, y kernel positions}
    int activationShape[4] = {input->shape[0], kernelCount, xWidth, yWidth};
    lay->weight = createTensor(weightShape, 4);
    lay->activation = createTensor(activationShape, 4);
    lay->activationType = activationFunc;
    lay->activationFunction = getActivation(activationFunc);
    return lay;
}

layer* linear(tensor* input, int* outputShape, int outputLength, int channelCount, int activationFunc){
    layer* lay = malloc(sizeof(layer));
    lay->layerType = LINEAR;
    int inputFeatures = input->shape[1] * input->shape[2] * input->shape[3];
    // Define the shape of the weight tensor
    int weightShape[2] = {inputFeatures, outputLength};
    lay->weight = createTensor(weightShape, 4);
    lay->activation = createTensor(outputShape, 4);
    lay->activationType = activationFunc;
    lay->activationFunction = getActivation(activationFunc);
    return lay;
}

layer* maxPool2d(tensor* t, int* kernelShape, int* padding, int padDimCount, int activationFunc){
    layer* lay = malloc(sizeof(layer));
    int shape[4] = {t->shape[0], t->shape[1], /*something*/, /*something*/};

    memcpy(lay->padding, padding, padDimCount);
    lay->weight = NULL;
    lay->layerType = POOL;
    lay->activationFunction = getActivation(activationFunc);
    return lay;
}




