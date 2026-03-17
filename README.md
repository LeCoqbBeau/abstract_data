# Abstract Data

The standard C++ containers all have a specific usage. To make sure you understand them, let’s re-implement them!

## Description

Abstract Data is a project in beta from the 42 school. The subject asks us to implement the sequence, associative, and adaptors containers from the 1998 C++ standard.

To help code all this, you are only allowed to use `std::allocator`, `std::string`, `std::numeric_limits`, and the `std::iterator_tags`. Thus, I have implemented the following containers: `list`, `deque`, `vector`, `map`, `set`, `multimap`, `multiset`, `stack`, `queue`, `priority_queue`, `unordered_map`, `unordered_set`, `unordered_multimap`, and `unordered_multiset`. All the source code for these containers is located in the `include` directory.

The second part of the requirements asks us to provide unit tests for our containers to compare them to the standard STL. For these unit tests, I used [Google Test](https://github.com/google/googletest).

The third and bonus part of the project involves implementing the C++11 unordered containers (already covered above), and designing a container that was never implemented in the STL. For this, I designed a custom `grid` container. More on that below!

## Setup and Installation

### Requirements
* The `c++` compiler
* Valgrind (and Cachegrind, optional)
* Doxygen (Tested with 1.16.1; probably works with other versions)

### Compiling and Testing
1.  Run `make gtest` to set up the testing framework.
2.  Run `make all` to compile the project.
3.  Run `make ft` or `make std` to run all unit tests for all standard containers plus the grid.

### Advanced Testing Flags
You can combine specific prefixes before `ft` or `std` for various testing scenarios:
* `make bft` / `make bstd`: Run the bonus tests (unordered containers, tested in C++11).
* `make cft` / `make cstd`: Run the tests with Cachegrind for profiling.
* `make valft` / `make valstd`: Run Valgrind with strict flags (stops at the first error).
* `make valbft` / `make valbstd`: Run Valgrind on the bonus tests.
* `make cbft` / `make cbstd`: Run Cachegrind on the bonus tests.

### Documentation
I have set up Doxygen to easily generate and view the project's documentation.
I have only documented my grid container because I am only asked to do this.
* Run `make doc` to generate the HTML documentation files.
* Run `make odoc` to automatically open the generated documentation in your default web browser (using the `open` command).

## Container Details & Fun Facts

### Vector
The easiest container to implement; I finished coding it in less than 3 hours. It is a simple contiguous array in memory.

### Deque
The devil in disguise, and probably the hardest container to fully grasp in the 1998 STL. The engine of a deque lies in its iterators, which handle almost everything under the hood.

### List
The first container I started and a pretty simple one. It involves lots of pointer tricks, but nothing too difficult.

### Queue / Stack
Basically limited sequence containers. I completed them in less than an hour.

### Priority Queue
This one is not as easy as the other adaptors. I had to research how a heap is made, because it's essentially a vector disguised as a heap.

### Set / Multiset / Map / Multimap
These were probably the most challenging containers to implement. Building Red-Black Trees from scratch required rigorous testing and careful attention to the balancing logic.

### Unordered Set / Multiset / Map / Multimap
These are hashmaps with buckets to handle conflicts! The iterators are pretty unique, but building them was very fun and rewarding.

### Grid
This one is my own custom baby! It is a stack-allocated double array where the internal data is stored like `value_type[M][N]`. It is heavily inspired by C++11's `std::array`, though `std::array` stores the data in a single dimension as `value_type[N]`.


## Credits
- AI, for debugging, explanation (no blind vibecoding tho), and grammar for the README.md (you're reading it right now!!!! i still wrote it myself :D)
- [cplusplus.com](https://cplusplus.com) and [cppreference.com](https://cppreference.com): for documentation and some helper function (in other files)
- [EASTL](https://github.com/electronicarts/EASTL): for some code too