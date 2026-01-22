# IAL - Project 2

Implementation of Binary Search Trees and Hash Tables for the IAL course at FIT VUT.

## 📋 What's Inside

- **Binary Search Tree** - Three versions (recursive, iterative, extended)
- **Hash Table** - With collision handling

## 📁 Files

```
IAL_2/
├── btree/              # Binary tree tests
├── hashtable/          # Hash table tests
├── btree-rec.c         # BST - recursive version
├── btree-iter.c        # BST - iterative version
├── btree-exa.c         # BST - extra operations
└── hashtable.c         # Hash table
```

## 🔨 How to Build

### Binary Tree

```bash
cd btree
make btree-rec      # or btree-iter or btree-exa
./btree-rec
```

### Hash Table

```bash
cd hashtable
make
./hashtable-test
```

Clean up:
```bash
make clean
```

## 📚 What Each File Does

### btree-rec.c - Recursive BST

Standard tree operations using recursion:
- Insert, search, delete nodes
- Tree traversals (preorder, inorder, postorder)

### btree-iter.c - Iterative BST

Same operations as recursive version, but using loops instead of recursion.

### btree-exa.c - Extended BST

Additional operations:
- Print tree visually
- Advanced traversal methods

### hashtable.c - Hash Table

Key-value storage with:
- Insert and search
- Delete operations
- Collision handling using linked lists

## 🧪 Testing

Each implementation has test files in its directory. Run them after building to check if everything works.

## 🎓 Course Info

**Course**: IAL (Algorithms)  
**School**: FIT VUT Brno  
**Project**: Project 2

## ⚙️ Requirements

- GCC compiler
- Make

## ✍️ Author

StefieS

---

**Note**: Academic project - follow your school's academic integrity policy.
