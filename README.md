#BST-as-Dictionary

Modular Dictionary, C Programming, Dynamic Memory Allocation, Linked Data Structures.

A simplified UNIX yelp.com (local business directory) as a concrete instance of a dictionary.
Can use it to look up information about a specific business name, such as full address or opening times.

Store the information contained in the file specified in the command line argument. 
Search the binary search tree for records, based on their keys. The keys are read in from stdin. 
Then output the information (the data found) to the output file specified by the second command line parameter. If the key is not found in the tree, output the word NOTFOUND.
The number of key comparisons performed during both successful and unsuccessful lookups will also be written to stdout.

First BST: 

Each record is stored in a separate Node. Note that the entries in the file do not necessarily have unique keys. This BST locates all keys matching the search key including duplicates until a leaf node, and output all the data found.


Second BST:

Searching is more efficient than the first tree.
The Tree is structured such that once a key is found, all duplicate keys can be found without further key comparisons. Every element in the tree is a list. Every record is a node. Every list consists of all nodes with the same name.

Both trees support: make_dictionary, insert, search.
