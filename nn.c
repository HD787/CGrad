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