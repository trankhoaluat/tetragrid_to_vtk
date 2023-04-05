# tetragrid_to_vtk
This is a simple demostration on how to write a tetrahedral grid to VTK (ASCII). The grid contains only tetrahedral elements.

## The grid format:
1. a vector of 3D coordinates: coords[p1_x, p1_y, p1_z, p2_x, p2_y, p2_z, ... , pn_x, pn_y, pn_z];
2. a vector of connectivities: connectivities[n0, n1, n2, n3 /\*1st cell\*/, n2, n3, n4, n5 /\*2nd cell\*/ ... ];
