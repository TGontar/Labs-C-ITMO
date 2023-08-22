#include "stdio.h"
#include "locale.h"
#include "ghoul.h"


int main() {
    setlocale(LC_ALL, "Russian");
    double points[6];
    for (int i = 0; i < 6; i++) {
        scanf("%lf", &points[i]);
    }

    struct Triangle tr1;
    triangalise(points, &tr1);
    tr1.len1 = length(tr1.p1, tr1.p2);
    tr1.len2 = length(tr1.p3, tr1.p2);
    tr1.perimetr = trperimetr(tr1);
    tr1.square = trsquare(tr1);

    printf("Периметр равен: %lf\n", tr1.perimetr);
    printf("Площадь равна: %lf", tr1.square);


    return 0;
}
