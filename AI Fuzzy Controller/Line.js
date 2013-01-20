// ************************************************************************ 
// File Name:   Line.js 
// Author:      Sarah Herzog 
// Purpose:     Racing line which the car will have to stay close to. 
// ************************************************************************

// ************************************************************************
// Global Constants
// ************************************************************************
var LINE_SPEED = 500;			// Constant speed factor for line movement

// Line Class
function Line() {
    // ********************************************************************
    // Data Members 
    // ********************************************************************
	this.position = 0;		// The x position of the line in game world
	this.velocity = 0;		// The x velocity of the line in game world
	this.change_rate = 1;
	this.direction = 0;
	
    // ********************************************************************
    // Function:    logic()
    // Purpose:     Handles logic for line. 
    // ********************************************************************
    this.logic = function(user_control) {
		if(game_user_control) user_control = game_user_control;
		// Move the line based on it's direction and change rate
		if(user_control) this.velocity = this.direction*this.change_rate*LINE_SPEED;
		
		// Update position based on velocity
		this.position += this.velocity / FPS;
		
		// Clamp line to screen
		this.position = clamp(this.position, 0-CANVAS_WIDTH/2, CANVAS_WIDTH/2)
    } 
	
    // ********************************************************************
    // Function:    draw()
    // Purpose:     Draws the line to the screen
    // ********************************************************************
    this.draw = function(camera) {
		ctx.lineWidth = 5;				// Set line width
		ctx.strokeStyle = "#FFF";		// Set line color
		// Line
		ctx.beginPath();
		ctx.moveTo(CANVAS_WIDTH/2+(this.position-camera),0);
		ctx.lineTo(CANVAS_WIDTH/2+(this.position-camera),CANVAS_HEIGHT);
		ctx.stroke();
    }
	
    // ********************************************************************
    // Function:    reset()
    // Purpose:     Resets to starting values
    // ********************************************************************
    this.reset = function() {
		this.position = 0;		
		this.velocity = 0;		
    }
}