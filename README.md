# Structures for C
The project will have some libraries with some popular data structures like RSQ, Segment Tree, Vectors...

# Project and Objective
I'm Gael and with this project I will learn some new data structures, how libraries work in C, and low-level optimization. 
My goal with this project is to master these concepts

# Clone 
## Https 
```bash
git clone https://github.com/Gael346/Structures-for-c-.git
```
## Github CLI
```bash
gh repo clone Gael346/Structures-for-c-
```
# RSQ (Range Sum Query)

## Features
- O(1) Push and pop back
- O(1) Get element
- O(1) Query range sum
- Automatic memory growth and shrinking
- Optional automatic free(rsq_free_all)
- Dual sintaxis API(OPP-style and procedural)

## Include and compile
```c
#include "rsq.h"
```
```bash
gcc src/rsq.c examples/rsq_examples.c -I include -o rsq_examples
```

See `examples/rsq_examples` for usage.

# Vector 

## Features
- O(1) Get element
- O(1) Push and pop back
- O(n) Insert and erase
- Automatic memory growth and shrinking
- Generic type support(INT , STRING , FLOAT...)
- Custom type suport by passing elemnt size( vect_new_custom )
- Optional automatic free (vector_free_all)
- Dual sintaxis API(OPP-style and procedural)
- User-friendly data extraction macros (VGET , VDATE , PARSE) 

## Include and compile

```c
#include "vector.h"
```
```bash
gcc src/vector.c examples/vector_examples.c -I include -o vector_examples
```

See `examples/vector_examples` for usage.


## Contact
Email: leomontsar@gmail.com  
Open to: small collaborations, code reviews...

This project is licensed under the MIT License — see the [LICENSE](./LICENSE) file for details.
