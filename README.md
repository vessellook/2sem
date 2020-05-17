# 2sem
This repository contains course works of 1st year Bachelor student.

There is no useful samples for you

# In details

This repo consists of 2 folders:
- **dynamic_array** -- you find here a small **C** program with implementation of structure **DynamicArray**.
You can resize this array, set items, get items, and change all items by callback function (**map** array).
That's all
- **sequence** -- you find here a small **C++** program. File **input_in_mess.cpp** contains
implementation of simple shell which provides operations with square matrices. THis repo contains following classes:
    - **DynamicArray** -- class provides protection against access to unallocated memory
    (**SafeDynamicArray** just the same but also uses class 
    - **SinglyLinkedList**
    - **ISequence** -- abstract class with two derived classes: ArraySequence and LinkedListSequence (it's course work, not my will)
    - **ArraySequence** -- contains class field of type **DynamicArray**
    - **LinkedListSequence** -- contains class field of type **SinglyLinkedList**
    - **IMatrix** -- abstract class of square matrix with two derived classes: ArrayMatrix and ListMatrix
    - **ArrayMatrix** -- implementation is based on **ArraySequence**
    - **ListMatrix** -- implementation is based on **LinkedListSequence**. Copy-Paste of **ArrayMatrix**
