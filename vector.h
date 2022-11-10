#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/*
    @params
    suffix -    an alias for the type, since, f.e., 'usinged ...' would not work when
                when conustructing the structs and functions. 
    type -      Is the actual data type, that the vector shall hold
*/

#define define_vector(suffix,type) \
    /*
        Config paramters for each vector type
    */ \
    bool throw_error_vector_##suffix = true; \
    bool filter_frees_old_vector_##suffix = true; \
    /*
        Create struct for the type 
    */ \
    typedef struct s_vector_##suffix { \
        type m_value; \
        struct s_vector_##suffix *ptr_next, *ptr_prev; \
    } vector_##suffix; \
\
    /*
        Construtor
    */ \
    vector_##suffix *new_vector_##suffix(type v) { \
        vector_##suffix *n = (vector_##suffix*) calloc(1,sizeof(vector_##suffix)); \
        assert(n != NULL); \
        n->m_value = v; \
        n->ptr_next = NULL; \
        n->ptr_prev = NULL; \
        return n; \
    } \
\
    /*
        Destructor
    */ \
    void destroy_vector_##suffix(vector_##suffix *v) { \
        vector_##suffix *i = v; \
        while(i->ptr_next != NULL) i = i->ptr_next; \
        while(i != NULL) { \
            free(i); \
            i = i->ptr_prev; \
        } \
    } \
\
    type *last_item_vector_##suffix(vector_##suffix *v) { \
        vector_##suffix *i = v; \
        while(i->ptr_next != NULL) i = i->ptr_next; \
        return &(i->m_value); \
    } \
\
    void push_vector_##suffix(vector_##suffix *v,type val) { \
        vector_##suffix *i = v; \
        while(i->ptr_next != NULL) i = i->ptr_next; \
        i->ptr_next = (vector_##suffix*)calloc(1,sizeof(vector_##suffix)); \
        assert(i->ptr_next != NULL); \
        i->ptr_next->ptr_prev = i; \
        i->ptr_next->m_value = val; \
        i->ptr_next->ptr_next = NULL; \
    } \
\
    void pop_vector_##suffix(vector_##suffix *v) { \
        vector_##suffix *i = v; \
        while(i->ptr_next->ptr_next != NULL) i = i->ptr_next; \
        free(i->ptr_next); \
        i->ptr_next = NULL; \
    } \
\
    type *by_index_vector_##suffix(vector_##suffix *v, int index) { \
        if(index < 0) { \
            puts("Error in by_index_...: Index is less then 0"); \
            exit(-1); \
        } \
        vector_##suffix *vi = v;  \
        int i = -1; \
        while(vi != NULL) { \
            i++; \
            if(i == index) break; \
            vi = vi->ptr_next; \
        } \
        if(i == index && vi != NULL) return &(vi->m_value); \
        if(throw_error_vector_##suffix) { \
            puts("Error in by_index_...: Index out of bounds!"); \
            exit(-1); \
        } \
        return NULL; \
    } \
\
    void set_at_index_vector_##suffix(vector_##suffix *v, int index, type val) { \
    } \
\
    void map_over_vector_##suffix(vector_##suffix *v, type(*f)(type)) { \
        vector_##suffix *i = v; \
        while(i != NULL) { \
            i->m_value = (*f)(i->m_value); \
            i = i->ptr_next; \
        } \
    } \
\
    vector_##suffix *filter_over_vector_##suffix(vector_##suffix *v, bool(*f)(type)) { \
        vector_##suffix *n = NULL; \
        vector_##suffix *i = v; \
        while(i != NULL) { \
            if((*f)(i->m_value)) { \
                if(n == NULL) { \
                    n = new_vector_##suffix(i->m_value); \
                }else{ \
                    push_vector_##suffix(n,i->m_value); \
                } \
            } \
            i = i->ptr_next; \
        } \
        return n; \
    } \
