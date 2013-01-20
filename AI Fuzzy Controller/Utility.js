// ************************************************************************ 
// File Name:   Utility.js 
// Author:      Sarah Herzog 
// Purpose:     Utility JS functions for use with the HTML inputs
// ************************************************************************ 

var controller = new FuzzyController();
controller.initialise();
//controller.randomise();
var CANVAS_WIDTH = 1200,                 
	CANVAS_HEIGHT = 300,
	FUNC_TOP = 50,
	FUNC_BOT = 250;

// ************************************************************************
// Function:    inputUpdate()
// Purpose:     Updates the provided element to the provided value. 
// ************************************************************************
function inputUpdate(variable, set, point, newValue) {
	// Error checking
	if (point == "lbp") {
		if (newValue > controller[variable].sets[set].memfunc.lpp)
			newValue = controller[variable].sets[set].memfunc.lpp;
	}
	if (point == "lpp") {
		if (newValue < controller[variable].sets[set].memfunc.lbp)
			newValue = controller[variable].sets[set].memfunc.lbp;
		if (newValue > controller[variable].sets[set].memfunc.rpp)
			newValue = controller[variable].sets[set].memfunc.rpp;
	}
	if (point == "rpp") {
		if (newValue < controller[variable].sets[set].memfunc.lpp)
			newValue = controller[variable].sets[set].memfunc.lpp;
		if (newValue > controller[variable].sets[set].memfunc.rbp)
			newValue = controller[variable].sets[set].memfunc.rbp;
	}
	if (point == "rbp") {
		if (newValue < controller[variable].sets[set].memfunc.rpp)
			newValue = controller[variable].sets[set].memfunc.rpp;
	}
	if (point == "lc" || point == "rc") {
		if (newValue < 0)
			newValue = 0;
		if (newValue > 10)
			newValue = 10;
	}
	// Update input fields
	if (document.getElementById("input_"+variable+"_memfunc_"+set+"_"+point))
		document.getElementById("input_"+variable+"_memfunc_"+set+"_"+point).value=newValue;
	if (document.getElementById("readout_"+variable+"_memfunc_"+set+"_"+point))
		document.getElementById("readout_"+variable+"_memfunc_"+set+"_"+point).value=newValue;
		
	// Update value
	if (point != "name")
		controller[variable].sets[set].memfunc[point] = parseInt(newValue, 10);
	
	// Update canvas
	updateMemFuncCanvas(variable);
}

// ************************************************************************
// Function:    ruleUpdate()
// Purpose:     Updates a rule in the controller to the provided value
// ************************************************************************
function ruleUpdate(pos, vel, val) {
	controller.rules[pos][vel] = val;
}

// ************************************************************************
// Function:    memfuncInit()
// Purpose:     Initialises the memory function values and input. 
// ************************************************************************
function memfuncInit() {
	// Set inputs to default values
	var variables = new Array("position", "velocity", "action")
	for (var variable in variables) {
		variable = variables[variable];
		for (iter=0; iter < controller[variable].sets.length; ++iter) {
			var test = controller[variable].sets[iter].memfunc;
			for (var point in controller[variable].sets[iter].memfunc) {
				inputUpdate(variable, iter, point, controller[variable].sets[iter].memfunc[point]);
			}
		}
	}
	
	// Rules set to defaults
	for (iter = 0; iter < controller.rules.length; ++iter) {
		for (iter2 = 0; iter2 < controller.rules[iter].length; ++iter2) {
			document.getElementById("readout_rules_"+iter+"_"+iter2).value=controller.rules[iter][iter2];
		}
	}
	
	// Initialise canvas
	var canvas_memfunc_pos = document.getElementById('canvas_position_memfunc');
	var canvas_memfunc_vel = document.getElementById('canvas_velocity_memfunc');
	var canvas_memfunc_act = document.getElementById('canvas_action_memfunc');
	canvas_memfunc_pos.width = CANVAS_WIDTH;
	canvas_memfunc_pos.height = CANVAS_HEIGHT;
	canvas_memfunc_vel.width = CANVAS_WIDTH;
	canvas_memfunc_vel.height = CANVAS_HEIGHT;
	canvas_memfunc_act.width = CANVAS_WIDTH;
	canvas_memfunc_act.height = CANVAS_HEIGHT;
	updateMemFuncCanvas("position");
	updateMemFuncCanvas("velocity");
	updateMemFuncCanvas("action");
}

