/**
 * Greg Attra
 * 12/08/2021
 * 
 * Test the counter gravity force on a rigidbody.
 */

#include "graphics.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    int rows, cols, nFrames;
    Matrix VTM, GTM;
    Color White, Grey,DkGrey;
    DrawState *ds;
    View3D view;
    Lighting *light;

    rows = 900;
    cols = 900;
    nFrames = 60;

    color_set( &White, 1.0, 1.0, 1.0 );
    color_set( &Grey, 0.6, 0.62, 0.64 );
    color_set( &DkGrey, 0.1, 0.1, 0.1 );

	float d = 25;
	point_set3D(&view.vrp, d, -d/2.7, d);
	vector_set( &(view.vpn), -d, 0, -d);
	vector_set( &(view.vup), 0.0, 1.0, 0.0 );
	view.d = 1.5;
	view.du = 1.0;
	view.dv = 1.0*rows/cols;
	view.screeny = rows;
	view.screenx = cols;
	view.f = 0.0;
	view.b = 3.0;

    matrix_setView3D( &VTM, &view );
    matrix_identity( &GTM );

    ds = drawstate_create();
    point_copy(&ds->viewer, &(view.vrp));
    ds->shade = ShadeGouraud;
    // ds->shade = ShadeFlat;
    ds->fill = BarycentricFill;

    light = lighting_create();
    lighting_add( light, LightPoint, &White, NULL, &(view.vrp), 0, 0 );
    
    Image *src;
    src = image_create(rows, cols);

    Rigidbody *rb = rigidbody_create();
    rigidbody_setMass(rb, 1);

    Vector up;
    vector_set(&up, 0, 1, 0);
    Force *countergrav = force_createp(&up, GRAVITY * rb->mass * 2);

    int toggleTime = 5;
    int timer = toggleTime;
    int gravFlag = 1;
    for (int i = 0; i < nFrames; i++)
    {
        Module *md;
        md = module_create();

        Module *sphere;
        sphere = module_create();
        module_color(sphere, White);
        module_bodyColor(sphere, White);
        module_surfaceColor(sphere, DkGrey);
        module_scale(sphere, 2, 2, 2);
        module_sphere(sphere, 4, 1);
        rigidbody_setModule(rb, sphere);

        if (gravFlag < 0)
            rigidbody_addForce(rb, countergrav);

        rigidbody_tick(rb);
        rigidbody_render(rb, md);

        module_draw(md, &VTM, &GTM, ds, light, src);
        module_delete(md);

        char buffer[256];
        sprintf(buffer, "final/testcountergrav/testcountergrav_frame%03d.ppm", i);
        image_write(src, buffer);

        image_reset(src);

        timer--;
        if (timer <= 0)
        {
            timer = toggleTime;
            gravFlag *= -1;
        }
    }

    rigidbody_free(rb);
    image_free(src);

    return 0;
}