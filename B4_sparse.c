#include <stdio.h>

#define MAX 20

typedef struct {
    int row, col, value;
} term;

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX] = {0};
    int starting_pos[MAX] = {0};
    int next_pos[MAX];
    int i, j, k, n;

    n = a[0].value;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = n;

    for (i = 1; i <= n; i++)
        row_terms[a[i].col]++;

    starting_pos[0] = 1;

    for (i = 1; i < a[0].col; i++)
        starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];

    printf("\nrow_terms[]: ");
    for (i = 0; i < a[0].col; i++)
        printf("%d ", row_terms[i]);

    printf("\nstarting_pos[]: ");
    for (i = 0; i < a[0].col; i++)
        printf("%d ", starting_pos[i]);

    for (i = 0; i < a[0].col; i++)
        next_pos[i] = starting_pos[i];

    for (i = 1; i <= n; i++) {
        j = a[i].col;
        k = next_pos[j]++;

        b[k].row = a[i].col;
        b[k].col = a[i].row;
        b[k].value = a[i].value;
    }
}

void display(term a[]) {
    int i;

    printf("Row\tCol\tValue\n");
    for (i = 0; i <= a[0].value; i++)
        printf("%d\t%d\t%d\n", a[i].row, a[i].col, a[i].value);
}

int main(void) {
    int matrix[MAX][MAX];
    int rows, cols, i, j, count = 0;
    term a[MAX * MAX + 1], b[MAX * MAX + 1];

    printf("Enter rows and columns: ");
    if (scanf("%d %d", &rows, &cols) != 2 ||
        rows <= 0 || rows > MAX || cols <= 0 || cols > MAX) {
        printf("Invalid matrix dimensions.\n");
        return 1;
    }

    printf("Enter matrix elements row by row:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1)
                return 1;

            if (matrix[i][j] != 0) {
                count++;
                a[count].row = i;
                a[count].col = j;
                a[count].value = matrix[i][j];
            }
        }
    }

    a[0].row = rows;
    a[0].col = cols;
    a[0].value = count;

    printf("\nOriginal matrix triples:\n");
    display(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples:\n");
    display(b);

    printf("\nTriples are already in row-major order.\n");
    return 0;
}
