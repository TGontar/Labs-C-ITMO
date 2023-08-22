#include "ghoul.h"
#include "math.h"

double length(struct Point p1, struct Point p2) {
    double ans = sqrt(pow((p1.x - p2.x), 2) + pow((p2.y - p1.y), 2));
    return ans;
}

double trperimetr(struct Triangle tr) {
    double len3 = sqrt(pow(tr.len1, 2) + pow(tr.len2, 2));
    double p = tr.len1 + tr.len2 + len3;
    return p;
}

double trsquare(struct Triangle tr) {
    double s = (tr.len1 * tr.len2) / 2.0;
    return s;
}

void triangalise(double arr[], struct Triangle *tr) {
    tr->p1.x = arr[0];
    tr->p1.y = arr[1];
    tr->p2.x = arr[2];
    tr->p2.y = arr[3];
    tr->p3.x = arr[4];
    tr->p3.y = arr[5];
}