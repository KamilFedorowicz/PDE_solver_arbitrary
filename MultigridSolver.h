#include "Solver.h"

class Multigrid
{
public:
    Multigrid(std::vector<Solver> solvers): solvers(_solvers){};
    
    void solve()
    {
        
    }
    
private:
    std::vector<Solver> solvers{};
    
};
