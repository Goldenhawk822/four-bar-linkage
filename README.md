# four-bar-linkage
A repository for various four bar linkage calculations and manipulations (a work in progress)

Plot 5 points, Ao, Bo, A1, B1, and C. For ease of visualization, put Ao and Bo near the bottom, A1 and B1 in the middle, and C near the top, 
and keep the "B"s to the right of the "A"s. Connect Ao to A1, Bo to B1, A1 to B1, A1 to C and B1 to C. Now you have a fourbar.
By keeping Ao and Bo locked in place and moving A1, it's possible to determine the location of B1 and C by maintaining the same lengths
between points.

As for the "fourbarsolver.h" I don't recall the syntax off the top of my head, but it was intended to solve for one "half linkage"
and any pair of "half linkages" that correspond to the same changes in the position of C can be connected into a fourbar.