// ************************************************************************
// Function:    updateMemFuncCanvas()
// Purpose:     Updates the canvas for the provided variable 
// ************************************************************************
function updateMemFuncCanvas(variable) {

	// Setup
	var canvas = document.getElementById('canvas_'+variable+'_memfunc');
	if (!canvas) return; 			// Exit out if we failed to get the canvas
	var ctx = canvas.getContext('2d');
	ctx.fillStyle = 'rgba('+        // Sets fill color
		'255,255,200,255)';
	ctx.beginPath();                // Start drawing
	ctx.rect(0,0,                   // Draws rectangle
		CANVAS_WIDTH,
		CANVAS_HEIGHT);        
	ctx.closePath();                // Ends drawing
	ctx.fill();                     // Fills rectangle w/ active color
	
	
	// Draw axis and labels
	ctx.lineWidth = 1;				// Set line width
	ctx.strokeStyle = "#999";		// Set line color
	ctx.fillStyle = "#999";			// Set line color
	// Bottom Line
	ctx.beginPath();
	ctx.moveTo(0,FUNC_BOT);
	ctx.lineTo(CANVAS_WIDTH,FUNC_BOT);
	ctx.stroke();
	// Top Line
	ctx.beginPath();
	ctx.moveTo(0,FUNC_TOP);
	ctx.lineTo(CANVAS_WIDTH,FUNC_TOP);
	ctx.stroke();
	// Center Line
	ctx.beginPath();
	ctx.moveTo(CANVAS_WIDTH/2,0);
	ctx.lineTo(CANVAS_WIDTH/2,CANVAS_HEIGHT);
	ctx.stroke();
	// Y Axis Labels
	ctx.font = '20px san-serif';
	ctx.textBaseline = 'top';
    ctx.textAlign = 'left';
	ctx.fillText("1", CANVAS_WIDTH/2+5, FUNC_TOP+5);
	// X Axis Labels
	ctx.fillText("0", CANVAS_WIDTH/2+5, FUNC_BOT+5);
    ctx.textAlign = 'center';
	for (i=1;i<12;i=i+1){
		if (i != 6) {
			axis_label = i*100 - 600;
			ctx.fillText(axis_label, i*100, FUNC_BOT+5);
		}
	}
    ctx.textAlign = 'right';
	ctx.fillText("600", 1200-5, FUNC_BOT+5);
    ctx.textAlign = 'left';
	ctx.fillText("-600", 5, FUNC_BOT+5);
	
	// Draw lines
	drawMemFunc(variable, 0, "#339");
	drawMemFunc(variable, 1, "#939");
	drawMemFunc(variable, 2, "#393");
	drawMemFunc(variable, 3, "#336");
	drawMemFunc(variable, 4, "#933");
	if (variable == "action") {
		drawMemFunc(variable, 5, "#363");
		drawMemFunc(variable, 6, "#993");
		drawMemFunc(variable, 7, "#399");
		drawMemFunc(variable, 8, "#633");
	}
	
}

