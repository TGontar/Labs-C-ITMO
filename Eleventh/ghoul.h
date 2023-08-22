#ifndef ELEVENTH_GHOUL_H
#define ELEVENTH_GHOUL_H

struct Point {
    double x;
    double y;
};

struct Triangle {
    struct Point p1;
    struct Point p2;
    struct Point p3;
    double len1;
    double len2;
    double perimetr;
    double square;
};

double length(struct Point p1, struct Point p2);
double trperimetr(struct Triangle tr);
double trsquare(struct Triangle tr);
void triangalise(double arr[], struct Triangle *tr);

#endif //ELEVENTH_GHOUL_H







