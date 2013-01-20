// ************************************************************************ 
// File Name:   FuzzyController.js 
// Author:      Sarah Herzog 
// Purpose:     AI object which processes input using fuzzy logic
// ************************************************************************

// Inheritance
FuzzyController.prototype = new AI();
FuzzyController.prototype.constructor = FuzzyController;

// FuzzyController Class
function FuzzyController() {

    // ********************************************************************
    // Function:    initialise()
    // Purpose:     Sets default variables
    // ********************************************************************
	this.initialise = function() {
	
		// ********************************************************************
		// Position Set Information 
		// ********************************************************************
		this.position = new Object();
		this.position.sets = new Object();
		this.position.sets.length = 5;
		this.position.sets[0] = new Object();
		this.position.sets[0].name = "Far Left";
		this.position.sets[1] = new Object();
		this.position.sets[1].name = "Left";
		this.position.sets[2] = new Object();
		this.position.sets[2].name = "Center";
		this.position.sets[3] = new Object();
		this.position.sets[3].name = "Right";
		this.position.sets[4] = new Object();
		this.position.sets[4].name = "Far Right";
	
		// ********************************************************************
		// Velocity Set Information 
		// ********************************************************************
		this.velocity = new Object();
		this.velocity.sets = new Object();
		this.velocity.sets.length = 5;
		this.velocity.sets[0] = new Object();
		this.velocity.sets[0].name = "Large Left";
		this.velocity.sets[1] = new Object();
		this.velocity.sets[1].name = "Left";
		this.velocity.sets[2] = new Object();
		this.velocity.sets[2].name = "None";
		this.velocity.sets[3] = new Object();
		this.velocity.sets[3].name = "Right";
		this.velocity.sets[4] = new Object();
		this.velocity.sets[4].name = "Large Right";
	
		// ********************************************************************
		// Action Set Information 
		// ********************************************************************
		this.action = new Object();
		this.action.sets = new Object();
		this.action.sets.length = 9;
		this.action.sets[0] = new Object();
		this.action.sets[0].name = "Extreme Left";
		this.action.sets[1] = new Object();
		this.action.sets[1].name = "Large Left";
		this.action.sets[2] = new Object();
		this.action.sets[2].name = "Left";
		this.action.sets[3] = new Object();
		this.action.sets[3].name = "Slight Left";
		this.action.sets[4] = new Object();
		this.action.sets[4].name = "None";
		this.action.sets[5] = new Object();
		this.action.sets[5].name = "Slight Right";
		this.action.sets[6] = new Object();
		this.action.sets[6].name = "Right";
		this.action.sets[7] = new Object();
		this.action.sets[7].name = "Large Right";
		this.action.sets[8] = new Object();
		this.action.sets[8].name = "Extreme Right";
		
		// ********************************************************************
		// Line Position Member Function 
		// ********************************************************************
		
		// Far Left Member Function
		this.position.sets[0].memfunc = new Object();
		this.position.sets[0].memfunc.lbp = -650;
		this.position.sets[0].memfunc.lpp = -650;
		this.position.sets[0].memfunc.lc = 5;
		this.position.sets[0].memfunc.rpp = -350;
		this.position.sets[0].memfunc.rbp = -200;
		this.position.sets[0].memfunc.rc = 5;
		
		// Left Member Function
		this.position.sets[1].memfunc = new Object();
		this.position.sets[1].memfunc.lbp = -400;
		this.position.sets[1].memfunc.lpp = -250;
		this.position.sets[1].memfunc.lc = 5;
		this.position.sets[1].memfunc.rpp = -150;
		this.position.sets[1].memfunc.rbp = 0;
		this.position.sets[1].memfunc.rc = 5;
		
		// Center Member Function
		this.position.sets[2].memfunc = new Object();
		this.position.sets[2].memfunc.lbp = -200;
		this.position.sets[2].memfunc.lpp = -50;
		this.position.sets[2].memfunc.lc = 5;
		this.position.sets[2].memfunc.rpp = 50;
		this.position.sets[2].memfunc.rbp = 200;
		this.position.sets[2].memfunc.rc = 5;
		
		// Right Member Function
		this.position.sets[3].memfunc = new Object();
		this.position.sets[3].memfunc.lbp = 0;
		this.position.sets[3].memfunc.lpp = 150;
		this.position.sets[3].memfunc.lc = 5;
		this.position.sets[3].memfunc.rpp = 250;
		this.position.sets[3].memfunc.rbp = 400;
		this.position.sets[3].memfunc.rc = 5;
		
		// Far Right Member Function
		this.position.sets[4].memfunc = new Object();
		this.position.sets[4].memfunc.lbp = 200;
		this.position.sets[4].memfunc.lpp = 350;
		this.position.sets[4].memfunc.lc = 5;
		this.position.sets[4].memfunc.rpp = 650;
		this.position.sets[4].memfunc.rbp = 650;
		this.position.sets[4].memfunc.rc = 5;
		
		// ********************************************************************
		// Line Velocity Member Function 
		// ********************************************************************
		
		// Far Left Member Function
		this.velocity.sets[0].memfunc = new Object();
		this.velocity.sets[0].memfunc.lbp = -650;
		this.velocity.sets[0].memfunc.lpp = -650;
		this.velocity.sets[0].memfunc.lc = 5;
		this.velocity.sets[0].memfunc.rpp = -350;
		this.velocity.sets[0].memfunc.rbp = -200;
		this.velocity.sets[0].memfunc.rc = 5;
		
		// Left Member Function
		this.velocity.sets[1].memfunc = new Object();
		this.velocity.sets[1].memfunc.lbp = -400;
		this.velocity.sets[1].memfunc.lpp = -250;
		this.velocity.sets[1].memfunc.lc = 5;
		this.velocity.sets[1].memfunc.rpp = -150;
		this.velocity.sets[1].memfunc.rbp = 0;
		this.velocity.sets[1].memfunc.rc = 5;
		
		// Center Member Function
		this.velocity.sets[2].memfunc = new Object();
		this.velocity.sets[2].memfunc.lbp = -200;
		this.velocity.sets[2].memfunc.lpp = -50;
		this.velocity.sets[2].memfunc.lc = 5;
		this.velocity.sets[2].memfunc.rpp = 50;
		this.velocity.sets[2].memfunc.rbp = 200;
		this.velocity.sets[2].memfunc.rc = 5;
		
		// Right Member Function
		this.velocity.sets[3].memfunc = new Object();
		this.velocity.sets[3].memfunc.lbp = 0;
		this.velocity.sets[3].memfunc.lpp = 150;
		this.velocity.sets[3].memfunc.lc = 5;
		this.velocity.sets[3].memfunc.rpp = 250;
		this.velocity.sets[3].memfunc.rbp = 400;
		this.velocity.sets[3].memfunc.rc = 5;
		
		// Far Right Member Function
		this.velocity.sets[4].memfunc = new Object();
		this.velocity.sets[4].memfunc.lbp = 200;
		this.velocity.sets[4].memfunc.lpp = 350;
		this.velocity.sets[4].memfunc.lc = 5;
		this.velocity.sets[4].memfunc.rpp = 650;
		this.velocity.sets[4].memfunc.rbp = 650;
		this.velocity.sets[4].memfunc.rc = 5;
		
		// ********************************************************************
		// Action Member Function 
		// ********************************************************************
		
		// Extreme Left Member Function
		this.action.sets[0].memfunc = new Object();
		this.action.sets[0].memfunc.lbp = -650;
		this.action.sets[0].memfunc.lpp = -650;
		this.action.sets[0].memfunc.lc = 0;
		this.action.sets[0].memfunc.rpp = -550;
		this.action.sets[0].memfunc.rbp = -450;
		this.action.sets[0].memfunc.rc = 0;
		
		// Large Left Member Function
		this.action.sets[1].memfunc = new Object();
		this.action.sets[1].memfunc.lbp = -600;
		this.action.sets[1].memfunc.lpp = -500;
		this.action.sets[1].memfunc.lc = 0;
		this.action.sets[1].memfunc.rpp = -400;
		this.action.sets[1].memfunc.rbp = -300;
		this.action.sets[1].memfunc.rc = 0;
		
		// Left Member Function
		this.action.sets[2].memfunc = new Object();
		this.action.sets[2].memfunc.lbp = -450;
		this.action.sets[2].memfunc.lpp = -350;
		this.action.sets[2].memfunc.lc = 0;
		this.action.sets[2].memfunc.rpp = -250;
		this.action.sets[2].memfunc.rbp = -150;
		this.action.sets[2].memfunc.rc = 0;
		
		// Slight Left Member Function
		this.action.sets[3].memfunc = new Object();
		this.action.sets[3].memfunc.lbp = -300;
		this.action.sets[3].memfunc.lpp = -200;
		this.action.sets[3].memfunc.lc = 0;
		this.action.sets[3].memfunc.rpp = -100;
		this.action.sets[3].memfunc.rbp = 0;
		this.action.sets[3].memfunc.rc = 0;
		
		// Center Member Function
		this.action.sets[4].memfunc = new Object();
		this.action.sets[4].memfunc.lbp = -150;
		this.action.sets[4].memfunc.lpp = -50;
		this.action.sets[4].memfunc.lc = 0;
		this.action.sets[4].memfunc.rpp = 50;
		this.action.sets[4].memfunc.rbp = 150;
		this.action.sets[4].memfunc.rc = 0;
		
		// Slight Right Member Function
		this.action.sets[5].memfunc = new Object();
		this.action.sets[5].memfunc.lbp = 0;
		this.action.sets[5].memfunc.lpp = 100;
		this.action.sets[5].memfunc.lc = 0;
		this.action.sets[5].memfunc.rpp = 200;
		this.action.sets[5].memfunc.rbp = 300;
		this.action.sets[5].memfunc.rc = 0;
		
		// Right Member Function
		this.action.sets[6].memfunc = new Object();
		this.action.sets[6].memfunc.lbp = 150;
		this.action.sets[6].memfunc.lpp = 250;
		this.action.sets[6].memfunc.lc = 0;
		this.action.sets[6].memfunc.rpp = 350;
		this.action.sets[6].memfunc.rbp = 450;
		this.action.sets[6].memfunc.rc = 0;
		
		// Large Right Member Function
		this.action.sets[7].memfunc = new Object();
		this.action.sets[7].memfunc.lbp = 300;
		this.action.sets[7].memfunc.lpp = 400;
		this.action.sets[7].memfunc.lc = 0;
		this.action.sets[7].memfunc.rpp = 500;
		this.action.sets[7].memfunc.rbp = 600;
		this.action.sets[7].memfunc.rc = 0;
		
		// Extreme Right Member Function
		this.action.sets[8].memfunc = new Object();
		this.action.sets[8].memfunc.lbp = 450;
		this.action.sets[8].memfunc.lpp = 550;
		this.action.sets[8].memfunc.lc = 0;
		this.action.sets[8].memfunc.rpp = 650;
		this.action.sets[8].memfunc.rbp = 650;
		this.action.sets[8].memfunc.rc = 0;
		
		// ********************************************************************
		// Rules 
		// ********************************************************************
		this.rules = [];
		for (iter = 0; iter < this.position.sets.length; ++iter) { // For each pos value, add an array of velocity
			this.rules.push([]);
			for (iter2 = 0; iter2 < this.velocity.sets.length; ++iter2) { // Set all rules to 0 initially
				this.rules[iter].push(0);
			}
		}
		for (iter = 0; iter < this.action.sets.length; ++iter) {
			for(iter2 = 0; iter2 <= iter; ++iter2) {
				var limit = this.position.sets.length;
				if (iter2 < limit && (iter-iter2) < limit) {
					this.rules[iter2][iter-iter2] = iter
				}
			}
		}
		
		
	}

    // ********************************************************************
    // Function:    randomise()
    // Purpose:     Randomises default variables
    // ********************************************************************
	this.randomise = function() {
		var points = new Array();
		
		// ********************************************************************
		// Line Position Member Function 
		// ********************************************************************
		for (iter = 0; iter < 4*this.position.sets.length-4; ++iter) {
			points[iter] = randomise(-600,600);
		}
		points.sort( function(a,b) {return a - b;} );
		
		// Far Left Member Function
		this.position.sets[0].memfunc.rpp = points[1];
		this.position.sets[0].memfunc.rbp = points[4];
		this.position.sets[0].memfunc.lc = 0;
		this.position.sets[0].memfunc.rc = 0;
		
		// Left Member Function
		this.position.sets[1].memfunc.lbp = points[0];
		this.position.sets[1].memfunc.lpp = points[2];
		this.position.sets[1].memfunc.rpp = points[5];
		this.position.sets[1].memfunc.rbp = points[8];
		this.position.sets[1].memfunc.lc = 0;
		this.position.sets[1].memfunc.rc = 0;
		
		// Center Member Function
		this.position.sets[2].memfunc.lbp = points[3];
		this.position.sets[2].memfunc.lpp = points[6];
		this.position.sets[2].memfunc.rpp = points[9];
		this.position.sets[2].memfunc.rbp = points[12];
		this.position.sets[2].memfunc.lc = 0;
		this.position.sets[2].memfunc.rc = 0;
		
		// Right Member Function
		this.position.sets[3].memfunc.lbp = points[7];
		this.position.sets[3].memfunc.lpp = points[10];
		this.position.sets[3].memfunc.rpp = points[13];
		this.position.sets[3].memfunc.rbp = points[15];
		this.position.sets[3].memfunc.lc = 0;
		this.position.sets[3].memfunc.rc = 0;
		
		// Far Right Member Function
		this.position.sets[4].memfunc.lbp = points[11];
		this.position.sets[4].memfunc.lpp = points[14];
		this.position.sets[4].memfunc.lc = 0;
		this.position.sets[4].memfunc.rc = 0;
		
		// ********************************************************************
		// Line Velocity Member Function 
		// ********************************************************************
		for (iter = 0; iter < 4*this.velocity.sets.length-4; ++iter) {
			points[iter] = randomise(-600,600);
		}
		points.sort( function(a,b) {return a - b;} );
		
		// Far Left Member Function
		this.velocity.sets[0].memfunc.rpp = points[1];
		this.velocity.sets[0].memfunc.rbp = points[4];
		this.velocity.sets[0].memfunc.lc = 0;
		this.velocity.sets[0].memfunc.rc = 0;
		
		// Left Member Function
		this.velocity.sets[1].memfunc.lbp = points[0];
		this.velocity.sets[1].memfunc.lpp = points[2];
		this.velocity.sets[1].memfunc.rpp = points[5];
		this.velocity.sets[1].memfunc.rbp = points[8];
		this.velocity.sets[1].memfunc.lc = 0;
		this.velocity.sets[1].memfunc.rc = 0;
		
		// Center Member Function
		this.velocity.sets[2].memfunc.lbp = points[3];
		this.velocity.sets[2].memfunc.lpp = points[6];
		this.velocity.sets[2].memfunc.rpp = points[9];
		this.velocity.sets[2].memfunc.rbp = points[12];
		this.velocity.sets[2].memfunc.lc = 0;
		this.velocity.sets[2].memfunc.rc = 0;
		
		// Right Member Function
		this.velocity.sets[3].memfunc.lbp = points[7];
		this.velocity.sets[3].memfunc.lpp = points[10];
		this.velocity.sets[3].memfunc.rpp = points[13];
		this.velocity.sets[3].memfunc.rbp = points[15];
		this.velocity.sets[3].memfunc.lc = 0;
		this.velocity.sets[3].memfunc.rc = 0;
		
		// Far Right Member Function
		this.velocity.sets[4].memfunc.lbp = points[11];
		this.velocity.sets[4].memfunc.lpp = points[14];
		this.velocity.sets[4].memfunc.lc = 0;
		this.velocity.sets[4].memfunc.rc = 0;
		
		// ********************************************************************
		// Action Member Function 
		// ********************************************************************
		for (iter = 0; iter < 4*this.action.sets.length-4; ++iter) {
			points[iter] = randomise(-600,600);
		}
		points.sort( function(a,b) {return a - b;} );
		
		// Extreme Left Member Function
		this.action.sets[0].memfunc.rpp = points[1];
		this.action.sets[0].memfunc.rbp = points[4];
		
		// Large Left Member Function
		this.action.sets[1].memfunc.lbp = points[0];
		this.action.sets[1].memfunc.lpp = points[2];
		this.action.sets[1].memfunc.rpp = points[5];
		this.action.sets[1].memfunc.rbp = points[8];
		
		// Left Member Function
		this.action.sets[2].memfunc.lbp = points[3];
		this.action.sets[2].memfunc.lpp = points[6];
		this.action.sets[2].memfunc.rpp = points[9];
		this.action.sets[2].memfunc.rbp = points[12];
		
		// Slight Left Member Function
		this.action.sets[3].memfunc.lbp = points[7];
		this.action.sets[3].memfunc.lpp = points[10];
		this.action.sets[3].memfunc.rpp = points[13];
		this.action.sets[3].memfunc.rbp = points[16];
		
		// Center Member Function
		this.action.sets[4].memfunc.lbp = points[11];
		this.action.sets[4].memfunc.lpp = points[14];
		this.action.sets[4].memfunc.rpp = points[17];
		this.action.sets[4].memfunc.rbp = points[20];
		
		// Slight Right Member Function
		this.action.sets[5].memfunc.lbp = points[15];
		this.action.sets[5].memfunc.lpp = points[18];
		this.action.sets[5].memfunc.rpp = points[21];
		this.action.sets[5].memfunc.rbp = points[24];
		
		// Right Member Function
		this.action.sets[6].memfunc.lbp = points[19];
		this.action.sets[6].memfunc.lpp = points[22];
		this.action.sets[6].memfunc.rpp = points[25];
		this.action.sets[6].memfunc.rbp = points[28];
		
		// Large Right Member Function
		this.action.sets[7].memfunc.lbp = points[23];
		this.action.sets[7].memfunc.lpp = points[26];
		this.action.sets[7].memfunc.rpp = points[29];
		this.action.sets[7].memfunc.rbp = points[31];
		
		// Extreme Right Member Function
		this.action.sets[8].memfunc.lbp = points[27];
		this.action.sets[8].memfunc.lpp = points[30];
		
	}

    // ********************************************************************
    // Function:    exportAsString()
    // Purpose:     Exports the controller in a comma separated fashion
	//				stuiable for Excel import.
    // ********************************************************************
	this.exportAsString = function() {
	
		var export_string = "Fuzzy Controller Data,";
	
		// For each member function...
		variables = new Array("position", "velocity", "action");
		for (iter1 = 0; iter1 < variables.length; ++iter1) {
			// Record variable name
			export_string+="\n"+variables[iter1].capitalise()+" membership functions,";
			export_string+="\nname,lbp,lpp,lc,rpp,rbp,rc,"
			for (iter2 = 0; iter2 < this[variables[iter1]].sets.length; ++iter2) {
				// Get membership function
				export_string+="\n"+this[variables[iter1]].sets[iter2].name;
				export_string+=","+this[variables[iter1]].sets[iter2].memfunc.lbp;
				export_string+=","+this[variables[iter1]].sets[iter2].memfunc.lpp;
				export_string+=","+this[variables[iter1]].sets[iter2].memfunc.lc;
				export_string+=","+this[variables[iter1]].sets[iter2].memfunc.rpp;
				export_string+=","+this[variables[iter1]].sets[iter2].memfunc.rbp;
				export_string+=","+this[variables[iter1]].sets[iter2].memfunc.rc;
				export_string+=","
			}
		}
		
		// Get rules
		export_string+="\nRules,";
		export_string+="\nposition,velocity,action,";
		for (iter = 0; iter < this.position.sets.length; ++iter) {
			for (iter2 = 0; iter2 < this.velocity.sets.length; ++iter2) { 
				export_string+="\n";
				export_string+=iter+",";
				export_string+=iter2+",";
				export_string+=this.rules[iter][iter2]+",";
			}
		}
		
		return export_string;
		
	}
	
    // ********************************************************************
    // Function:    importAsString()
    // Purpose:     Accepts a string and imports a full controller from it
    // ********************************************************************
	this.importAsString = function(to_import) {
		var data = to_import.split(",");
		data.shift(); // Skip title
	
		// For each member function...
		variables = new Array("position", "velocity", "action");
		for (iter1 = 0; iter1 < variables.length; ++iter1) {
			data.shift(); // skip variable name
			// skip column titles
			data.shift(); data.shift(); data.shift(); data.shift(); data.shift(); data.shift(); data.shift(); 
			for (iter2 = 0; iter2 < this[variables[iter1]].sets.length; ++iter2) {
				data.shift(); // skip membfunc name
				this[variables[iter1]].sets[iter2].memfunc.lbp = parseInt(data[0]); data.shift();
				this[variables[iter1]].sets[iter2].memfunc.lpp = parseInt(data[0]); data.shift();
				this[variables[iter1]].sets[iter2].memfunc.lc = parseInt(data[0]); data.shift();
				this[variables[iter1]].sets[iter2].memfunc.rpp = parseInt(data[0]); data.shift();
				this[variables[iter1]].sets[iter2].memfunc.rbp = parseInt(data[0]); data.shift();
				this[variables[iter1]].sets[iter2].memfunc.rc = parseInt(data[0]); data.shift();
			}
		}
		
		// Get rules
		data.shift(); // Skip rules title
		// skip column titles
		data.shift(); data.shift(); data.shift();
		for (iter = 0; iter < this.position.sets.length; ++iter) {
			for (iter2 = 0; iter2 < this.velocity.sets.length; ++iter2) { 
				this.rules[parseInt(data[0])][parseInt(data[1])]=parseInt(data[2]); data.shift(); data.shift(); data.shift();
			}
		}
		
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
		// Default membership values
		var pos = new Array(0,0,0,0,0), 
			vel = new Array(0,0,0,0,0),
			act = new Array(0,0,0,0,0,0,0,0,0);
		
		// Clamp input into universe of discourse
		line_position = clamp(line_position, -600, 600);
		line_velocity = clamp(line_velocity, -600, 600);
		
		// Process inputs into set membership values
		for (iter = 0; iter < pos.length; ++iter) {
			pos[iter] = this.fuzzify("position",iter,line_position);
		}
		for (iter = 0; iter < vel.length; ++iter) {
			vel[iter] = this.fuzzify("velocity",iter,line_velocity);
		}
		
		// Use rules to determine degree of action membership
		for (iter = 0; iter < pos.length; ++iter) {
			for (iter2 = 0; iter2 < vel.length; ++iter2) {
				var act_index = this.rules[iter][iter2];
				act[act_index] = Math.max(act[act_index], Math.min(pos[iter],vel[iter2]));
			}
		}
		
		// Use defuzzification to determine action from degree of membership
		var weighted_result = 0, // default value of 0
			total_area = 0,
			velocity_change = 0;
		for (iter = 0; iter < act.length; ++iter) {
			var result = this.defuzzify("action",iter,act[iter])
			weighted_result += result.value*result.area;
			total_area += result.area;
		}
		if (total_area > 0) velocity_change = weighted_result/total_area;
		
		return velocity_change; 
	}
	
	
    // ********************************************************************
    // Function:    processOutput()
    // Purpose:     Given inputs and their set memberships, determines the
	//				output based it's rules.
    // Input:       pos_input - position set membership values
	//				vel_input - velocity set membership values
    // Output:      result - the membership value for this output
    // ********************************************************************
	this.processOutput = function(pos_input, vel_input) {
		var result = 0;
		for (var iter = 0; iter < this.posrules.length; ++iter) {
			// get the correct position and velocity from the provided sets
			var position = pos_input[this.posrules[iter]]; 
			var velocity = vel_input[this.velrules[iter]];
			// AND the two together, then OR them with the result.
			result = Math.max(result, Math.min(position,velocity))
		}
		return result;
	}
	
    // ********************************************************************
    // Function:    fuzzify()
    // Purpose:     Determine the set membership for the given input
    // Input:       variable - The variable being processed
	//				set - the set to check for membership
	//				input - value to evaluate membership from
    // Output:      fuzzy_value - value of the fuzzy membership
    // ********************************************************************
	this.fuzzify = function(variable, set, input) {
		
		input = clamp(input, -600, 600);
		
		//console.log("Fuzzifying variable = "+variable+", set="+set+", input="+input);
	
		// Determine points
		var lbp = this[variable].sets[set].memfunc.lbp,
			lpp = this[variable].sets[set].memfunc.lpp;
		var	lc = this[variable].sets[set].memfunc.lc,
			lbc = lbp+(this[variable].sets[set].memfunc.lc/10)*(lpp-lbp),
			lpc = lpp-(this[variable].sets[set].memfunc.lc/10)*(lpp-lbp);
		var rbp = this[variable].sets[set].memfunc.rbp,
			rpp = this[variable].sets[set].memfunc.rpp;
		var	rc = this[variable].sets[set].memfunc.rc,
			rpc = rpp+(this[variable].sets[set].memfunc.rc/10)*(rbp-rpp),
			rbc = rbp-(this[variable].sets[set].memfunc.rc/10)*(rbp-rpp);
		var fuzzy_value=0;
		//console.log("   lbp = "+lbp+", lpp="+lpp+", lc="+lc+", lbc="+lbc+", lpc="+lpc);
		//console.log("   rbp = "+rbp+", rpp="+rpp+", rc="+rc+", rpc="+rpc+", rbc="+rbc);
		
		// Below lbp - non-member
		if (input <= lbp) {
			fuzzy_value=0;
		}
		
		// Between lbp and lpp - in the sloped region of the graph
		else if (input > lbp && input < lpp) {
			// If there's no curviness, just use a straight line (faster)
			if (lc == 0) {
				var slope = (1)/(lpp-lbp);
				fuzzy_value = (input-lbp)*slope;
			}
			else { // use bezier curve equation to determine membership
				// Find cubic root t from x coordinates
				var a = -lbp+3*lbc-3*lpc+lpp,
					b = 3*lbp-6*lbc+3*lpc,
					c = -3*lbp+3*lbc,
					d = lbp - input;
				var t = this.solveCubic(a,b,c,d);
				
				// Given t, calculate y
				var y = Math.pow((1-t),3) + 3*Math.pow((1-t),2)*t;
				fuzzy_value = 1-y; 
			}
		}
		
		// Between lpp and rpp - total membership
		else if (input >= lpp && input <= rpp) {
			fuzzy_value = 1;
		}
		
		// Between rpp and rbp - in the sloped region of the graph
		else if (input > rpp && input < rbp) {
			// If there's no curviness, just use a straight line (faster)
			if (rc == 0) {
				var slope = (1)/(rbp-rpp);
				fuzzy_value = (input-rpp)*slope;
			}
			else { // use bezier curve equation to determine membership
				// Find cubic root t from x coordinates
				var a = -rpp+3*rpc-3*rbc+rbp,
					b = 3*rpp-6*rpc+3*rbc,
					c = -3*rpp+3*rpc,
					d = rpp - input;
				var t = this.solveCubic(a,b,c,d);
				
				// Given t, calculate y
				var y = Math.pow((1-t),3) + 3*Math.pow((1-t),2)*t;
				fuzzy_value = y;
			}
		}
		
		// Above rbp - non-member
		else if (input >= rbp) {
			fuzzy_value = 0;
		}
		
		// Return result
		//console.log("   Fuzzification result: fuzzy_value = "+fuzzy_value);
		return fuzzy_value;
	}
	
    // ********************************************************************
    // Function:    solveCubic()
    // Purpose:     Given 4 coefficients, determine the root falling 
	//					between 0 and 1
    // Input:       a*x^3 + b*x^2 + c*x + d = 0
	// Output:		t = x falling between 0 and 1
    // ********************************************************************
	this.solveCubic = function(a,b,c,d) {
		var p = (3*a*c - Math.pow(b,2)) / (3 * Math.pow(a,2));
		var q = (9*a*b*c - 27*Math.pow(a,2)*d - 2*Math.pow(b,3)) / (27*Math.pow(a,3));
		var Q = p/3;
		var R = q/2;
		//console.log("   Solving cubic root for a="+a+", b="+b+", c="+c+", d="+d);
		//console.log("      Depressed cubic values p="+p+", q="+q+", Q="+Q+", R="+R);
		
		// Solve for w
		var w3 = (R + Math.sqrt(Q*Q*Q + R*R));
		var w = Math.pow(w3,(1/3)); 
		//console.log("      w3="+w3+", w="+w);
		
		var t = w - p/(3*w);
		var x = t - b/(3*a);
		//console.log("      t="+t+", x="+x);
		
		// As one equation
		// x = -b/(3*a)
			// - (1 / (3*a) ) 
					// * Math.pow((0.5)
								// *(2*b*b*b 
									// - 9*a*b*c
									// + 27*a*a*d
									// + Math.sqrt( Math.pow((2*b*b*b
															// -9*a*b*c
															// +27*a*a*d),2
												// )
												// -4*Math.pow((b*b-3*a*c),3)
									// )
								// ),1/3)
			// - (1 / (3*a) ) 
					// * Math.pow((0.5)
								// *(2*b*b*b 
									// - 9*a*b*c
									// + 27*a*a*d
									// - Math.sqrt( Math.pow((2*b*b*b
															// -9*a*b*c
															// +27*a*a*d),2
												// )
												// -4*Math.pow((b*b-3*a*c),3)
									// )
								// ),1/3)
		// //console.log("      x="+x);
		
		return x;
	}
	
    // ********************************************************************
    // Function:    defuzzify()
    // Purpose:     Given a set membership, determine the action to be
	//					taken. NOTE: Currently ignores the curviness
	//					of output functions.
    // Input:       variable - The variable being processed
	//				set - the set to check for membership
	//				input - fuzzy set membership
    // Output:      result.value - real interpretation based on fuzzy set
	//				result.area - weighting for the value
    // ********************************************************************
	this.defuzzify = function(variable, set, input) {
		// Error handling
		if (!this[variable]) {
			console.error("Cannor find variable "+variable);
			return;
		}
		
		//console.log("Defuzzifying variable = "+variable+", set="+set+", input="+input);
	
		// Determine points
		var lbp = this[variable].sets[set].memfunc.lbp,
			lpp = this[variable].sets[set].memfunc.lpp;
		var	lc = this[variable].sets[set].memfunc.lc,
			lbc = lbp+(this[variable].sets[set].memfunc.lc/10)*(lpp-lbp),
			lpc = lpp-(this[variable].sets[set].memfunc.lc/10)*(lpp-lbp);
		var rbp = this[variable].sets[set].memfunc.rbp,
			rpp = this[variable].sets[set].memfunc.rpp;
		var	rc = this[variable].sets[set].memfunc.rc,
			rpc = rpp+(this[variable].sets[set].memfunc.rc/10)*(rbp-rpp),
			rbc = rbp-(this[variable].sets[set].memfunc.rc/10)*(rbp-rpp);
		var result = new Object(); 
		result.value = 0; 
		result.area = 0;
		
		// Non-member - no recommendation able to be made
		if (input == 0) {
			// Result remains 0,0
		}
		// Full-member
		if (input == 1) {
			// Area under the peak
			result.value = lpp+(rpp-lpp)/2;
			result.area = (rpp-lpp);
		}
		
		// Partial member
		if (input > 0 && input < 1) {
			// Area under the partial shape, we need x coordinates for both sides.
			var lx, rx;
			
			// Left side
			// If there's no curviness, just use a straight line (faster)
			//if (lc == 0) {
				var lslope = (1)/(lpp-lbp);
				lx = lbp + input/lslope;
			// } else { // use bezier curve equation to determine x
				// var a = 0+3*0-3*1+1,
					// b = 3*0-6*0+3*1,
					// c = -3*0+3*0,
					// d = 0 - input;
				// var a = -2,
					// b = 3,
					// c = 0,
					// d = -input;
				// var t = this.solveCubic(a,b,c,d);
				
				// //console.log("   Cubic root t = "+t);
				
				// t = 0.5 * (
					// Math.pow(2*Math.sqrt(input*input - input)-2*input+1,(1/3))
					// + 1 / (Math.pow((2*Math.sqrt(input*input - input)-2*input+1),(1/3))) + 1
					// )
				// //console.log("   Wolfram t = "+t);
				
				
				//Given t, calculate x
				// lx = Math.pow((1-t),3)*lbp + 3*Math.pow((1-t),2)*t*lbc 
						// + (1-t)*t*t*lpc + t*t*t*lpp;
			// }
			
			// Left side
			// If there's no curviness, just use a straight line (faster)
			// if (rc == 0) {
				var rslope = (-1)/(rbp-rpp);
				rx = rpp + (input-1)/rslope;
			// } else { // use bezier curve equation to determine x
				// var a = -1+3*1-3*0+0,
					// b = 3*1-6*1+3*0,
					// c = -3*1+3*1,
					// d = 1 - input;
				// var a = 2,
					// b = -3,
					// c = 0,
					// d = 1 - input;
				// var t = this.solveCubic(a,b,c,d);
				
				//Given t, calculate x
				// rx = Math.pow((1-t),3)*rpp + 3*Math.pow((1-t),2)*t*rpc 
						// + (1-t)*t*t*rbc + t*t*t*rbp;
			// }
			
			// Calculate value and area
			result.value = lx+(rx-lx)/2;
			result.area = (rx-lx)*input;
		}
		
		// Return the result
		//console.log("   Defuzzification result: value = "+result.value+", area = "+result.area);
		return result;
		
	}
}