# Usage of the Hungarian Algorithm in untagling the segments

The Hungarian algorithm is used to solve the problem of finding such a pairing of points from two sets, that the total length of line segments will be as short as possible. 

The triangle inequality might be used to prove that line segments created in this way will not intersect. 
Two segments (P1, P2) and (R1, R2), which intersect at a point M form two triangles e.g. (P1, R1, M) and (P2, R2, M). Because there are no three collinear points the triangles have an area greater than zero. Thus the segment (P1, R1) is shorter than the total length of the segments (M, P1) and (M, R1). Similarly (P2, R2) is shorter than the total length of segments (M, P2) and (M, R2). The total length of segments (P1, R1) and (P2, R2) is thus shorter than the total length of the following segments: (M, P1), (M, P2), (M, R1), (M, R2), that is (P1, P2) and (R1, R2). In other words, by untangling any two segments, the total length of the segments is lowered. 

Complexity: O(n * n * n * n)
