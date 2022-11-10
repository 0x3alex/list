#include "vector.h"
#include <stdio.h>

define_vector(uint,int); 
define_vector(char_ptr, char*);

int timesTwo(int i) {return i*2;}
bool is4(int i) {return i == 4;}

int main(void) {
    vector_uint *v = new_vector_uint(1);
    push_vector_uint(v,2);
    map_over_vector_uint(v, &timesTwo);
    printf("%d\n",*last_item_vector_uint(v));

    vector_uint *v2 = filter_over_vector_uint(v,&is4);
    printf("%d\n",*by_index_vector_uint(v2,0));
    destroy_vector_uint(v2);

    vector_char_ptr *c = new_vector_char_ptr("hello");
    throw_error_vector_char_ptr = 1;
    push_vector_char_ptr(c,"world");
    printf("%s\n",*by_index_vector_char_ptr(c,1));
    pop_vector_char_ptr(c);
    printf("%s\n",*last_item_vector_char_ptr(c));
    destroy_vector_char_ptr(c);
}