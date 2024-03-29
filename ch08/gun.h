// File name: ExtremeC_examples_chapter7_2_gun.h
// Description: Declares the public API of the class Gun

#ifndef GUN_H
#define GUN_H

typedef int bool_t;

// Type forward declarations
struct gun_t;

// Memory allocator
struct gun_t* gun_new();

// Constructor
void gun_ctor(struct gun_t*, int);

// Destructor
void gun_dtor(struct gun_t*);

// Behavior functions
bool_t gun_has_bullets(struct gun_t*);
void gun_trigger(struct gun_t*);
void gun_refill(struct gun_t*);

#endif
