cjglover@usc.edu
6404176352
cs104 hw8

compilitation instructions:
$make

to clean up
$make clean

questions:

1. for large inputs, i used public domain books, such as hamlet, frankenstein,
and goethe's faust in both english and german

2. 
for hamlet, hash ran in around .04, splay in about .07
for frankenstein, hash ran in around .1, splay in around 1.4
for faust(german): hash in around .05, splay in .09
for faust(english): hash ran in around .07, splay in .08

3.
the splaytree has guranteed worst case amortized run time log(n) for operations, 
so it should run through the whole document in worst case nlog(n) guranteed
the hashtable has constant average case run time for operations, but linear worst case
so we dont have a gurantee, but on average it should run through the whole document
in linear time, compared to nlog(n) for splaytree's average case

i think splaytree will run well on text which repeat words alot, as predicted
by zipf, since those words will likely be higher up in the tree
hashtable will also run well on text which repeat words alot, so it will not
have to resize often, however, words were are used infrequently are more
damaging to hashtable's run time, since these words will fill a bucket and 
cause collisions, where as in a splaytree they would just sit at the button
this may be why hashtable did comparatively worse with faust in german

4.

an unsorted list implementation would be much slower than both, requiring theta of n^2 to read the file,
 since each time a word is added, the program must search through the list to find if 
the word is in the data structure

a sorted list would perform similar to a splaytree, since each add word operation can
be done in log(n) time [for the sortest list, this can be done using binary search],
so to read the file would gurantee worst case nlog(n) run time, though still slower
than hashtable
in practice a sorted list would probably perform slower than a splaytree, since
splaytree perform well when the same elements are accessed frequently, which is 
the case according to zipf's law

A binary search tree (non rotation) would also be comparable to splaytree if
inputs were random, but the effects of zipf law will give splaytree an avantage
in practice, hashtable will probably perform best again, since the repition of
certain words will prevent hashtable from frequent resizing

A Binary Search Tree with avl rebalancing would gurantee worst case nlog(n) to read the file, but 
it would probably also do worse than splaytree because if a few elements are accessed
multiple times, a splaytree would ensure these elements are near the top. likewise 
hashtable will also be advantaged by repition element accessing






