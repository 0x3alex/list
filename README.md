# vector

vector is a single header **without** external dependencies, giving you the possibility to create dynamic vectors for every data type or struct you want :D

It is written in macros and is pretty straight forward to use!

The pointer, which is set, when calling 
```c
new_vector_...
```
will always be the head of the vector,  except when set to another address manually

## Vector Config Paramters
``##suffix`` is going to be replaced by the data type, which the vector holds
```C++
    bool throw_error_vector_##suffix = true; //if errors shall be thrown
    bool filter_frees_old_vector_##suffix = true; //if old vectors, when returning new vectors, shall be freed
    bool print_with_ptr_vector_##suffix = false; // if print_all_... prints the value and addresses
```
See [test.c](https://github.com/0x3alex/vector/blob/main/test.c) for some usage examples.

# License

>MIT License
>
>Copyright (c) 2022 Alex
>
>Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the >Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, >and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
>
>The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
>
>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A >PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF >CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
