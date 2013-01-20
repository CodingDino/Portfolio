// ************************************************************************ 
// File Name:   GeneticAlgorithm.js 
// Author:      Sarah Herzog 
// Purpose:     Runs Genetic Algorithm tuning of a controller
// ************************************************************************ 

// Global Variables
var OPS = 100,                          // Operations per second
    //RUNTIME = 4,						// Time the game will run before ending and processing results
	NUM_SOLUTIONS = 1000,				// Number of members of the gene pool at any given time
	MUTATION_CHANCE = 0.0005;			// 0.05% chance of mutation
    
// GeneticAlgorithm Class
function GeneticAlgorithm() {
    // ********************************************************************
    // Data Members 
    // ********************************************************************
    
    // Timers
    this.now = new Date();
    this.start_time = this.now.getTime();
    this.mark_time = this.start_time;
    this.current_time = this.start_time;
	this.stop = false;
	this.interval_ID = 0;
	this.generation = 1;
	
	// Arrays of objects
	this.cars = new Array();
	this.lines = new Array();
	this.tracks = new Array();
	this.controls = new Array();
	this.results = new Array();
	
	// Set up individual objects
	for (i = 0; i < NUM_SOLUTIONS; ++i) {
		this.cars.push(new Car());
		this.lines.push(new Line());
		this.tracks.push(new Track());
		this.controls.push(new FuzzyController());
		this.results.push(new Results());
	}
	for (i = 0; i < NUM_SOLUTIONS; ++i) {
		this.tracks[i].initialise();
		this.controls[i].initialise();
		this.controls[i].randomise();
		this.results[i].initialise();
	}

    // ********************************************************************
    // Function:    gameLoop()
    // Purpose:     Continuous loop runs while the game is loaded. 
    // ********************************************************************
    this.gameLoop = function() {
        this.logic();     // Run all logic functions for each solution
		// Drawing only happens after a track is finished (draw generation's results to screen)
		
		if (this.stop) {
			console.log("Processing generation "+this_genetics.generation+"...");
			// Stop simulation
			stopGenetics();
			
			// Process results for all solutions
			var now = new Date();
			var current_time = now.getTime();
			
			// SELECTION, CROSSOVER, AND MUTATION
			console.log("   Calculating fitness values...");
			// Calculate raw fitness and sum raw fitnesses
			// Actually gets the inverse, as a high mean is undesireable.
			var max_fitness = 0;
			for (i = 0; i < NUM_SOLUTIONS; ++i) {
				this.results[i].process(current_time - this.start_time);
				this.controls[i].inverse_raw_fitness = this.results[i].statistics.mean_distance;
				this.controls[i].results = this.results[i];
				if (this.controls[i].inverse_raw_fitness > max_fitness) max_fitness = this.controls[i].inverse_raw_fitness;
				//console.log("      Processing solution with performance: "+this.controls[i].inverse_raw_fitness)
			}
			var sum_raw_fitness=0;
			for (i = 0; i < NUM_SOLUTIONS; ++i) {
				this.controls[i].raw_fitness = max_fitness-this.controls[i].inverse_raw_fitness;
				sum_raw_fitness += this.controls[i].raw_fitness;
			}
			// Normallise Fitness Values
			for (i = 0; i < NUM_SOLUTIONS; ++i) {
				this.controls[i].normalised_fitness = this.controls[i].raw_fitness / sum_raw_fitness;
			}
			// Sort by decending fitness values
			this.controls.sort( function(a,b) {return b.normalised_fitness - a.normalised_fitness;} );
			// Draw results to screen
			this.draw(this.controls[0].results);
			// Calculate accumulated normalised fitness values
			var sum_normalised_fitness=0;
			for (i = 0; i < NUM_SOLUTIONS; ++i) {
				sum_normalised_fitness += this.controls[i].normalised_fitness;
				this.controls[i].accumulated_normalised_fitness = sum_normalised_fitness;
			}
			console.log("   Top performing solution: "+this.controls[0].inverse_raw_fitness+" mean distance from line.")
			// Create array to hold new controllers
			var new_controllers = Array();
			// Repeat the following until we have a new population
			console.log("   Producing offspring...");
			while (new_controllers.length < NUM_SOLUTIONS) {
				// Determine R between 0 and 1;
				var R1 = Math.random(), R2 = Math.random();
				var parent1=0, parent2=0;
				// Determine parent1 and parent2
				for (iter = 0; iter < NUM_SOLUTIONS; ++iter) {
					//console.log("      Checking solution with ANF of "+this.controls[iter].accumulated_normalised_fitness+ " against R1 = " +R1+ " and R2 = " +R2 )
					if (!parent1 && this.controls[iter].accumulated_normalised_fitness >= R1) {
						parent1 = this.controls[iter];
						//console.log("      Found parent1 with performance " +parent1.inverse_raw_fitness)
					}
					if (!parent2 && this.controls[iter].accumulated_normalised_fitness >= R2) {
						parent2 = this.controls[iter];
						//console.log("      Found parent2 with performance " +parent2.inverse_raw_fitness)
					}
					if (parent1 && parent2) break;
				}
				// Use Crossover to determine offspring settings
				//console.log("      Crossing parents with performance " +parent1.inverse_raw_fitness+ " and " +parent2.inverse_raw_fitness)
				var offspring = this.crossover(parent1,parent2);
				// Mutation
				//console.log("      Checking for mutation.")
				offspring = this.mutate(offspring);
				// Save resulting offspring in new array;
				new_controllers.push(offspring);
			}
			// Prepare solutions for next round of evaluation
			if (this.stopall) {
				var result = this.controls[0].exportAsString();
				document.getElementById("input_genetics_export").value = result;
			}
			else {
				console.log("   Preparing the next generation...");
				++this.generation;
				this.controls = new_controllers;
				// Prepare other arrays
				for (i = 0; i < NUM_SOLUTIONS; ++i) {
					this.tracks[i].reset();
					this.results[i].reset();
					this.cars[i].reset();
					this.lines[i].reset();
				}
				this.stop = false;
				startGenetics();
			}
		}
    } 
	
    // ********************************************************************
    // Function:    crossover()
    // Purpose:     Combines two controllers using the Uniform Crossover method
    // ********************************************************************
    this.crossover = function(p1,p2) {
		//console.log("         Parents passed in with performance " +p1.inverse_raw_fitness+ " and " +p2.inverse_raw_fitness);
		var offspring = new FuzzyController();
		var parents = new Array();
		parents[0] = p1;
		parents[1] = p2;
		choose(parents);
		//console.log("         Parents passed in with performance " +parents[0].inverse_raw_fitness+ " and " +parent[1].inverse_raw_fitness);
		offspring.initialise();
	
		// Fitness Function Crossover
		variables = new Array("position", "velocity", "action");
		var point = new Array(0,0,0,0);
		for (iter1 = 0; iter1 < variables.length; ++iter1) {
			for (iter2 = 0; iter2 < offspring[variables[iter1]].sets.length; ++iter2) {
				point[0] = choose(p1,p2)[variables[iter1]].sets[iter2].memfunc.lbp;
				//console.log("         Parent donated point "+point[0]+" from "+variables[iter1]+" set "+iter2+" lbp")
				point[1] = choose(p1,p2)[variables[iter1]].sets[iter2].memfunc.lpp;
				//console.log("         Parent donated point "+point[1]+" from "+variables[iter1]+" set "+iter2+" lpp")
				point[2] = choose(p1,p2)[variables[iter1]].sets[iter2].memfunc.rpp;
				//console.log("         Parent donated point "+point[2]+" from "+variables[iter1]+" set "+iter2+" rpp")
				point[3] = choose(p1,p2)[variables[iter1]].sets[iter2].memfunc.rbp;
				//console.log("         Parent donated point "+point[3]+" from "+variables[iter1]+" set "+iter2+" rbp")
				
				point.sort( function(a,b) {return a - b;} );
				
				offspring[variables[iter1]].sets[iter2].memfunc.lbp = point[0];
				//console.log("         Offspring assigned "+point[0]+" for "+variables[iter1]+" set "+iter2+" lbp")
				offspring[variables[iter1]].sets[iter2].memfunc.lpp = point[1];
				//console.log("         Offspring assigned "+point[1]+" for "+variables[iter1]+" set "+iter2+" lpp")
				offspring[variables[iter1]].sets[iter2].memfunc.rpp = point[2];
				//console.log("         Offspring assigned "+point[2]+" for "+variables[iter1]+" set "+iter2+" rpp")
				offspring[variables[iter1]].sets[iter2].memfunc.rbp = point[3];
				//console.log("         Offspring assigned "+point[3]+" for "+variables[iter1]+" set "+iter2+" rbp")
				
				// curviness
				offspring[variables[iter1]].sets[iter2].memfunc.lc = choose(p1,p2)[variables[iter1]].sets[iter2].memfunc.lc;
				offspring[variables[iter1]].sets[iter2].memfunc.rc = choose(p1,p2)[variables[iter1]].sets[iter2].memfunc.rc;
			}
		}
		
		// Selection of data sent to log
		//console.log("         Offpsring formed with position center lbp of: "+offspring.position.sets[2].memfunc.lbp)
		
		// Note: currently not crossing over rules
	
		return offspring;
	}
	
    // ********************************************************************
    // Function:    mutate()
    // Purpose:     mutates a controller at a small chance
    // ********************************************************************
    this.mutate = function(controller) {
	
		variables = new Array("position", "velocity", "action");
		for (iter1 = 0; iter1 < variables.length; ++iter1) {
			for (iter2 = 0; iter2 < controller[variables[iter1]].sets.length; ++iter2) {
				if (Math.random() < MUTATION_CHANCE) {
					controller[variables[iter1]].sets[iter2].memfunc.lbp = randomise(-650, controller[variables[iter1]].sets[iter2].memfunc.lpp);
					//console.log("         MUTATION! "+variables[iter1]+" set "+iter2+" lbp = "+controller[variables[iter1]].sets[iter2].memfunc.lbp)
				}
				if (Math.random() < MUTATION_CHANCE) {
					controller[variables[iter1]].sets[iter2].memfunc.lpp = randomise(controller[variables[iter1]].sets[iter2].memfunc.lbp, controller[variables[iter1]].sets[iter2].memfunc.rpp);
					//console.log("         MUTATION! "+variables[iter1]+" set "+iter2+" lpp = "+controller[variables[iter1]].sets[iter2].memfunc.lpp)
				}
				if (Math.random() < MUTATION_CHANCE) {
					controller[variables[iter1]].sets[iter2].memfunc.rpp = randomise(controller[variables[iter1]].sets[iter2].memfunc.lpp, controller[variables[iter1]].sets[iter2].memfunc.rbp);
					//console.log("         MUTATION! "+variables[iter1]+" set "+iter2+" rpp = "+controller[variables[iter1]].sets[iter2].memfunc.rpp)
				}
				if (Math.random() < MUTATION_CHANCE) {
					controller[variables[iter1]].sets[iter2].memfunc.rbp = randomise(controller[variables[iter1]].sets[iter2].memfunc.rpp, 650);
					//console.log("         MUTATION! "+variables[iter1]+" set "+iter2+" rbp = "+controller[variables[iter1]].sets[iter2].memfunc.rbp)
				}
			}
		}
		
		// Note: currently not mutating rules
	
		return controller;
	}
	
    // ********************************************************************
    // Function:    logic()
    // Purpose:     Handle all game logic. 
    // ********************************************************************
    this.logic = function() {
		if (this.stop) return;
	
		// Process each solution
		for (i = 0; i < NUM_SOLUTIONS; ++i) {
	
			// Get track control
			this.tracks[i].logic(this.lines[i]);
		
			// Perform Line Logic
			this.lines[i].logic(false);
			
			// Perform Car Logic
			this.cars[i].logic(this.lines[i], this.controls[i]);
			
			// Record results
			this.results[i].record(this.lines[i], this.cars[i]);
			
			// Stop game if done
			if (this.tracks[i].done) {
				this.stop = true;
			}
			
		}
		
    } 
    
    // ********************************************************************
    // Function:    clear()
    // Purpose:     Sets up the canvas for each frame. 
    // ********************************************************************
    this.clear = function() {
		this.ctx.fillStyle = 'rgba('+        // Sets fill color
		'255,255,200,255)';
        this.ctx.beginPath();                // Start drawing
        this.ctx.rect(0,0,                   // Draws rectangle
            CANVAS_WIDTH,
            CANVAS_HEIGHT);        
        this.ctx.closePath();                // Ends drawing
        this.ctx.fill();                     // Fills rectangle w/ active color
		
		// Text properties
		this.ctx.font = '20px san-serif';
		this.ctx.textBaseline = 'top';
		this.ctx.textAlign = 'right';
		this.ctx.fillStyle = "#222";
		
		// Statistics
		this.ctx.fillText("SIMULATING GENERATION "+this.generation+"...", CANVAS_WIDTH-5, 5);
		
    }
	
    // ********************************************************************
    // Function:    draw()
    // Purpose:     Draws all game objects and text to the canvas. 
    // ********************************************************************
    this.draw = function(result) {
        // Clear the canvas to the level's bg color
        this.clear();
		
		// Draw current results to the screen
		result.draw(this.ctx);
		
		// Text properties
		this.ctx.font = '20px san-serif';
		this.ctx.textBaseline = 'top';
		this.ctx.textAlign = 'right';
		this.ctx.fillStyle = "#222";
		
		// Statistics
		this.ctx.fillText("DISPLAYED BEST RESULT FROM "+this.generation+".", CANVAS_WIDTH-5, 5);
		if (!this.stopall) this.ctx.fillText("SIMULATING GENERATION "+(this.generation+1)+"...", CANVAS_WIDTH-5, 25);
		
    }	
	
}

