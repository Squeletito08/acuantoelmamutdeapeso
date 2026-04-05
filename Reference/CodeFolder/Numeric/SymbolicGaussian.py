from sympy import Matrix, symbols, simplify

def symbolic_gaussian_elimination(equations, variables):
    """
    Solves a system of linear equations symbolically using Gaussian elimination.
    
    Parameters:
    - equations: list of equations (e.g., [eq1, eq2, eq3])
    - variables: list of variables (e.g., [x, y, z])
    
    Returns:
    - Dictionary mapping variables to their symbolic solutions
    """
    # Convert equations to augmented matrix
    augmented_matrix = Matrix(equations).transpose().row_join(Matrix([0]*len(equations)))
    
    # Perform Gaussian elimination
    reduced_matrix = augmented_matrix.rref()[0]
    
    # Extract solutions
    solutions = {}
    for i, var in enumerate(variables):
        solutions[var] = simplify(reduced_matrix[i, -1])
    
    return solutions

# Example usage:
x, y, z = symbols('x y z')
eq1 = 2*x + 3*y - z
eq2 = 4*x + y + 2*z
eq3 = -2*x + 5*y - z

equations = [eq1 - 5, eq2 - 6, eq3 + 4]  # Move constants to RHS
variables = [x, y, z]

solution = symbolic_gaussian_elimination(equations, variables)
print("Symbolic Solution:")
for var, val in solution.items():
    print(f"{var} = {val}")

