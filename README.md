# Fibonacci Heap C++ Implementation

This C++ code provides an implementation of a Fibonacci heap, a data structure used for priority queues with support for efficient operations. The code includes data structures and functions for various heap operations, including insertion, extraction of the minimum value, and key decrease.

## Table of Contents
- [Introduction](#introduction)
- [Data Structures](#data-structures)
  - [Node](#node)
  - [Fibonacci Heap](#fibonacci-heap)
- [Functions](#functions)
  - [insert](#insert)
  - [heap_union](#heap-union)
  - [print_roots](#print_roots)
  - [print_children](#print_children)
  - [extract_min](#extract_min)
  - [decrease_key](#decrease_key)
- [Private Functions](#private-functions)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This code provides a C++ implementation of a Fibonacci heap, a specialized priority queue data structure known for its efficient operations. The Fibonacci heap is a versatile data structure that supports insertions, extracting the minimum value, and decreasing key values efficiently.

## Data Structures

### Node

The `Node` struct represents a node in the Fibonacci heap. Each node contains the following fields:
- `key`: The value associated with the node.
- `child`: A pointer to the first child of the node.
- `left`: A pointer to the previous node in the circular, doubly-linked list.
- `right`: A pointer to the next node in the circular, doubly-linked list.
- `parent`: A pointer to the parent node.
- `degree`: The number of children of the node.
- `mark`: A boolean flag (1 if marked, 0 otherwise).

### Fibonacci Heap

The `fibonacci_heap` struct represents the Fibonacci heap itself. It includes the following fields:
- `head`: A pointer to the head of the circular, doubly-linked list of root nodes.
- `min`: A pointer to the root node with the minimum key.
- `n_nodes`: The total number of nodes in the heap.
- `n_tree`: The number of root trees in the heap.
- `cmp`: A comparator object for comparing keys.

## Functions

### insert

```cpp
void insert(const T x)
```

- Inserts a new node with the given value `x` into the Fibonacci heap.

### heap_union

```cpp
void heap_union(fibonacci_heap<T, CMP> heap)
```

- Unites the current Fibonacci heap with another heap.

### print_roots

```cpp
void print_roots()
```

- Prints the circular, doubly-linked list of root nodes.

### print_children

```cpp
void print_children(const Node<T>* a)
```

- Prints the children of a given node `a`.

### extract_min

```cpp
T extract_min()
```

- Removes and returns the node with the minimum key from the Fibonacci heap.

### decrease_key

```cpp
void decrease_key(Node<T>* x, T new_key)
```

- Decreases the key of a given node `x` to a new value `new_key`.

## Private Functions

This code includes several private functions such as `linking`, `scambio`, `consolidate`, `cut`, and `cascading_cut`, which are used to implement various operations of the Fibonacci heap data structure.

## Usage

You can use this C++ code to work with Fibonacci heaps for various priority queue operations, such as inserting elements, extracting the minimum value, and decreasing key values. Simply include the `fibonacciheap.hpp` header file and use the provided data structures and functions in your application.

```cpp
#include "fibonacciheap.hpp"

int main() {
    // Create a Fibonacci heap
    fibonacci_heap<int, NodeComparator<int>> fibHeap;

    // Perform operations on the heap
    fibHeap.insert(42);
    int minVal = fibHeap.extract_min();
    // ...

    return 0;
}
```


