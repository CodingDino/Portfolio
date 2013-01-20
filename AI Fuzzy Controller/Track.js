// ************************************************************************ 
// File Name:   Track.js 
// Author:      Sarah Herzog 
// Purpose:     Holds and interprets instructions for a track. 
// ************************************************************************

// Track Class
function Track() {
    // ********************************************************************
    // Data Members 
    // ********************************************************************
	this.done = false;			// Set to true when all instructions are run
	this.current = 0;			// Location in the instruction set
	this.instructions = new Array();	// Instruction set
	
    // ********************************************************************
    // Function:    reset()
    // Purpose:     Resets to starting values
    // ********************************************************************
    this.reset = function() {
		this.done = false;			
		this.current = 0;		
    }
	
    // ********************************************************************
    // Function:    initialise()
    // Purpose:     Sets default variables
    // ********************************************************************
	this.initialise = function() {
		// Track uses four speeds, similar to user-control
		var slow = LINE_SPEED,
			med = LINE_SPEED*2,
			fast = LINE_SPEED*3;
		// buffer speed to wait for ball to catch up before next test
		var buff = 10;
	

		var inst;
		
		// ********************************************************************
		// Same direction, varying speeds 
		// ********************************************************************
		// Get us to the left edge
		inst = new Object();
		inst.position = -550; 
		inst.velocity = -slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -600; 
		inst.velocity = -buff;
		this.instructions.push(inst);
		// Acceleration
		inst = new Object();
		inst.position = -200; 
		inst.velocity = slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 200; 
		inst.velocity = med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 550; 
		inst.velocity = fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 600; 
		inst.velocity = buff;
		this.instructions.push(inst);
		// Deceleration
		inst = new Object();
		inst.position = 200; 
		inst.velocity = -fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -200; 
		inst.velocity = -med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -550; 
		inst.velocity = -slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -600; 
		inst.velocity = -buff;
		this.instructions.push(inst);
		
		// ********************************************************************
		// Sharp direction changes (probably overshooting) 
		// ********************************************************************
		// At all fast 
		inst = new Object();
		inst.position = 600; 
		inst.velocity = fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -400; 
		inst.velocity = -fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 400; 
		inst.velocity = fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -200; 
		inst.velocity = -fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 200; 
		inst.velocity = fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -50; 
		inst.velocity = -fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 50; 
		inst.velocity = fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 50; 
		inst.velocity = fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -550; 
		inst.velocity = -fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -600; 
		inst.velocity = -buff;
		this.instructions.push(inst);
		// At all med 
		inst = new Object();
		inst.position = 600; 
		inst.velocity = med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -400; 
		inst.velocity = -med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 400; 
		inst.velocity = med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -200; 
		inst.velocity = -med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 200; 
		inst.velocity = med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -50; 
		inst.velocity = -med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 50; 
		inst.velocity = med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 50; 
		inst.velocity = med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -550; 
		inst.velocity = -med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -600; 
		inst.velocity = -buff;
		this.instructions.push(inst);
		// At all slow 
		inst = new Object();
		inst.position = 600; 
		inst.velocity = slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -400; 
		inst.velocity = -slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 400; 
		inst.velocity = slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -200; 
		inst.velocity = -slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 200; 
		inst.velocity = slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -50; 
		inst.velocity = -slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 50; 
		inst.velocity = slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 50; 
		inst.velocity = slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -550; 
		inst.velocity = -slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -600; 
		inst.velocity = -buff;
		this.instructions.push(inst);
		// Mixed 
		inst = new Object();
		inst.position = 600; 
		inst.velocity = slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -400; 
		inst.velocity = -fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 400; 
		inst.velocity = med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -200; 
		inst.velocity = -fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 200; 
		inst.velocity = slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -50; 
		inst.velocity = -fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 50; 
		inst.velocity = slow;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = 50; 
		inst.velocity = med;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -550; 
		inst.velocity = -fast;
		this.instructions.push(inst);
		inst = new Object();
		inst.position = -600; 
		inst.velocity = -buff;
		this.instructions.push(inst);
	}
	
    // ********************************************************************
    // Function:    logic()
    // Purpose:     Handles logic for line. 
    // Input:       line - The racing line object to be modified
    // ********************************************************************
    this.logic = function(line) {
		// Check if it's time to change instructions
		if ( (line.velocity > 0 && line.position >= this.instructions[this.current].position)
				|| (line.velocity < 0 && line.position <= this.instructions[this.current].position) ) {
			this.current++;
			if (this.current >= this.instructions.length) {
				this.done = true;	// Instructions are done
				this.current = 0;	// Loop back to beginning of instructions (game controls when we quit)
			}
		}
		line.velocity = this.instructions[this.current].velocity;		// Set the velocity based on instruction
    }
}