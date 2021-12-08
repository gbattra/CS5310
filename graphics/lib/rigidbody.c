/**
 * Greg Attra
 * 12/08/2021
 * 
 * Implementation of rigidbody API defined in rigidbody.h
 */

#include "rigidbody.h"


Rigidbody *rigidbody_create(void)
{
    Rigidbody *rb = (Rigidbody *) malloc(sizeof(Rigidbody));
    rb->mass = 0.0;
    rb->friction = 0.0;
    rb->md = module_create();
    rb->forces = ll_new();
    point_set3D(&rb->position, 0, 0, 0);
    vector_set(&rb->velocity, 0, 0, 0);
    quaternion_set(&rb->orientation, 0, 0, 0, 0);
}

Rigidbody *rigidbody_createp(
    double mass,
    double friction,
    Point *pos,
    Vector *vel,
    Quaternion *q,
    Module *md)
{
    Rigidbody *rb = (Rigidbody *) malloc(sizeof(Rigidbody));
    rb->mass = mass;
    rb->friction = friction;
    rb->md = md;
    rb->forces = ll_new();
    point_copy(&rb->position, pos);
    vector_copy(&rb->velocity, vel);
    quaternion_copy(&rb->orientation, q);
}

void rigidbody_setMass(Rigidbody *rb, double mass)
{
    rb->mass = mass;
}

void rigidbody_setFriction(Rigidbody *rb, double friction)
{
    rb->friction = friction;
}

void rigidbody_setPosition(Rigidbody *rb, Point *pos)
{
    point_copy(&rb->position, pos);
}

void rigidbody_setVelocity(Rigidbody *rb, Vector *vel)
{
    vector_copy(&rb->velocity, vel);
}

void rigidbody_setOrientation(Rigidbody *rb, Quaternion *q)
{
    quaternion_copy(&rb->orientation, q);
}

void rigidbody_setModule(Rigidbody *rb, Module *md)
{
    rb->md = md;
}

static void force_compare(const void *one, const void *two)
{
    return 1;
}

void rigidbody_addForce(Rigidbody *rb, Force *f)
{
    ll_insert(rb->forces, f, &force_compare);
}

void rigidbody_free(Rigidbody *rb)
{
    Force *curr = (Force *) ll_pop(rb->forces);
    while (curr != NULL)
    {
        force_free(curr);
    }

    free(rb);
}

void rigidobdy_render(Rigidbody *rb, Module *md)
{
    module_module(md, rb->md);
}

void rigidbody_tick(Rigidbody *rb)
{
    Vector newVel;
    vector_copy(&newVel, &rb->velocity);

    Force *f = (Force *) ll_pop(rb->forces);
    while (f != NULL)
    {
        force_apply(f, rb->mass, &newVel, &rb->orientation, &newVel);
    }

    // apply friction
    vector_set(
        &newVel,
        newVel.val[0] - (newVel.val[0] * rb->friction),
        newVel.val[1] - (newVel.val[1] * rb->friction),
        newVel.val[2] - (newVel.val[2] * rb->friction));
    
    vector_copy(&rb->velocity, &newVel);
    point_set3D(
        &rb->position,
        rb->position.val[0] + rb->velocity.val[0],
        rb->position.val[1] + rb->velocity.val[1],
        rb->position.val[2] + rb->velocity.val[2]);
}