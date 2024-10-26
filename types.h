enum layerTypes{
    NO_TYPE,
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
    tensor* activation;
    int* padding;
    int* kernelShape;
    int padDimCount;
    int kernelDimCount;
    int activationType;
    int layerType;
    void(*activationFunction)(layer* lay);
}layer;

typedef struct{
    layer* graph;
    int length;
}nn;

typedef struct{
    int* coords;
    int ndim;
}coord;


