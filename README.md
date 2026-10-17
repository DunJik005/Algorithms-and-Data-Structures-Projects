Algorithms and Data Structures Coursework

This repository contains coursework implemented in Python and C++ for Algorithms and Data Structures 1 and 2 at the University of Belgrade School of Electrical Engineering. The programs explore linked lists, graphs, searching, tree structures, and process scheduling through interactive console applications. The collection also includes a basic command line interpreter written in C++.

Python Linked Lists and Graphs

The asp1 domaci123 folder contains a custom singly linked list and a directed weighted graph built using linked lists. The list supports insertion at a selected position, searching, deletion, file loading, and traversal.

The graph program in dz1.py supports adding and removing vertices and edges, displaying adjacency lists, and loading graph data from a text file. Breadth first search explores reachable vertices, while Dijkstra's algorithm finds a shortest path and its total weight. The program uses a console menu and checks input such as vertex identifiers and negative edge weights. The linked list implementation is provided in zadatak1LinkedList.py.

Temperature Searching and Guest Records

The asp2domaci1 folder contains two separate C++ programs.

The asp2dz1p1.cpp program stores up to 365 temperature measurements in an array. Measurements can be entered manually, loaded from a file, or generated randomly. Manually entered and imported values must already be sorted, while generated values are sorted using bubble sort. Binary search is used to locate the first and last occurrence of a temperature and to find measurements within a selected range.

The asp2dz1p2.cpp program manages guest records in a binary search tree ordered by points. Each record contains a point value, a first name, and a last name. The program supports console and file input, searching by points, increasing points, displaying the tree, and finding the guest at a selected position in ascending order. It rebuilds the tree into a balanced shape after loading records or updating points and uses iterative traversals for several tree operations.

Tree Structures and Process Scheduling

The asp2domaci2 folder contains a process scheduling simulation built around balanced search trees. The main implementation in asp2dz2p1.cpp uses a tree with two, three, or four children per internal node. A separate implementation using a red black tree is included in redblack.cpp.

Process records track names, required execution time, maximum waiting time, accumulated waiting time, and completed execution time. The console menus provide operations for inserting, searching, updating, and deleting processes, loading records from files, and inspecting tree representations.

The main simulation can advance by a single time slice or run until completion. Process timing values are updated as execution progresses, and unfinished processes are returned to the tree. A complete simulation writes its progress to simulacija.txt. The folder includes sample inputs in test1.txt and test2.txt.

Command Line Interpreter

The asp2domaci3 folder contains a C++ interpreter with separate components for tokenization, command creation, input handling, and error reporting. The available commands are echo, time, date, touch, and wc. Word and character counting are supported by wc, while commands that consume input can read from standard input, quoted text, or a file.

The implementation uses abstract interfaces, inheritance, and smart pointers to separate command behavior from input sources. This version provides basic command execution. Pipelines and output redirection are not implemented in the supplied source files.

Running the Programs

The assignments are separate programs rather than one application. Run dz1.py with Python 3 while keeping zadatak1LinkedList.py in the same folder. The Python code uses the standard library.

Build each C++ program in asp2domaci1 separately. In asp2domaci2, the supplied CMakeLists.txt selects asp2dz2p1.cpp and requests C++20 and CMake 4.0 or newer. Build redblack.cpp separately if you want to use the alternative implementation, since it has its own main function.

For the interpreter, build main.cpp together with the implementation files in the commands, core, io, and errors folders. The collection has no shared build configuration. Most console prompts and source comments are written in Serbian.

Acknowledgements

Source comments credit course materials for selected traversal and tree construction routines. The main process scheduling implementation also references tree implementations by Simon Tatham and GitHub user gabrieledcjr. These acknowledgements are preserved in the source files.
