#include "vector.h"
#include <stdio.h>

//needs to be done OUTSIDE a function
define_vector(uint,int); 
define_vector(char_ptr, char*);

int timesTwo(int i) {return i*2;}
bool is4(int i) {return i == 4;}

int main(void) {
    vector_uint *v = new_vector_uint(3,1,2,3);
    //print_with_ptr_vector_uint = true; //config option
    insert_after_vector_uint(by_index_vector_uint(v,1),1337);
    // map_over_vector_uint(v, &timesTwo);
    by_index_vector_uint(v,0)->m_value = 69;
    print_vector_uint(v,"%d\n");

    vector_uint *v2 = filter_over_vector_uint(v,&is4);  //v is freed here if not configured
                                                        //otherwise
    map_over_vector_uint(v2, &timesTwo);
    //print_vector_uint(v2,"%d\n");
    destroy_vector_uint(v2);

    vector_char_ptr *c = new_vector_char_ptr(2,"hello","world");
    push_vector_char_ptr(c,"!");
    print_vector_char_ptr(c,"%s\n");
    //printf("%s\n",by_index_vector_char_ptr(c,1)->m_value);
    //pop_vector_char_ptr(c);
    //printf("%s\n",*last_item_vector_char_ptr(c));
    destroy_vector_char_ptr(c);
}
