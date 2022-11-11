# vector

vector is a single header **without** external dependencies, giving you the possibility to create dynamic vectors for every data type or struct you want :D

It is written in macros and is pretty straight forward to use!

## Vector Config Paramters
``##suffix`` is going to be replaced by the data type, which the vector holds
```C++
    bool throw_error_vector_##suffix = true; //if errors shall be thrown
    bool filter_frees_old_vector_##suffix = true; //if old vectors, when returning new vectors, shall be freed
    bool print_with_ptr_vector_##suffix = false; // if print_all_... prints the value and addresses
```
See [test.c](https://github.com/0x3alex/vector/blob/main/test.c) for some usage examples.

