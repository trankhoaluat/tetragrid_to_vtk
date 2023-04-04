#include <vector>
#include <iostream>
#include <fstream>

void tetrahedral_grid_to_vtk(std::ofstream &stream, const std::vector<double> &coords, const std::vector<int> &connectivities)
{
  // 0. write header
  stream << "# vtk DataFile Version 4.0\n"
         << "A TITLE\n"
         << "ASCII\n"
         << "DATASET UNSTRUCTURED_GRID\n";

  const int n_points = coords.size() / 3;
  const int n_cells = connectivities.size() / 4;

  // 1. verify nodes and cells
  if (n_points * 3 != coords.size())
  {
    throw "point coords and total node number are mismatched";
  }

  if (n_cells * 4 != connectivities.size())
  {
    throw "cell connectivities and total cell number are mismatched";
  }

  // 2. write points
  stream << "POINTS " << n_points << " float\n";
  for (const auto var : coords)
  {
    stream << var << '\n';
  }

  // 3. write mesh
  stream << "CELLS " << n_cells /*cell numbers*/ << ' ' << 5 * n_cells /* total number of integer values required to represent the list*/ << '\n';
  for (int i = 0; i < connectivities.size();)
  {
    stream << 4 << ' ' << connectivities[i++] << ' ' << connectivities[i++] << ' ' << connectivities[i++] << ' ' << connectivities[i++] << '\n';
  }

  // 3. write cell types
  stream << "CELL_TYPES " << n_cells << '\n';
  for (int i = 0; i < n_cells; ++i)
  {
    stream << 10 << '\n'; // tetra type
  }
}

int main()
{
  // 1. create points coords
  std::vector<double> coords{22.0, 0.0, 0.0,
                             10.0, 0.0, 1.0,
                             10.0, 0.0, -1.0,
                             10.0, -1.0, 0.0,
                             5.0, -1.0, 0.0,
                             4.0, -1.5, -5.0,
                             4.0, -1.5, 5.0};
  // 2. setup connectivities
  std::vector<int> connectivities{0, 1, 2, 3,
                                  1, 2, 3, 4,
                                  2, 3, 4, 5,
                                  1, 3, 4, 6};
  // 3. output
  std::ofstream stream("Plane_test.vtk");
  tetrahedral_grid_to_vtk(stream, coords, connectivities);
  
  return 0;
}
