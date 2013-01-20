// ************************************************************************ 
// File Name:   AI.js 
// Author:      Sarah Herzog 
// Purpose:     Abstract interface which all types of AI inherit
// ************************************************************************

// AI Class
function AI() {

    // ********************************************************************
    // Data Members 
    // ********************************************************************
	
    // ********************************************************************
    // Function:    setAttributes()
    // Purpose:     Sets an AI's attributes to those of the object supplied
    // ********************************************************************
	this.setAttributes = function(other) {
		for (var attrname in other) { this[attrname] = other[attrname]; }
	}
	
    // ********************************************************************
    // Function:    initialise()
    // Purpose:     Initialises AI object
    // ********************************************************************
	this.initialise = function() {
	}
	
    // ********************************************************************
    // Function:    process()
    // Purpose:     Given input, process using AI logic and recommend an
	//				action.
    // Input:       line_position - position of the line relative to player
	//				line_velocity - velocity of line relative to player
    // Output:      velcoty_change - recommended change in player velocity
    // ********************************************************************
	this.process = function(line_position, line_velocity) {
		return velocity_change = 0; // default value of 0
	}
}