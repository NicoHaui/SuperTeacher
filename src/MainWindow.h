#pragma once

/**
 * \file MainWindow.h
 * \author Samuel Dolt
 * \brief MainWindow management function
 */

#include <SDL2/SDL.h>


/**
 * Create a main window. Must be called only once
 */
void MainWindow_Open(void);

/**
 * Close the main window
 */
void MainWindow_Close(void);
