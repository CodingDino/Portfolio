// ************************************************************************ 
// File Name:   Readout.js 
// Author:      Sarah Herzog 
// Purpose:     Readout which displays member function results in realtime 
// ************************************************************************

// ************************************************************************
// Global Constants
// ************************************************************************
var READOUT_TOP = 100,
	READOUT_X_PAD = 250,
	READOUT_Y_PAD = 20,
	READOUT_TRUNC = 25;

// Readout Class
function Readout() {
    
    // ********************************************************************
    // Function:    clear()
    // Purpose:     Sets up the readout for each frame. 
    // ********************************************************************
    this.clear = function() {
		ctx.fillStyle = 'rgba('+        // Sets fill color
		'255,255,200,255)';
        ctx.beginPath();                // Start drawing
        ctx.rect(0,READOUT_TOP,         // Draws rectangle
            CANVAS_WIDTH,
            CANVAS_HEIGHT);        
        ctx.closePath();                // Ends drawing
        ctx.fill();                     // Fills rectangle w/ active color
    }
	
    // ********************************************************************
    // Function:    draw()
    // Purpose:     Draws all readout text to the canvas. 
    // ********************************************************************
    this.draw = function(car,line) {
        // Clear the readout
        this.clear();
		
		// Text properties
		ctx.font = '20px san-serif';
		ctx.textBaseline = 'top';
		ctx.textAlign = 'left';
		ctx.fillStyle = "#222";
		
		// Line Position
		ctx.fillText("LINE POSITION", 5, READOUT_TOP+5);
		ctx.fillText(("Absolute Position = "+line.position).substring(0,READOUT_TRUNC), 5, READOUT_TOP+5+READOUT_Y_PAD);
		ctx.fillText(("Relative Position = "+car.line_position).substring(0,READOUT_TRUNC), 5, READOUT_TOP+5+READOUT_Y_PAD*2);
		ctx.fillText(("Fuzzy Membership:").substring(0,READOUT_TRUNC), 5, READOUT_TOP+5+READOUT_Y_PAD*3);
		var pos = new Array(0,0,0,0,0);
		for (iter = 0; iter < pos.length; ++iter) {
			pos[iter] = controller.fuzzify("position",iter,car.line_position);
			ctx.fillText(("   "+controller["position"].sets[iter].name+" = "+pos[iter]).substring(0,READOUT_TRUNC), 5, READOUT_TOP+5+READOUT_Y_PAD*(4+iter));
		}
		
		// Line Velocity
		ctx.fillText("LINE VELOCITY", READOUT_X_PAD, READOUT_TOP+5);
		ctx.fillText(("abs velocity = "+line.velocity).substring(0,READOUT_TRUNC), READOUT_X_PAD, READOUT_TOP+5+READOUT_Y_PAD);
		ctx.fillText(("rel velcoity = "+car.line_rel_vel).substring(0,READOUT_TRUNC), READOUT_X_PAD, READOUT_TOP+5+READOUT_Y_PAD*2);
		ctx.fillText(("Fuzzy Membership:").substring(0,READOUT_TRUNC), READOUT_X_PAD, READOUT_TOP+5+READOUT_Y_PAD*3);
		var vel = new Array(0,0,0,0,0);
		for (iter = 0; iter < vel.length; ++iter) {
			vel[iter] = controller.fuzzify("velocity",iter,car.line_rel_vel);
			ctx.fillText(("   "+controller["velocity"].sets[iter].name+" = "+vel[iter]).substring(0,READOUT_TRUNC), READOUT_X_PAD, READOUT_TOP+5+READOUT_Y_PAD*(4+iter));
		}
		
		// Car Stats
		ctx.fillText("CAR DETAILS", READOUT_X_PAD*2, READOUT_TOP+5);
		ctx.fillText(("car position = "+car.position).substring(0,READOUT_TRUNC), READOUT_X_PAD*2, READOUT_TOP+5+READOUT_Y_PAD);
		ctx.fillText(("car velocity = "+car.velocity).substring(0,READOUT_TRUNC), READOUT_X_PAD*2, READOUT_TOP+5+READOUT_Y_PAD*2);
		ctx.fillText(("Fuzzy Membership:").substring(0,READOUT_TRUNC), READOUT_X_PAD*2, READOUT_TOP+5+READOUT_Y_PAD*3);
		var act = new Array(0,0,0,0,0,0,0,0,0);
		for (iter = 0; iter < pos.length; ++iter) {
			for (iter2 = 0; iter2 < vel.length; ++iter2) {
				var act_index = controller.rules[iter][iter2];
				act[act_index] = Math.max(act[act_index], Math.min(pos[iter],vel[iter2]));
			}
		}
		for (iter = 0; iter < 5; ++iter) {
			ctx.fillText(("   "+controller["action"].sets[iter].name+" = "
				+(act[iter]+"").substring(0,4)
				+" ("
				+(""+(controller.defuzzify("action",iter,act[iter])).value).substring(0,5) + ", "
				+(""+(controller.defuzzify("action",iter,act[iter])).area).substring(0,5)
				+")"), 
				READOUT_X_PAD*2, READOUT_TOP+5+READOUT_Y_PAD*(4+iter));
		}
		for (iter = 5; iter < act.length; ++iter) {
			ctx.fillText(("   "+controller["action"].sets[iter].name+" = "
				+(act[iter]+"").substring(0,4)
				+" ("
				+(""+(controller.defuzzify("action",iter,act[iter])).value).substring(0,5) + ", "
				+(""+(controller.defuzzify("action",iter,act[iter])).area).substring(0,5)
				+")"), READOUT_X_PAD*3, READOUT_TOP+5+READOUT_Y_PAD*(iter-1));
		}
		
		// Misc
		ctx.fillText(("runtime = "+(game_current_time-game_start_time)/1000).substring(0,READOUT_TRUNC), READOUT_X_PAD*4, READOUT_TOP+5);
	
    }  
	
}