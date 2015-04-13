Top-k Association Rules Generation
==================================

Generating top-k association rules base on the priority:
1. Support
2. Confidence
3. Lexicography

Simply make in the outside directory.

The original dataset can be downloaded at:
http://snap.stanford.edu/data/movies.txt.gz

The FP-growth implementation is adapted from **Mr. Christian Borgelt**'s implementation:
http://www.borgelt.net/fpgrowth.html

commands:
./ruleGen [original dataset] [min_sup] [min_conf] [# of rules]

Sample commands:
./ruleGen movies.txt 0.0010318 0 10
