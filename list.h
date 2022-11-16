#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>

/*
    @params
    suffix -    an alias for the type, since, f.e., 'usinged ...' would not work when
                when conustructing the structs and functions. 
    type -      Is the actual data type, that the list shall hold
*/

#define define_list(suffix,type) \
    /*
        Config paramters for each list type
    */ \
    static bool throw_error_list_##suffix = true; \
    static bool filter_frees_old_list_##suffix = true; \
    static bool print_with_ptr_list_##suffix = false; \
    /*
        Create struct for the type 
    */ \
    typedef struct s_list_##suffix { \
        type m_value; \
        struct s_list_##suffix *ptr_next, *ptr_prev; \
    } list_##suffix; \
\
    /*
        Construtor
    */ \
    static list_##suffix *new_list_##suffix(const unsigned int amount_of_values,...) { \
        if(amount_of_values < 1) return NULL; /*There is nothing todo here*/ \
        list_##suffix *n = (list_##suffix*) calloc(1,sizeof(list_##suffix)); \
        assert(n != NULL); \
        va_list argp; \
        va_start(argp, amount_of_values); \
        /*
            If its just one value, init it like in the first iteration of the constructor
        */ \
        if(amount_of_values == 1) { \
            n->m_value = va_arg(argp, type); \
            n->ptr_next = NULL; \
            n->ptr_prev = NULL; \
            va_end(argp); \
            return n; \
        } \
        /*
            If its more than one, iterate
        */ \
        if(amount_of_values > 1) { \
            list_##suffix *p = NULL,*t = NULL; \
            for(int i = 0; i < amount_of_values; i++) { \
                if(i == 0) { \
                    n->m_value = va_arg(argp, type); \
                    n->ptr_next = NULL; \
                    n->ptr_prev = NULL; \
                    p = n; \
                    continue; \
                } \
                t = (list_##suffix*)calloc(1,sizeof(list_##suffix)); \
                assert(t != NULL); \
                t->m_value = va_arg(argp, type); \
                p->ptr_next = t;  \
                t->ptr_prev = p; \
                t->ptr_next = NULL; \
                p = t; \
            } \
        } \
        va_end(argp); \
        return n; \
    } \
\
    /*
        Destructor
    */ \
    static void destroy_list_##suffix(list_##suffix *v) { \
        if(v == NULL) return; \
        list_##suffix *i = v, *t = NULL; \
        while(i->ptr_next != NULL) i = i->ptr_next; \
        while(i != NULL) { \
            t = i->ptr_prev; \
            free(i); \
            i = t; \
        } \
    } \
\
    static list_##suffix *last_item_list_##suffix(list_##suffix *v) { \
        list_##suffix *i = v; \
        while(i->ptr_next != NULL) i = i->ptr_next; \
        return i; \
    } \
\
    static void push_list_##suffix(list_##suffix *v,type val) { \
        list_##suffix *i = v; \
        while(i->ptr_next != NULL) i = i->ptr_next; \
        i->ptr_next = (list_##suffix*)calloc(1,sizeof(list_##suffix)); \
        assert(i->ptr_next != NULL); \
        i->ptr_next->ptr_prev = i; \
        i->ptr_next->m_value = val; \
        i->ptr_next->ptr_next = NULL; \
    } \
\
    static void pop_list_##suffix(list_##suffix *v) { \
        list_##suffix *i = v; \
        while(i->ptr_next->ptr_next != NULL) i = i->ptr_next; \
        free(i->ptr_next); \
        i->ptr_next = NULL; \
    } \
\
    static void print_list_##suffix(list_##suffix *v, char* formatter) { \
        list_##suffix *i = v; \
        while(i != NULL) { \
            printf(formatter,i->m_value); \
            if(print_with_ptr_list_##suffix)  { \
                printf("v %p\nn %p\np %p\n",i,i->ptr_next,i->ptr_prev); \
            } \
            i = i->ptr_next; \
        } \
    } \
\
    static list_##suffix *by_index_list_##suffix(list_##suffix *v, const unsigned int index) { \
        if(index < 0) { \
            puts("Error in by_index_...: Index is less then 0"); \
            exit(-1); \
        } \
        list_##suffix *vi = v;  \
        int i = -1; \
        while(vi != NULL) { \
            i++; \
            if(i == index) break; \
            vi = vi->ptr_next; \
        } \
        if(i == index && vi != NULL) return vi; \
        if(throw_error_list_##suffix) { \
            puts("Error in by_index_...: Index out of bounds!"); \
            exit(-1); \
        } \
        return NULL; \
    } \
\
    static void insert_after_list_##suffix(list_##suffix *v, type val) { \
        if(v == NULL) return; \
        list_##suffix *n = v->ptr_next; \
        v->ptr_next = (list_##suffix*)calloc(1,sizeof(list_##suffix)); \
        assert(v->ptr_next != NULL); \
        v->ptr_next->ptr_next = n; \
        if(n != NULL) { \
            n->ptr_prev = v->ptr_next; \
        } \
        v->ptr_next->m_value = val; \
        v->ptr_next->ptr_prev = v; \
    } \
\
    static void map_over_list_##suffix(list_##suffix *v, type(*f)(type)) { \
        list_##suffix *i = v; \
        while(i != NULL) { \
            i->m_value = (*f)(i->m_value); \
            i = i->ptr_next; \
        } \
    } \
\
    static list_##suffix *filter_over_list_##suffix(list_##suffix *v, bool(*f)(type)) { \
        list_##suffix *n = NULL; \
        list_##suffix *i = v; \
        while(i != NULL) { \
            if((*f)(i->m_value)) { \
                if(n == NULL) { \
                    n = new_list_##suffix(1,i->m_value); \
                }else{ \
                    push_list_##suffix(n,i->m_value); \
                } \
            } \
            i = i->ptr_next; \
        } \
        if(filter_frees_old_list_##suffix) { \
            destroy_list_##suffix(v); \
        } \
        return n; \
    } \
