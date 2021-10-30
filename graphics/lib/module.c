/**
 * Greg Attra
 * 10/24/2021
 * 
 * Implementation of the module API defined in module.h
 */

#include "image.h"
#include "point.h"
#include "line.h"
#include "circle.h"
#include "polyline.h"
#include "polygon.h"
#include "cube.h"
#include "matrix.h"
#include "module.h"
#include <stdio.h>

/**
 * Allocate and initialize an empty element.
 * 
 * @return a pointer to the allocated element
 */
Element *element_create(void)
{
    Element *el = (Element *) malloc(sizeof(Element));
    el->next = NULL;
    el->type = ObjNone;
    return el;
}

Element *element_init(ObjectType type, void *obj)
{
    Element *el = element_create();
    el->type = type;
    switch(type)
    {
        case ObjLine:
            line_copy(&el->obj.line, obj);
            break;
        case ObjPoint:
            point_copy(&el->obj.point, obj);
            break;
        case ObjPolyline:
            polyline_copy(&el->obj.polyline, obj);
            break;
        case ObjPolygon:
            polygon_copy(&el->obj.polygon, obj);
            break;
        case ObjCube:
            cube_copy(&el->obj.cube, obj);
            break;
        case ObjIdentity:
            matrix_identity(&el->obj.matrix);
            break;
        case ObjMatrix:
            matrix_copy(&el->obj.matrix, obj);
            break;
        case ObjColor:
            color_copy(&el->obj.color, obj);
        case ObjBodyColor:
            color_copy(&el->obj.color, obj);
        case ObjSurfaceColor:
            color_copy(&el->obj.color, obj);
            break;
        case ObjSurfaceCoeff:
            el->obj.coeff = *(float*) obj;
            break;
        case ObjModule:
            el->obj.module = obj;
            break;
        default:
            break;
    }
    return el;
}

void element_delete(Element *el)
{
    free(el->next);
    free(el);
}

Module *module_create(void)
{
    Module *mod = (Module *) malloc(sizeof(Module));
    mod->head = NULL;
    mod->tail = NULL;
    return mod;
}

void module_clear(Module *md)
{
    Element *el = md->head;
    while (el)
    {
        Element *tmp = el->next;
        element_delete(el);
        el = tmp;
    }
    md->head = NULL;
    md->tail = NULL;
}

void module_delete(Module *md)
{
    module_clear(md);
    free(md);
}

void module_insert(Module *md, Element *el)
{
    md->tail->next = element_init(el->type, &el->obj);
    md->tail = md->tail->next;
}

void module_module(Module *md, Module *sub)
{
    md->tail->next = sub;
    md->tail = sub;
}

void module_point(Module *md, Point *p)
{
    md->tail->next = element_init(ObjPoint, p);
    md->tail = md->tail->next;
}

void module_line(Module *md, Line *l)
{
    md->tail->next = element_init(ObjLine, l);
    md->tail = md->tail->next;
}

void module_polyline(Module *md, Polyline *pl)
{
    md->tail->next = element_init(ObjPolyline, pl);
    md->tail = md->tail->next;
}

void module_polygon(Module *md, Polygon *pgon)
{
    md->tail->next = element_init(ObjPolygon, pgon);
    md->tail = md->tail->next;
}

void module_identity(Module *md)
{
    md->tail->next = element_init(ObjIdentity, NULL);
    md->tail = md->tail->next;
}

void module_translate2D(Module *md, double tx, double ty)
{
    Matrix *m;
    matrix_translate2D(m, tx, ty);
    md->tail->next = element_init(ObjMatrix, m);
    md->tail = md->tail->next;
}

void module_scale2D(Module *md, double sx, double sy)
{
    Matrix *m;
    matrix_scale2D(m, sx, sy);
    md->tail->next = element_init(ObjMatrix, m);
    md->tail = md->tail->next;
}

void module_rotateZ(Module *md, double cth, double sth)
{
    Matrix *m;
    matrix_rotateZ(m, cth, sth);
    md->tail->next = element_init(ObjMatrix, m);
    md->tail = md->tail->next;
}

void module_shear2D(Module *md, double shx, double shy)
{
    Matrix *m;
    matrix_shear2D(m, shx, shy);
    md->tail->next = element_init(ObjMatrix, m);
    md->tail = md->tail->next;
}

void module_translate(Module *md, double tx, double ty, double tz)
{
    Matrix *m;
    matrix_translate(m, tx, ty, tz);
    md->tail->next = element_init(ObjMatrix, m);
    md->tail = md->tail->next;
}

void module_scale(Module *md, double sx, double sy, double sz)
{
    Matrix *m;
    matrix_translate(m, sx, sy, sz);
    md->tail->next = element_init(ObjMatrix, m);
    md->tail = md->tail->next;
}

void module_rotateX(Module *md, double cth, double sth)
{
    Matrix *m;
    matrix_rotateX(m, cth, sth);
    md->tail->next = element_init(ObjMatrix, m);
    md->tail = md->tail->next;
}

void module_rotateY(Module *md, double cth, double sth)
{
    Matrix *m;
    matrix_rotateY(m, cth, sth);
    md->tail->next = element_init(ObjMatrix, m);
    md->tail = md->tail->next;
}

void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w)
{
    Matrix *m;
    matrix_rotateXYZ(m, u, v, w);
    md->tail->next = element_init(ObjMatrix, m);
    md->tail = md->tail->next;
}

void module_cube(Module *md, int solid)
{
    Point c;
    point_set2D(&c, 0, 0);

    Cube *cube;
    cube = cube_create(1, 1, 1, c, solid);

    md->tail->next = element_init(ObjCube, cube);
    md->tail = md->tail->next;
}

void module_color(Module *md, Color c)
{
    md->tail->next = element_init(ObjColor, &c);
    md->tail = md->tail->next;
}

void module_bodyColor(Module *md, Color c)
{
    md->tail->next = element_init(ObjBodyColor, &c);
    md->tail = md->tail->next;
}

void module_surfaceColor(Module *md, Color c)
{
    md->tail->next = element_init(ObjSurfaceColor, &c);
    md->tail = md->tail->next;
}

void module_surfaceCoeff(Module *md, float sc)
{
    md->tail->next = element_init(ObjSurfaceCoeff, &sc);
    md->tail = md->tail->next;
}

/**
 * Draw the module onto the image using the VTM, GTM and DrawState
 * by traversing each element in the module.
 * 
 * @param md the module to draw
 * @param vtm the view transformatin matrix
 * @param gtm the global transformation matrix
 * @param ds the draw state
 * @param light the lighting of the scene
 * @param src the image to draw to
 * 
 * @return void
 */
void module_draw(
    Module *md,
    Matrix *vtm,
    Matrix *gtm,
    DrawState *ds,
    Lighting *light,
    Image *src);