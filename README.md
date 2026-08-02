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
- O(1) insert back
- O(1) pop back
- O(1) range sum
- Automatic memory growth and shrinking
- optional automatic free(rsq_free_all)
- Dual sintaxis API(OPP-style and procedural)

## Include and compile
```c
#include "rsq.h"
```
```bash
gcc src/rsq.c examples/rsq_examples.c -I include -o example
```

See `examples/rsq_examples` for usage.

# Vector 

## Features
- O(1) insert back
- O(1) pop back
- O(n) insert
- O(n) erase
- Automatic memory growth and shrinking
- Generic type support(INT , STRING , FLOAT...)
- Custom type suport by passing elemnt size( vect_new_custom )
- optional automatic free(vector_free_all)
- Dual sintaxis API(OPP-style and procedural)

## Include and compile

```c
#include "rsq.h"
```
```bash
gcc src/rsq.c examples/rsq_examples.c -I include -o example
```

See `examples/rsq_examples` for usage.


## Contact
Email: leomontsar@gmail.com  
Open to: small collaborations, code reviews...

This project is licensed under the MIT License — see the [LICENSE](./LICENSE) file for details.
