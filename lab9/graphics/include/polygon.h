/**
 * Greg Attra
 * 10/06/2021
 * 
 * Definition of the polygon API.
 */

#ifndef POLYGON
#define POLYGON

#include "image.h"
#include "point.h"
#include "vector.h"
#include "line.h"
#include "list.h"
#include "lighting.h"
#include "drawstate.h"
#include <stdlib.h>

typedef struct
{
    int oneSided;
    int nVertex;
    int zBuffer;
    Point *vlist;
    Color *clist;
    Vector *nlist;
} Polygon;

typedef Polygon Triangle;

/**
 * Returns an allocated Polygon pointer initialized so that numVertex is 0 and
 * vertex is NULL.
 * 
 * @return initialized polygon
 */
Polygon *polygon_create(void);

/**
 * Create a triangle.
 * 
 * @return an initialized triangle
 */
Triangle *triangle_create(void);

/**
 * Create a triangle from the points list.
 * 
 * @param vlist the corners of the triangle
 * 
 * @return instantiated triangle
 */
Triangle *triangle_createp(Point *vlist);

/**
 * Compare two triangles.
 * 
 * @param one the first to compare
 * @param two the second to compare
 * 
 * @return void
 */
int triangle_compare(const void *one, const void *two);

/**
 * Split the triangle into 4 triangles.
 * 
 * @param trgl the triangle to split
 * @param trgls the resulting triangles
 * 
 * @return void
 */
void triangle_divide(Triangle *trgl, Triangle trgls[4]);

/**
 * Returns an allocated Polygon pointer with the vertex list initialized to a
 * copy of the points in vlist.
 * 
 * @param nVertex the number of points in the polygon
 * @param vlist the list of points
 * 
 * @return initialized polygon
 */
Polygon *polygon_createp(int nVertex, Point *vlist);

/**
 * Frees the internal data for a Polygon and the Polygon pointer.
 * 
 * @param pgon the polygon to free
 * 
 * @return void
 */
void polygon_free(Polygon *pgon);

/**
 * Initializes the existing Polygon to an empty Polygon.
 * 
 * @param pgon
 * 
 * @return void
 */
void polygon_init(Polygon *pgon);

/**
 * Initializes the vertex array to the points in vlist.
 * 
 * @param pgon the polygon to set
 * @param numV the number of vertices
 * @param vlist the list of vertices
 * 
 * @return void
 */
void polygon_set(Polygon *pgon, int numV, Point *vlist);

/**
 * Frees the internal data and resets the fields.
 * 
 * @param pgon the polygon to free
 * 
 * @return void
 */
void polygon_clear(Polygon *pgon);

/**
 * Sets the oneSided field to the value.
 * 
 * @param pgon the polygon to set
 * @param oneSided the value to set
 * 
 * @return void
 */
void polygon_setSided(Polygon *pgon, int oneSided);

/**
 * Sets the color list on the polygon.
 * 
 * @param pgon the polygon to set
 * @param numV the number of vertices in the polygon
 * @param clist the list of colors
 * 
 * @return void
 */
void polygon_setColors(Polygon *pgon, int numV, Color *clist);

/**
 * Compute the polygon surface normal and store it in the normal vector.
 * 
 * @param vlist the vertices of the polygon
 * @param normal the vector to store the normal
 * 
 * @return void
 */
void polygon_normal(Point *vlist, Vector *normal);

/**
 * Initializes the normal array to the vectors in nlist.
 * 
 * @param pgon the polygon to set
 * @param numV the number of normals in the list
 * @param nlist the normals list
 * 
 * @return void
 */
void polygon_setNormals(Polygon *pgon, int numV, Vector *nlist);

/**
 * Convert polygon to list of lines.
 * 
 * @param pgon the polygon to convert
 * @param lines where to save the lines
 * 
 * @return void
 */
void polygon_toLines(Polygon *pgon, Line *lines);

/**
 * Sets all the properties of the polygon.
 * 
 * @param pgon the polygon to set
 * @param numV the number of vertices in the polygon
 * @param vlist the list of vertices
 * @param clist the list of colors
 * @param nlist the list of normals
 * @param zBuffer the zbuffer flag value
 * @param oneSided the oneSided flag value
 * 
 * @return void
 */
void polygon_setAll(
    Polygon *pgon,
    int numV,
    Point *vlist,
    Color *clist,
    Vector *nlist,
    int zBuffer,
    int oneSided);

/**
 * Sets the zbuffer flag on the polygon.
 * 
 * @param pgon the polygon to update
 * @param flag the zbuffer flag value
 * 
 * @return void
 */
void polygon_zBuffer(Polygon *pgon, int flag);

/**
 * Copies one polygon to another.
 * 
 * @param to the polygon to copy to
 * @param from the polygon to copy from
 * 
 * @return void
 */
void polygon_copy(Polygon *to, Polygon *from);

/**
 * Prints the polygon to the filepointer.
 * 
 * @param pgon the polygon to print
 * @param fp the filepointer to print to
 * 
 * @return void
 */
void polygon_print(Polygon *pgon, FILE *fp);

/**
 * Normalizes the polygon.
 * 
 * @param pgon the polygon to normalize
 * 
 * @return void
 */
void polygon_normalize(Polygon *pgon);

/**
 * Draws the polygon outline on the image.
 * 
 * @param pgon the polygon to draw
 * @param src the image to draw on
 * @param c the color of the polygon
 * 
 * @return void
 */
void polygon_draw(Polygon *pgon, Image *src, Color c);

/**
 * Draws and fills the polygon on the image.
 * 
 * @param pgon the polygon to draw
 * @param src the image to draw on
 * @param ds the draw state to use
 * 
 * @return void
 */
void polygon_drawFill(Polygon *pgon, Image *src, DrawState *ds);

/**
 * Draws and fills the polygon using the barycentric coordinates.
 * 
 * @param pgon the polygon to draw
 * @param src the image to draw
 * @param color the color to use
 * 
 * @return void
 */
void polygon_drawFillB(Polygon *pgon, Image *src, Color color);

/**
 * Fills a polygon using barycentric coords and blends the pixel
 * colors using the alpha, beta, and gamma values.
 * 
 * @param pgon the polygon to draw
 * @param src the image to draw on
 * @param ac the A point color
 * @param bc the B point color
 * @param cc the C point color
 * 
 * @return void
 */
void polygon_blendFillB(Polygon *pgon, Image *src, Color ac, Color bc, Color cc);

/**
 * Gets the furthest point right.
 * 
 * @param pgon the polygon to search
 * 
 * @return the furthest right point
 */
Point *polygon_maxX(Polygon *pgon);

/**
 * Gets the furthest point left.
 * 
 * @param pgon the polygon to search
 * 
 * @return the furthest left point
 */
Point *polygon_minX(Polygon *pgon);

/**
 * Shade the polygon using the lighting structure.
 * 
 * @param pgon the polygon to draw
 * @param ds the draw state to use
 * @param light the lights in the scene
 * 
 * @return void
 */
void polygon_drawShade(Polygon *pgon, Image *src, DrawState *ds, Lighting *light);

/**
 * Compute the colors for each vertex using Gouraud shading.
 * 
 * @param pgon the polygon to draw
 * @param ds the draw state to use
 * @param light the lights in the scene
 * 
 * @return void
 */
void polygon_shade(Polygon *pgon, DrawState *ds, Lighting *light);

/**
 * Divide the polygon n_divs times.
 * 
 * @param pgon the polygon to divide
 * @param n_divs the number of times to divide
 * 
 * @return void
 */
void polygon_divide(Polygon *pgon, int n_divs);

#endif