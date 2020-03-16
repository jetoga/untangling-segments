# Untangling Segments

There are two disjoint sets of N points, where no three points are collinear. The task is to create line segments out of pair of points, where one point is selected from one set and the other from the other, where no segments intersect.

# Proposed solution

Three solutions have been analysed: algorithm based on an angle sort, algorithm based on the Hungarian algorithm and a brute force approach for comparison.

## Bruteforce
Slow but gets the job done.

![Bruteforce result visualization - all the segments are untangled](bruteforce/bruteforce.png)

## Angle sort
Lightning fast, all the segments will be long and skewed towards one direction.

![Angle sort result visualization - long line segments skewed along the top-right/down left axis](angle-sort/angle_sort.png)

## Hungarian algorithm
Slower than angle sort, faster than bruteforce, also creates segments with the smallest total length.

![Hungarian algorithm result visualization - short line segments everywhere](hungarian/hungarian.png)


