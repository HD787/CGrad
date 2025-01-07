enum layerTypes{
    NO_TYPE,
    INPUT,
    LINEAR,
    CONV,
    MAX_POOL
};

enum activationTypes{
    NO_ACTIVATION,
    RELU,
    SIGMOID
};

typedef struct{
    float* data;
    int* shape;
    int ndim;
    int length;
    int grad;
}tensor;

//each layer may need and additional tensor or something for the backward pass
typedef struct{
    tensor* weight;
    tensor* bias;
    tensor* activation;
    int* padShape;
    int* kernelShape;
    void(*activationFunction)(tensor* t);
    int useBias;
    int padDimCount;
    int kernelDimCount;
    int kernelStride;
    int activationType;
    int layerType;
}layer;

typedef struct{
    layer* graph;
    int length;
}nn;

typedef struct{
    int* coords;
    int ndim;
}coord;