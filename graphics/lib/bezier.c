/**
 * Greg Attra
 * 11/07/2021
 * 
 * Implementation of Bezier curve API defined in bezier.h
 */

#include "matrix.h"
#include "bezier.h"
#include "point.h"
#include <math.h>


void bezierCurve_init(BezierCurve *bc)
{
    bc->zBuffer = 1;

    float val = 0.0;
    float delim = 1.0/4.0;
    for (int i = 0; i < 4; i++)
    {
        point_set3D(&bc->vlist[i], val, 0, 0);
        val += delim;
    }
}

void bezierSurface_init(BezierSurface *bs)
{
    bs->zBuffer = 1;
    
    float xVal = 0.0;
    float delim = 1.0/4.0;
    for (int i = 0; i < 4; i++)
    {
        float zVal = 0.0;
        for (int j = 0; j < 4; j++)
        {
            point_set3D(&bs->vlist[(i * 4) + j], xVal, 0, zVal);
            zVal += delim;
        }
        xVal += delim;
    }
}

void bezierCurve_set(BezierCurve *bc, Point *vlist)
{
    for (int i = 0; i < 4; i++)
    {
        point_copy(&bc->vlist[i], &vlist[i]);
    }
}

void bezierSurface_set(BezierSurface *bs, Point *vlist)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            point_copy(&bs->vlist[(i * 4) + j], &vlist[(i * 4) + j]);
        }
    }
}

void bezierCurve_zBuffer(BezierCurve *bc, int flag)
{
    bc->zBuffer = flag;
}

void bezierSurface_zBuffer(BezierSurface *bs, int flag)
{
    bs->zBuffer = flag;
}

/**
 * Compare two bezier curves.
 * 
 * @param one the first curve
 * @param two the second curve
 * 
 * @return -1 if one < two, 0 if equal, 1 if two < one
 */
static int bezierCurve_compare(const void *one, const void *two)
{
    BezierCurve *bc_one = (BezierCurve *) one;
    BezierCurve *bc_two = (BezierCurve *) two;

    if (bc_one->vlist[0].val[0] < bc_two->vlist[0].val[0])
    {
        return -1;
    }
    if (bc_one->vlist[0].val[0] > bc_two->vlist[0].val[0])
    {
        return 1;
    }
    return 0;
}

void bezierCurve_divide(
    BezierCurve *bc,
    LinkedList *curves,
    int divs_remaining)
{
    BezierCurve *left = NULL;
    BezierCurve *right = NULL;
    bezierCurve_init(left);
    bezierCurve_init(right);

    Point plist[4];
    point_copyList(plist, bc->vlist, 4);

    int r = 0;
    while (r < 3)
    {
        point_copy(&left->vlist[r], &plist[r]);
        point_copy(&right->vlist[3-r], &plist[3-r]);
        Point tmp_plist[3-r];
        for (int i = 0; i < 3 - r; i++)
        {
            Point *start = &plist[i];
            Point *end = &plist[i + 1];
            float x = (start->val[0] + end->val[0]) / 2.0;
            float y = (start->val[1] + end->val[1]) / 2.0;
            float z = (start->val[2] + end->val[2]) / 2.0;

            Point midpoint;
            point_set(&midpoint, x, y, z, 1.0);
            point_copy(&tmp_plist[i], &midpoint);
        }
        point_copyList(plist, tmp_plist, 3 - r);
        r += 1;
    }

    point_copy(&left->vlist[3], &plist[0]);
    point_copy(&right->vlist[0], &plist[0]);

    divs_remaining = divs_remaining / 2;
    if (divs_remaining <= 1)
    {
        ll_insert(curves, left, &bezierCurve_compare);
        ll_insert(curves, right, &bezierCurve_compare);
        return;
    }

    bezierCurve_divide(left, curves, divs_remaining);
    bezierCurve_divide(right, curves, divs_remaining);

    free(left);
    free(right);

    return;
}

void bezierCurve_draw(BezierCurve *bc, Image *src, Color c)
{
    float pix_thresh = 10.0;
    float min_x = bc->vlist[0].val[0];
    float min_y = bc->vlist[0].val[1];
    float max_x = bc->vlist[0].val[0];
    float max_y = bc->vlist[0].val[1];
    for (int i = 1; i < 4; i++)
    {
        float x = bc->vlist[i].val[0];
        float y = bc->vlist[i].val[1];
        if (x < min_x) min_x = x;
        if (x > max_x) max_x = x;
        if (y < min_y) min_y = y;
        if (y > max_y) max_y = y;
    }
    float width = fabsf(max_x - min_x);
    float height = fabsf(max_y - min_y);
    if (width <= pix_thresh && height <= pix_thresh)
    {
        // draw line between start and end of bez curve
        Line l;
        line_set2D(
            &l,
            bc->vlist[0].val[0],
            bc->vlist[0].val[1],
            bc->vlist[3].val[0],
            bc->vlist[3].val[1]);
        line_draw(&l, src, c);
        return;
    }
    
    for (int i = 0; i < 3; i++)
    {
        Line l;
        line_set2D(
            &l,
            bc->vlist[i].val[0],
            bc->vlist[i].val[1],
            bc->vlist[i+1].val[0],
            bc->vlist[i+1].val[1]);
        line_draw(&l, src, c);
    }
}

