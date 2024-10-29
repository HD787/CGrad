enum layerTypes{
    NO_TYPE,
    INPUT,
    LINEAR,
    CONV,
    POOL
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

typedef struct layer{
    tensor* weight;
    tensor* bias;
    tensor* activation;
    int* padding;
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