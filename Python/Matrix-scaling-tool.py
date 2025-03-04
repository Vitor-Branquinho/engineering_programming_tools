import numpy as np

num_of_variables = int(input("Type the number of variables in the system of linear equations: "))
num_of_equations = int(input("Type the number of equations in the system: "))

i = 0
j = 0
variables = []
variables_l = []
coefficients = []
coefficients_l = []
results = []
results_l = []

if num_of_equations < num_of_variables:
    print("Indeterminate system. There are infinite solutions.")
else:
    while i < num_of_variables:
        variables = []
        variable = input(f"Enter the variable {i+1}: ")
        variables.append(variable)
        variables_l.append(variables)
        i += 1
    variables_array = np.array(variables_l)

    while j < num_of_equations:
        coefficients = []
        results = []
        for index in range(num_of_variables):
            coefficient = float(input(f"Enter the coefficient of the variable {variables_l[index][0]} in the equation {(j + 1)}: "))
            coefficients.append(coefficient)

        result = float(input(f"Enter the result of the equation {(j + 1)}: "))
        results.append(result)
        results_l.append(results)
        j += 1

        coefficients_l.append(coefficients)


    coefficients_array = np.array(coefficients_l)
    results_array = np.array(results_l)

    print("\n")

    print(f"Coefficients Matrix:\n {coefficients_array}")
    print(f"Variables Matrix:\n {variables_array}")
    print(f"Results matrix:\n {results_array}")
    print("\n")

    print('Let us scale the augmented matrix:')


    def printing_augmented_matrix(matrix1, matrix2):
        for lin in range(0, num_of_equations):
            coeffic = []
            for col in range(0, num_of_variables):
                coeffic.append(float(matrix1[lin][col]))
            resulting = float(matrix2[lin][0])
            print(f"| {coeffic} | {resulting} |")

        return

    printing_augmented_matrix(coefficients_array, results_array)
    print("\n")

    pos_signal = False

    if num_of_variables == num_of_equations:
        for column in range(0, num_of_variables):
            initial = column
            # Starting the scaling by turning every first coefficient into 1
            for line in range(initial, num_of_variables):
                if coefficients_array[line][column] != 0 and coefficients_array[line][column] != 1:
                    multiplier = 1/coefficients_array[line][column]
                    coefficients_array[line] = np.multiply(coefficients_array[line], multiplier)
                    results_array[line] = np.multiply(results_array[line], multiplier)
                if line == initial:
                    if coefficients_array[line][column] > 0:
                        pos_signal = True

            printing_augmented_matrix(coefficients_array, results_array)
            print("\n")

            repeated_lines = []
            lines_removed = 0
            possible = False

            for line in range(num_of_equations - 1):
                for assist_line in range(line + 1, num_of_equations):
                    if np.array_equal(coefficients_array[line], coefficients_array[assist_line]) and np.array_equal(
                            results_array[line], results_array[assist_line]):
                        repeated_lines.append(assist_line)

            lines_removed = len(repeated_lines)
            if num_of_variables == (num_of_equations - lines_removed):
                possible = True
            elif num_of_variables > (num_of_equations - lines_removed):
                possible = True
                print("Indeterminate system. There are infinite solutions.")
                dep_term = str(coefficients_array[0][0]) + variables_array[0][0]
                dep_result = ''
                term = ""
                term += (str(results_array[0]) + " + ")

                for i in range(1, num_of_variables):
                    coefficients_array[0][i] = (-1) * coefficients_array[0][i]

                for i in range(1, num_of_variables):
                    term += ( "(" + str(coefficients_array[0][i]) + variables_array[i][0] + ")")
                    if i < (num_of_variables - 1):
                        term += " + "

                dep_result += term

                print(f"Final solution: {dep_term} = {dep_result}")
                exit()

            if possible:

                preservation = 0

                for line in range(0, num_of_variables):
                    if line == column:
                        preservation = line

                for line in range(0, num_of_variables):
                    if line == preservation:
                        pass
                    elif coefficients_array[line][column] != 0:
                        if (pos_signal and coefficients_array[line][column] > 0) or (not pos_signal and coefficients_array[line][column] < 0):
                            multiplication_factor = coefficients_array[line][column]
                            for columns in range(0, num_of_variables):
                                coefficients_array[line][columns] += ((-1) * coefficients_array[preservation][columns] * multiplication_factor)
                            results_array[line] += ((-1) * results_array[preservation] * multiplication_factor)
                        elif (pos_signal and coefficients_array[line][column] < 0) or (not pos_signal and coefficients_array[line][column] > 0):
                            multiplication_factor = (-1) * coefficients_array[line][column]
                            for columns in range(0, num_of_variables):
                                coefficients_array[line][columns] += (coefficients_array[preservation][columns] * multiplication_factor)
                            results_array[line] += (results_array[preservation] * multiplication_factor)

                printing_augmented_matrix(coefficients_array, results_array)
                print("\n")

            print("The matrix was scaled. The solution is: \n")

            def printing_solutions(var_matrix, res_matrix):
                for lin in range(0, num_of_variables):
                    print(f"| {var_matrix[lin][0]} |  | {res_matrix[lin][0]:.5f} |")

                return

            printing_solutions(variables_array, results_array)
            print("\nor\n")

            for item in range(0, num_of_variables):
                print(f"{variables_array[item][0]} = {results_array[item][0]:.5f} ")

    else:
    # Starting the scaling by turning every first coefficient into 1
        for line in range(0, num_of_equations):
            if coefficients_array[line][0] != 0 and coefficients_array[line][0] != 1:
                multiplier = 1/(coefficients_array[line][0])
                coefficients_array[line] = np.multiply(coefficients_array[line], multiplier)
                results_array[line] = np.multiply(results_array[line], multiplier)

        printing_augmented_matrix(coefficients_array, results_array)

        repeated_lines = []
        lines_removed = 0
        possible = False

        for line in range(num_of_equations - 1):
            for assist_line in range(line + 1, num_of_equations):
                if np.array_equal(coefficients_array[line], coefficients_array[assist_line]) and np.array_equal(results_array[line], results_array[assist_line]):
                    repeated_lines.append(assist_line)

        lines_removed = len(repeated_lines)
        if num_of_variables == (num_of_equations - lines_removed):
            possible = True
        elif num_of_variables > (num_of_equations - lines_removed):
            possible = True
            print("Indeterminate system. There are infinite solutions.")
            dep_term = ''
            dep_term += (str(coefficients_array[0][0]) + variables_array[0])
            dep_result = ''
            for i in range(1, num_of_equations):
                term = (str(coefficients_array[0][i]) + variables_array[i])
                if i != (num_of_equations - 1):
                    dep_result += (term + " + ")
                else:
                    dep_result += term

            print(f"Final solution: {dep_term} = {dep_result}")
            exit()

        def printing_augmented_dependent_matrix(matrix1, matrix2):
            for lin in range(0, (num_of_equations - lines_removed)):
                coeffic = []
                for col in range(0, num_of_variables):
                    coeffic.append(float(matrix1[lin][col]))
                resulting = float(matrix2[lin][0])
                print(f"| {coeffic} | {resulting} |")

            return

        if not possible:
            print("There is no solution for the system.")
        else:
            print("\n")
            for rp_line in repeated_lines:
                coefficients_array = np.delete(coefficients_array, rp_line, axis=0)
                results_array = np.delete(results_array, rp_line, axis=0)

            print("Simplified Matrix:")

            printing_augmented_dependent_matrix(coefficients_array, results_array)

            print("\n")

            for column in range(0, num_of_variables):
                initial = column

                preservation = 0

                for line in range(0, num_of_variables):
                    if line == column:
                        preservation = line

                for line in range(0, num_of_variables):
                    if line == preservation:
                        pass
                    elif coefficients_array[line][column] != 0:
                        if (pos_signal and coefficients_array[line][column] > 0) or (
                                not pos_signal and coefficients_array[line][column] < 0):
                            multiplication_factor = coefficients_array[line][column]
                            for columns in range(0, num_of_variables):
                                coefficients_array[line][columns] += (
                                            (-1) * coefficients_array[preservation][columns] * multiplication_factor)
                            results_array[line] += ((-1) * results_array[preservation] * multiplication_factor)
                        elif (pos_signal and coefficients_array[line][column] < 0) or (
                                not pos_signal and coefficients_array[line][column] > 0):
                            multiplication_factor = (-1) * coefficients_array[line][column]
                            for columns in range(0, num_of_variables):
                                coefficients_array[line][columns] += (coefficients_array[preservation][columns] * multiplication_factor)
                            results_array[line] += (results_array[preservation] * multiplication_factor)

                printing_augmented_dependent_matrix(coefficients_array, results_array)
                print("\n")

            theres_deleted = False
            impossible = False

            for line in range(num_of_equations - lines_removed):
                if np.all(coefficients_array[line] == 0) and results_array[line] == 0:
                        coefficients_array = np.delete(coefficients_array, line, axis=0)
                        results_array = np.delete(results_array, line, axis=0)
                        theres_deleted = True
                elif np.all(coefficients_array[line] == 0) and results_array[line] != 0:
                        impossible = True

            if theres_deleted:
                printing_augmented_dependent_matrix(coefficients_array, results_array)
                print("Indeterminate system. There are infinite solutions.\n")
                exit()
            elif impossible:
                printing_augmented_dependent_matrix(coefficients_array, results_array)
                print("Impossible system.")
                exit()

            print("The matrix was scaled. The solution is: \n")


            def printing_solutions(var_matrix, res_matrix):
                for lin in range(0, num_of_variables):
                    print(f"| {var_matrix[lin][0]} |  | {res_matrix[lin][0]:.5f} |")

                return


            printing_solutions(variables_array, results_array)
            print("\nor\n")

            for item in range(0, num_of_variables):
                print(f"{variables_array[item][0]} = {results_array[item][0]:.5f} ")