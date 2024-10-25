enum layerTypes{
    NOTYPE,
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

typedef struct{
    tensor* weight;
    tensor* activation;
    int* padding;
    int activationType;
    int LayerType;
}layer;

typedef struct{
    layer* layers;
    int length;
}nn;

typedef struct{
    int* coords;
    int ndim;
}coord;


