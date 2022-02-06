# BTree-and-Variants
## Implementation of building and searching B and B+ Trees of variable order d in C++

## Bd tree:
A B-tree or Bd-Tree is a self-balancing tree data structure that maintains sorted data and allows searches, allows sequential access, insertions and deletions in logarithmic time. 
This tree generalizes the Binary Search Tree, allowing for nodes with more than two children. It is commonly used in databases and file systems as it is well suited for storage systems that read and write large blocks of data.

<p>B-Tree of order 5:</p>
<img src="http://vitalflux.com/wp-content/uploads/2015/05/btree-order5.jpg" style="float: left;"/>

## Bd+ tree:
A B+ tree or Bd+ Tree is an m-ary tree with a variable but often large number of children per node. A Bd+ tree can be seen as a Bd-tree in which each node contains only keys, to which an additional level is added at the bottom with linked leaves. Similar to the B-tree, B+ trees are great for data storage for efficient retrieval in filesystems. These trees have a very high fanout (number of pointers to child nodes in a node), which reduces the number of I\O operations required to find an element in the tree.

<p>B+ Tree of order 5</p>
<img src="http://www.cburch.com/cs/340/reading/btree/btree-6.png" style="float: left;"/>
