#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];
} polynomial;

polynomial add(polynomial a, polynomial b) {
    polynomial c;
    int i;

    c.degree = a.degree > b.degree ? a.degree : b.degree;

    for (i = 0; i <= c.degree; i++) {
        int exp = c.degree - i;
        float x = exp <= a.degree ? a.coef[a.degree - exp] : 0;
        float y = exp <= b.degree ? b.coef[b.degree - exp] : 0;
        c.coef[i] = x + y;
    }

    return c;
}

void display(polynomial p) {
    int i, first = 1;

    for (i = 0; i <= p.degree; i++) {
        float c = p.coef[i];
        int exp = p.degree - i;

        if (c == 0)
            continue;

        if (!first && c > 0)
            printf(" + ");
        else if (c < 0)
            printf(first ? "-" : " - ");

        if (c < 0)
            c = -c;

        if (exp == 0)
            printf("%g", c);
        else if (exp == 1)
            printf("%gx", c);
        else
            printf("%gx^%d", c, exp);

        first = 0;
    }

    if (first)
        printf("0");

    printf("\n");
}

polynomial readPolynomial(void) {
    polynomial p;
    int i;

    printf("Enter degree: ");
    if (scanf("%d", &p.degree) != 1 || p.degree < 0 || p.degree > 100) {
        printf("Invalid degree.\n");
        p.degree = -1;
        return p;
    }

    printf("Enter coefficients from highest degree to constant:\n");
    for (i = 0; i <= p.degree; i++) {
        if (scanf("%f", &p.coef[i]) != 1) {
            p.degree = -1;
            return p;
        }
    }

    return p;
}

int main(void) {
    polynomial a, b, c;

    printf("First polynomial:\n");
    a = readPolynomial();
    if (a.degree < 0)
        return 1;

    printf("Second polynomial:\n");
    b = readPolynomial();
    if (b.degree < 0)
        return 1;

    c = add(a, b);

    printf("A(x) = ");
    display(a);

    printf("B(x) = ");
    display(b);

    printf("A(x) + B(x) = ");
    display(c);

    return 0;
}
