#include <iostream>
#include "Grid.h"
#include "Multigrid.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Grid grid1(0, 0, 1, 1, 10, 10);
    Grid grid2(0, 1, 1, 2, 10, 10); // above grid 1
    Grid grid3(0, 2, 1, 3, 10, 10); // above grid 2
    
    Multigrid multigrid;
    multigrid.addGrid(grid1);
    multigrid.addGrid(grid2);
    multigrid.addGrid(grid3);
    
    multigrid.displayWalls();
    
    return 0;
}
