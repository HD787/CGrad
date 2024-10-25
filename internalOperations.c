void reprRecurse(tensor* t, int level, int* index){
    if(level == t->ndim - 1){
        printf("[");
        for(int i = 0; i < t->shape[level]; i++){
            printf("%f", t->data[(*index)++]);
            if(i < t->shape[level] - 1) printf(", ");
        }
        printf("]");
        return;
    }
    for(int i = 0; i < t->shape[level]; i++){
        printf("[");
        reprRecurse(t, level + 1, index);
        printf("]\n");
    }
}