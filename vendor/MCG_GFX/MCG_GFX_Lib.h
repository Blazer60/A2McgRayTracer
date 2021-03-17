/**
 * The mcg framework that allows pixels to be drawn to the screen.
 * Editing this file or the paired source file is forbidden.
 * Changes:
 * - The namespace MCG has been change to mcg
 * - All functions within the namespace now follow camelCase.
 * @author Leigh McLoughlin
 * @version 2.0.2 [Edited On: 17/03/2021]
 */
#ifndef A2MCGRAYTRACER_MCG_GFX_LIB_H
#define A2MCGRAYTRACER_MCG_GFX_LIB_H

// The GLM library contains vector and matrix functions and classes for us to use
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations

/// The mcg namespace provides all the functions to draw a pixel to the screen.
/// You should not be modifying this code for your assignment, you must use it as-is.
namespace mcg
{

	/// Initialises window to specified size
	/// The windowSize parameter specifies how many pixels wide and high the window should be
	/// \return False if something went wrong
	bool init(glm::ivec2 windowSize );

	/// Sets every pixel to specified colour
	/// The colour parameter ranges from 0 to 1. Values outside this range are clamped.
	void setBackground(glm::vec3 colour );

	/// Draws a single pixel to screen
	/// The position parameter is in pixel-coordinates, ranging from 0,0 to the size of the screen set with the init function. If coordinates are out of bounds, does nothing.
	/// The colour parameter ranges from 0 to 1. Values outside this range are clamped.
	void drawPixel(glm::ivec2 position, glm::vec3 colour );

	/// Displays graphics to screen and keeps window open until user requests exit (pressing escape key or closing window)
	int showAndHold();

	/// \return False when user requests program exit
	bool processFrame();

	/// For cleanly shutting down the graphics system
	void cleanup();

}

#endif  // A2MCGRAYTRACER_MCG_GFX_LIB_H

