// ************************************************************************ 
// File Name:   Car.js 
// Author:      Sarah Herzog 
// Purpose:     AI racecar 
// ************************************************************************

// ************************************************************************
// Global Constants
// ************************************************************************
var CAR_Y = 40;
var CAR_MAX_VEL = 1000;   // Can't go faster than this
var CAR_MAX_ACC = 600;	  // Can't accelerate faster than this

// Car Class
function Car() {
    // ********************************************************************
    // Data Members 
    // ********************************************************************
	this.position = 0;		// The x position of the car in game world
	this.velocity = 0;		// The x velocity of the car in game world
	this.line_position;		// The position of the line relative to the car
	this.line_rel_vel;		// The velocity of the line relative to the car
	
    // ********************************************************************
    // Function:    logic()
    // Purpose:     Handles logic for line. 
	// Arguments:	line - the line
    // ********************************************************************
    this.logic = function(line, control) {
		// Process abs_line_pos
		this.line_rel_vel = line.velocity - this.velocity;
		this.line_position = line.position - this.position;
		
		// Send through fuzzy controller
		vel_change = control.process(this.line_position, this.line_rel_vel);
		
		// Check for max acceleration
		if (vel_change > CAR_MAX_ACC) vel_change = CAR_MAX_ACC;
		if (vel_change < -1*CAR_MAX_ACC) vel_change = -1*CAR_MAX_ACC;
		this.velocity += vel_change;
		
		// Check for max velocity
		if (this.velocity > CAR_MAX_VEL) this.velocity = CAR_MAX_VEL;
		if (this.velocity < -1*CAR_MAX_VEL) this.velocity = -1*CAR_MAX_VEL;
		
		// Update position based on velocity
		this.position += this.velocity / FPS;
    } 
	
    // ********************************************************************
    // Function:    draw()
    // Purpose:     Draws the line to the screen
    // ********************************************************************
    this.draw = function(camera) {
		ctx.fillStyle = "#900";		// Set color
		// Circle (car)
        ctx.beginPath();
        ctx.arc(CANVAS_WIDTH/2+this.position-camera, CAR_Y, 
            20, 0, Math.PI * 2, true);
        ctx.closePath();
        ctx.fill();
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