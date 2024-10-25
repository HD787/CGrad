#include "internalOperations.c"
int findIndex(tensor* t, int* indices){
    int index = 0;
    int len = t->ndim;
    int count = len - 1;
    for(int i = 0;i < len; i++ ){
        int base = indices[i];
        for(int j = 0; j < count; j++){
            base *= t->shape[len - 1 - j];
        }
        index += base;
        count--;
    }
    return index;
}

coord* findCoords(tensor* t, int index){
    //don't leak this
    coord* coords = malloc(sizeof(coords));
    coords->coords = malloc(sizeof(int) * t->ndim);
    coords->ndim = t->ndim;
    for(int i = t->ndim - 1; i >= 0; i--){
        coords->coords[i] = index % t->shape[i];
        index /= t->shape[i];
    }
    return coords;
}

void deleteCoords(coord* coords){
    //please use
    free(coords->coords);
    free(coords);
}

void repr(tensor* t){
    int index = 0;
    reprRecurse(t, 0, &index);
}

tensor* createTensor(int* shape, int ndim){
    tensor* t = malloc(sizeof(tensor));
    t->ndim = ndim;
    t->shape = malloc(sizeof(int)* ndim);
    memcpy(t->shape, shape, sizeof(int) * ndim);
    int multiplier = 1;
    for(int i = 0; i < ndim; i++) multiplier *= shape[i];
    t->data = malloc(sizeof(float) * multiplier);
    t->length = multiplier;
    return t;
}

tensor* addPadding(tensor* t, int* pads, int padDimCount){
    //pads must be even numbers
    int newShape[t->ndim]; //this may effect the compilation on barebones c11+ compilers
    memcpy(newShape, t->shape, t->ndim);
    for(int i = 1; i < t->padDimCount; i++) newShape[t->ndim - i] = (padDimCount)pads[t->ndim - i] + t->shape[t->ndim - i];
    int multiplier = 1;
    for(int i = 0; i < t->ndim + 1; i++) multiplier *= newShape[i];
    tensor* nt = createTensor(newShape, t->ndim);

    float* newData = calloc(multiplier, sizeof(float));
    int i = 0; int j = 0;

    while(i < t->length && j < multiplier){
        coord* coords = findCoords(t, j);
        int inPad = 0;
        for(int k = 0; k < t->ndim; k++){
            if(coords->coords[k] < (pads[k]/2) || coords->coords[k] > newShape[k] - (pads[k]/2)-1){
                inPad = 1;
                break;
            }
        }
        if(inPad){j++; continue;}
        newData[j] = t->data[i];
        j++;
        i++;
        deleteCoords(coords);
    }
    free(t->data);
    nt->data = newData;
    nt->length = multiplier;
    return nt;
}

void reshape(tensor* t, int* shape, int ndim){
    int size = 1;
    for(int i = 0; i < ndim; i++) size *= shape[i];
    if(size != t->length) printf("invalid reshape");
    memcpy(t->shape, shape, sizeof(int) * ndim);
    t->ndim = ndim;
}

