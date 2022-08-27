/*!
  @file testing.cpp
  @brief Tests received roots.
*/

#include "sqr_solver.hpp"
#include "compare.hpp"
#include "test_SqrEq.hpp"
#include "io.hpp"

#define MAX_LEN 100

static char warning_error[57] = "ERROR: an error occurred while trying to get file data.";

int test_SqrEq(void)
{
    double x1 = 0;
    double x2 = 0;

    double a = 0;
    double b = 0;
    double c = 0;

    int check_fscanf = 0;
    int right_count = 0;
    int test_num = 0;

    double root1 = 0;
    double root2 = 0;

    char name_test_file[MAX_LEN];

    int count_ans = -1;

    get_name_test_file(name_test_file, MAX_LEN);

    FILE *test_file;
    if ((test_file = fopen(name_test_file, "r")) == NULL) {
        printf("ERROR: failed to open file %s\n", name_test_file);
        return 1;
    }

    printf("Function \"solver\" test starts now!\n");


    do {

        check_fscanf = fscanf(test_file, "%lg %lg %lg %d", &a, &b, &c, &right_count);

        if (check_fscanf == EOF) {
            return 0;
        }
        else if (check_fscanf != 4) {
            printf("%s\n", warning_error);
            return 1;
        }

        switch(right_count)
        {
            case INFINITY_ROOT:
                break;

            case TWO_ROOT:
                if (fscanf(test_file, "%lg %lg", &root1, &root2) == EOF) {
                    printf("%s\n", warning_error);
                    return 1;
                }
                break;

            case ONE_ROOT:
                if (fscanf(test_file, "%lg", &root1) == EOF) {
                    printf("%s\n", warning_error);
                    return 1;
                }
                break;
            case ZERO_ROOT:
                break;

            default:
                printf("Incorrect amount of roots in testing\n");
                break;
        }

        printf("Test #%d\n", ++test_num);

        solver(a, b, c, &count_ans, &x1, &x2);

        test_compare(a, b, c, count_ans, x1, x2, right_count, root1, root2);

    } while (check_fscanf == 4);

    if (fclose(test_file) == EOF) {
        printf("ERROR: failed to close file %s\n", name_test_file);
        return 1;
    }

    return 0;
}



void test_compare(double a, double b, double c, int count_ans, double x1, double x2,
                  int right_count, double root1, double root2)
{

    if(!(count_ans == right_count && is_equal(x1, root1) && is_equal(x2, root2))) {
                printf("Received coefficients: a = %lg b = %lg c = %lg\n", a, b, c);
                printf("FAILED:   count_ans = %d, x1 = %lg, x2 = %lg\n"
                       "EXPECTED: count_ans = %d, x1 = %lg, x2 = %lg\n",
                        count_ans, x1, x2, right_count, root1, root2);
    }
    else
        printf("SUCCESS!\n");
  
    printf("\n");
}
