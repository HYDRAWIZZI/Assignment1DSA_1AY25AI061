#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[20];
    float marks;
};

void readStudents(struct Student *ptr, int start, int end) {
    int i;

    for (i = start; i < end; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f",
              &(ptr + i)->roll_no,
              (ptr + i)->name,
              &(ptr + i)->marks);
    }
}

int main(void) {
    struct Student *ptr, *temp, *topper;
    int n, i, choice;
    float sum = 0;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    ptr = malloc(n * sizeof(struct Student));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    readStudents(ptr, 0, n);
    topper = ptr;

    for (i = 0; i < n; i++) {
        sum += (ptr + i)->marks;
        if ((ptr + i)->marks > topper->marks)
            topper = ptr + i;
    }

    printf("\nAverage marks: %.2f\n", sum / n);
    printf("Topper: %s (Roll %d, Marks %.2f)\n",
           topper->name, topper->roll_no, topper->marks);

    printf("\nAdd 2 more students? (1=Yes, 0=No): ");
    if (scanf("%d", &choice) != 1) {
        free(ptr);
        return 1;
    }

    if (choice == 1) {
        temp = realloc(ptr, (n + 2) * sizeof(struct Student));

        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            free(ptr);
            return 1;
        }

        ptr = temp;
        readStudents(ptr, n, n + 2);
        n += 2;
        sum = 0;

        for (i = 0; i < n; i++)
            sum += (ptr + i)->marks;

        printf("Updated average marks: %.2f\n", sum / n);
    }

    free(ptr);
    return 0;
}
