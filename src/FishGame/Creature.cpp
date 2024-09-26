#include "Creature.h"
Creature::Creature(Vector2f pos, float size, float friction, bool bouncy, float bounceDamp) : Mover(pos, size, friction, bouncy, bounceDamp){

}
//add delete  method
//needs to deregister from engine system