// ********************************************************************
// Function:    geneticsLoop()
// Purpose:     Start function which adds game_Loop to interval
// ********************************************************************
function geneticsLoop() {
	this_genetics.gameLoop();
}

// ********************************************************************
// Function:    startGenetics()
// Purpose:     Start function which adds game_Loop to interval
// ********************************************************************
function startGenetics() {
	this_genetics.interval_ID = setInterval(geneticsLoop, 1000 / OPS);
	
    var now = new Date();
    this_genetics.start_time = now.getTime();
	
	console.log("Simulating generation "+this_genetics.generation+"...");
}

// ********************************************************************
// Function:    stopGenetics()
// Purpose:     Removes the game loop from the interval.
// ********************************************************************
function stopGenetics() {
	if (this_genetics.interval_ID) clearInterval(this_genetics.interval_ID);
}

// ********************************************************************
// Function:    stopCalculations()
// Purpose:     Stops genetic calculations entirely.
// ********************************************************************
function stopCalculations() {
	this_genetics.stopall = true;
}

// ********************************************************************
// Function:    initialiseGenetics()
// Purpose:     Creates a game instance and initialises game
// ********************************************************************
function initialiseGenetics() {
	
	this_genetics = new GeneticAlgorithm();     // Create instance of the genetic algorithm
	
	// Initialise canvas  
	this_genetics.canvas = document.getElementById('canvas_genetics'),   // The canvas itself
	this_genetics.ctx = this_genetics.canvas.getContext('2d'),           // 2d graphics context
	this_genetics.canvas.width = CANVAS_WIDTH;
	this_genetics.canvas.height = CANVAS_HEIGHT;
	//this_genetics.clear();
}