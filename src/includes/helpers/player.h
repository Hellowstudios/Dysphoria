
/**********************************************************************************************
 * This header file contains all the functions that are used to init, update, draw, unload player related logics.
 **********************************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

void UpdatePlayerMovement(PlayerMovementState *pms, Rectangle *map, Rectangle objects[], int objectsCount);

#endif