/**
 * Greg Attra
 * 10/20/2021
 * 
 * Implementation of the cube API defined in cube.h
 */

#include "cube.h"


Cube *cube_create(double h, double w, double l, Point c)
{
    Cube *cube = (Cube *) malloc(sizeof(Cube));
    cube->h = h;
    cube->l = l;
    cube->w = w;
    point_copy(&cube->c, &c);
    cube_setSides(cube);

    return cube;
}

void cube_setSides(Cube *cube)
{
    double x = cube->c.val[0];
    double y = cube->c.val[1];
    double z = cube->c.val[2];

    double hr = cube->h / 2.0;
    double wr = cube->w / 2.0;
    double lr = cube->l / 2.0;

    Point tfl, tfr, tbl, tbr,
          bfl, bfr, bbl, bbr;
    point_set3D(&tfl, x - wr, y + hr, z + lr);
    point_set3D(&tfr, x + wr, y + hr, z + lr);
    point_set3D(&tbl, x - wr, y + hr, z - lr);
    point_set3D(&tbr, x + wr, y + hr, z - lr);
    point_set3D(&bfl, x - wr, y - hr, z + lr);
    point_set3D(&bfr, x + wr, y - hr, z + lr);
    point_set3D(&bbl, x - wr, y - hr, z - lr);
    point_set3D(&bbr, x + wr, y - hr, z - lr);

    Point front[4] = {bfl, tfl, tfr, bfr};
    Point back[4] = {bbl, bbr, tbr, tbl};
    Point left[4] = {tfl, tbl, bbl, bfl};
    Point right[4] = {tfr, tbr, bbr, bfr};
    Point top[4] = {tfl, tbl, tbr, tfr};
    Point bot[4] = {bfl, bbl, bbr, bfr};

    polygon_set(&cube->sides[0], 4, front);
    polygon_set(&cube->sides[1], 4, back);
    polygon_set(&cube->sides[2], 4, left);
    polygon_set(&cube->sides[3], 4, right);
    polygon_set(&cube->sides[4], 4, top);
    polygon_set(&cube->sides[5], 4, bot);
}

void cube_draw(Cube *cube, Image *src, Color c[6])
{
    for (int i = 0; i < 6; i++)
    {
        polygon_draw(&cube->sides[i], src, c[i]);
    }
}

void cube_drawFill(Cube *cub, Image *src, Color c[6])
{

}

void cube_free(Cube *cube)
{
    free(cube);
}

