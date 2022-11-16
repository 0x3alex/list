#include "list.h"
#include <stdio.h>

struct point {
    int x,y;
};

//needs to be done OUTSIDE a function
define_list(uint,int); 
define_list(s,struct point *);
define_list(char_ptr, char*);

int timesTwo(int i) {return i*2;}
bool is4(int i) {return i == 4;}

struct point *test(struct point *p) {
    p->x *= 2;
    return p;
}

int main(void) {
    list_uint *v = new_list_uint(3,1,2,3);
    //print_with_ptr_list_uint = true; //config option
    insert_after_list_uint(by_index_list_uint(v,1),1337);
    by_index_list_uint(v,0)->m_value = 69;
    print_list_uint(v,"%d\n");

    list_uint *v2 = filter_over_list_uint(v,&is4);  //v is freed here if not configured
                                                        //otherwise
    map_over_list_uint(v2, &timesTwo);
    //print_list_uint(v2,"%d\n");
    destroy_list_uint(v2);

    list_char_ptr *c = new_list_char_ptr(2,"hello","world");
    push_list_char_ptr(c,"!");
    print_list_char_ptr(c,"%s\n");
    destroy_list_char_ptr(c);
    struct point p1 = {
        .x = 1,
        .y = 1
    }, p2 = {
        .x = 3,
        .y = 5
    }, p3 = {
        .x = 10,
        .y = 11
    }, p4 = {
        .x = 1337,
        .y = 420
    };
    list_s *s = new_list_s(3,&p1,&p2,&p3);
    print_list_s(s,"%p\n");
    insert_after_list_s(by_index_list_s(s,1),&p4);
    puts("---");
    printf("%d\n",by_index_list_s(s,0)->m_value->x);
    map_over_list_s(s,&test);
    printf("%d\n",by_index_list_s(s,0)->m_value->x);
    print_list_s(s,"%p\n");
    destroy_list_s(s);
}
