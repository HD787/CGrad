#include <stdarg.h>
// nn* createNn(int count, ...){
//     va_list args;
//     va_start(args, count);
//     nn* newnn = malloc(sizeof(nn));
//     newnn->layers = malloc(sizeof(layer) * count)
//     newnn->length = count;
//     for(int i = 0; i < count; i++) nn->layers[i] = va_arg(args, layer);
//     va_end(args);
//     return newnn;
// }

void activate(nn* n){}

void gradient(nn* n){}

void conv2dActivation(layey* lay){
    if(padDimCount > 4 || padDimCount < 2) {printf("invalid dimension count for pool"); return NULL;}
    tensor* nt = ntaddPadding(t, padding, padDimCount);
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
    lay->activation = nt;
}