// ************************************************************************
// Function:    drawMemFunc()
// Purpose:     Draws a specific set's membership function 
// ************************************************************************
function drawMemFunc(variable, set, color) {

	// Setup line
	var canvas = document.getElementById('canvas_'+variable+'_memfunc');
	var ctx = canvas.getContext('2d');
	ctx.lineWidth = 3;				// Set line width
	ctx.strokeStyle = color;		// Set line color
	ctx.fillStyle = color;			// Set line color
	
	// Determine points
	var lbp = 600+controller[variable].sets[set].memfunc.lbp,
		lpp = 600+controller[variable].sets[set].memfunc.lpp;
	var	lbc = lbp+(controller[variable].sets[set].memfunc.lc/10)*(lpp-lbp),
		lpc = lpp-(controller[variable].sets[set].memfunc.lc/10)*(lpp-lbp);
	var rbp = 600+controller[variable].sets[set].memfunc.rbp,
		rpp = 600+controller[variable].sets[set].memfunc.rpp;
	var	rpc = rpp+(controller[variable].sets[set].memfunc.rc/10)*(rbp-rpp),
		rbc = rbp-(controller[variable].sets[set].memfunc.rc/10)*(rbp-rpp);
		
	// Left side
	ctx.beginPath();
	ctx.moveTo(lbp, FUNC_BOT);
	ctx.bezierCurveTo(lbc, FUNC_BOT, lpc, FUNC_TOP, lpp, FUNC_TOP);
	ctx.stroke();
	
	// Top
	ctx.beginPath();
	ctx.moveTo(lpp,FUNC_TOP);
	ctx.lineTo(rpp,FUNC_TOP);
	ctx.stroke();
	
	// Right side
	ctx.beginPath();
	ctx.moveTo(rpp, FUNC_TOP);
	ctx.bezierCurveTo(rpc, FUNC_TOP, rbc, FUNC_BOT, rbp, FUNC_BOT);
	ctx.stroke();
	
	// Title
	ctx.font = '20px san-serif';
	ctx.textBaseline = 'bottom';
    ctx.textAlign = 'center';
	
	// Label
	ctx.fillText(controller[variable].sets[set].name, (lpp+(rpp-lpp)/2), FUNC_TOP);
}

// ************************************************************************
// Function:    testMemFunc()
// Purpose:     Tests the position member function with the provided value 
// ************************************************************************
function testMemFunc(variable, newValue) {
	for (iter = 0; iter < controller[variable].sets.length; ++iter) {
		document.getElementById("readout_"+variable+"_test_"+iter).value=controller.fuzzify(variable,iter,newValue);
	}
}

// ************************************************************************
// Function:    testDefuzzify()
// Purpose:     Defuzzifies the selected action set and value 
// ************************************************************************
function testDefuzzify() {
	var result = 
		controller.defuzzify("action",
			document.getElementById("input_action_test_set").value,
			document.getElementById("input_action_test_value").value);
	document.getElementById("input_action_test_result").value = result.value;
	document.getElementById("input_action_test_area").value = result.area;
}

// ************************************************************************
// Function:    testOverall()
// Purpose:     Tests the overall controller 
// ************************************************************************
function testOverall() {
	var result = 
		controller.process(document.getElementById("input_testing_position").value,
			document.getElementById("input_testing_velocity").value);
	document.getElementById("input_testing_action").value = result;
}

// ************************************************************************
// Function:    exportController()
// Purpose:     Exports the controller to string 
// ************************************************************************
function exportController() {
	var result = controller.exportAsString();
	document.getElementById("input_export").value = result;
}

// ************************************************************************
// Function:    exportResults()
// Purpose:     Exports the results to string 
// ************************************************************************
function exportResults() {
	var result = game_results.exportAsString();
	document.getElementById("input_results_export").value = result;
}

// ************************************************************************
// Function:    importController()
// Purpose:     Exports the controller to string 
// ************************************************************************
function importController() {
	var result = document.getElementById("input_import").value;
	controller.importAsString(result);
	memfuncInit();
}

// ************************************************************************
// Function:    clamp()
// Purpose:     limits value to the range min..max
// ************************************************************************	
function clamp(value, min, max) {
	if (value < min) value = min;
	if (value > max) value = max;
	return value;
}

// ************************************************************************
// Function:    randomise()
// Purpose:     generates an integer in the range min..max (inclusive)
// ************************************************************************	
function randomise(min, max) {
	return Math.floor((Math.random()*(max-min+1))+min);
}

// ************************************************************************
// Function:    choose()
// Purpose:     Chooses a random item from an array
// ************************************************************************	
function choose(array) {
	var index = randomise(0, array.length-1);
	return array[index];
}

// ************************************************************************
// Function:    choose()
// Purpose:     Chooses a random item from an array
// ************************************************************************	
function choose(a,b) {
	if (randomise(0, 1)) return a; else return b;
}

// ************************************************************************
// Function:    capitalise()
// Purpose:     Capitalises the first character in a string.
// ************************************************************************	
String.prototype.capitalise = function() {
    return this.charAt(0).toUpperCase() + this.slice(1);
}