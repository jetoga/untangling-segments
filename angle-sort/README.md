# Untagling segments with the usage of angle sort

The algorithm connects a pair of points so that:
- a line going through those points will seperate all of the points into two sets
- the cardinality of these two sets is identical.

The procedure is repeated separately on the remaining two sets of points.

Complexity: O(n*nlog(n))
