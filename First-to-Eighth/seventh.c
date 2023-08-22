#include "stdio.h"
#include "math.h"
#include "locale.h"

enum Lamps {
    nakalivanya = 1,
    day_light = 2,
    galogen = 3,
    neon = 4
};

struct Triangle {
    double x1;
    double y1;
    double x2;
    double y2;
    double x3;
    double y3;
    double perimetr;
};

union CardReader {
    int cr;
    struct {
        unsigned state: 1;
        unsigned SDactive: 1;
        unsigned CLactive: 1;
        unsigned MSactive: 1;
    };
};

double perimetr1(struct Triangle tr) {
    double len1 = sqrt(pow((tr.x2 - tr.x1), 2) + pow((tr.y2 - tr.y1), 2));
    double len2 = sqrt(pow((tr.x3 - tr.x2), 2) + pow((tr.y3 - tr.y2), 2));
    double len3 = sqrt(pow((tr.x3 - tr.x1), 2) + pow((tr.y3 - tr.y1), 2));
    double p = len1 + len2 + len3;
    return p;

}

int main() {
    setlocale(LC_ALL, "Russian");
    enum Lamps gal = galogen;
    printf("%d\n", gal);

    double points[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    struct Triangle tr1;
    tr1.x1 = points[0];
    tr1.y1 = points[1];
    tr1.x2 = points[2];
    tr1.y2 = points[3];
    tr1.x3 = points[4];
    tr1.y3 = points[5];
    tr1.perimetr = perimetr1(tr1);

    double ans = tr1.perimetr;
    printf("%lf\n", ans);

    int values;
    printf("¬ведите число в 16-ричной системе счислени€: ");
    scanf("%x", &values);
    union CardReader cr1 = {values};
    printf("State: %d\n", cr1.state);
    printf("SD card active: %d\n", cr1.SDactive);
    printf("Compact flash active: %d\n", cr1.CLactive);
    printf("Memory stick active: %d\n", cr1.MSactive);

    return 0;
}
