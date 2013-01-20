// ************************************************************************ 
// File Name:   Game.js 
// Author:      Sarah Herzog 
// Purpose:     Wrapper and main game loop. 
// ************************************************************************ 

// Global Variables
var gLoop,                              // Game loop timer
    canvas_game,   						// The canvas itself
    ctx,           						// 2d graphics context
    FPS = 60,                           // Frames per second
    DEBUGMODE = true,                   // Debug mode
	RUNTIME = 60;						// Time the game will run before ending and processing results

// Movement keys
UP = 38;
DOWN = 40;
LEFT = 37;
RIGHT = 39;
NUM1 = 49;
NUM2 = 50;
NUM3 = 51;
    
// Game Class
function Game() {
    // ********************************************************************
    // Data Members 
    // ********************************************************************
    
    // Timers
    game_now = new Date();
    game_start_time = game_now.getTime();
    game_mark_time = game_start_time;
    game_current_time = game_start_time;
	game_stop = true;
	game_interval_ID = 0;
	
	// Keypresses
	game_keypress = new Object();
	game_user_control = false;
	
	// Objects
	game_car = new Car();
	game_line = new Line();
	game_readout = new Readout();
	game_track = new Track();
	game_results = new Results();
	
	// Initialisation
	game_track.initialise();
	game_results.initialise();
    
    // ********************************************************************
    // Function:    onkeydown()
    // Purpose:     Listens for key presses and passes them to the level 
    //              object. 
    // ********************************************************************
    document.onkeydown = function(e) {
		if (game_user_control) {
			if (e.keyCode == LEFT) {
				game_keypress.left = true;
				game_line.direction = -1;
			}
			if (e.keyCode == RIGHT) {
				game_keypress.right = true;
				game_line.direction = 1;
			}
			if (e.keyCode == UP) {
				game_keypress.up = true;
			}
			if (e.keyCode == DOWN) {
				game_keypress.down = true;
			}
			if (e.keyCode == NUM1) {
				game_keypress.num1 = true;
			}
			if (e.keyCode == NUM2) {
				game_keypress.num2 = true;
			}
			if (e.keyCode == NUM3) {
				game_keypress.num3 = true;
			}
		}
    }

    // ********************************************************************
    // Function:    onkeyup()
    // Purpose:     Listens for key presses and passes them to the level 
    //              object. 
    // ********************************************************************
    document.onkeyup = function(e) {
		if (game_user_control) {
			if (e.keyCode == LEFT) {
				game_keypress.left = false;
				game_line.direction = 0;
			}
			if (e.keyCode == RIGHT) {
				game_keypress.right = false;
				game_line.direction = 0;
			}
			if (e.keyCode == UP) {
				game_keypress.up = false;
				game_line.change_rate +=1;
				if (game_line.change_rate >3) game_line.change_rate = 3;
			}
			if (e.keyCode == DOWN) {
				game_keypress.down = false;
				game_line.change_rate -=1;
				if (game_line.change_rate <1) game_line.change_rate = 1;
			}
			if (e.keyCode == NUM1) {
				game_keypress.num1 = false;
				game_line.change_rate =1;
			}
			if (e.keyCode == NUM2) {
				game_keypress.num2 = false;
				game_line.change_rate =2;
			}
			if (e.keyCode == NUM3) {
				game_keypress.num3 = false;
				game_line.change_rate =3;
			}
		}
    }

    // ********************************************************************
    // Function:    gameLoop()
    // Purpose:     Continuous loop runs while the game is loaded. 
    // ********************************************************************
    this.gameLoop = function() {
        game_logic();     // Run all logic functions
        game_draw();      // Draw all objects and text
    } 
	
    // ********************************************************************
    // Function:    logic()
    // Purpose:     Handle all game logic. 
    // ********************************************************************
    game_logic = function() {
	
		// If there's no user control, get track control
		if (!game_user_control) game_track.logic(game_line);
	
		// Perform Line Logic
		game_line.logic();
		
		// Perform Car Logic
		game_car.logic(game_line, controller);
		
		// Record results
		game_results.record(game_line, game_car);
		
		// Update timer
		game_now = new Date();
		game_current_time = game_now.getTime();
		
		// Stop game if done
		if (game_current_time-game_start_time > RUNTIME*1000) {
			stopGame();
		}
		
    } 
    
    // ********************************************************************
    // Function:    clear()
    // Purpose:     Sets up the canvas for each frame. 
    // ********************************************************************
    game_clear = function() {
        ctx.fillStyle = 'rgba(150, 150, 150, 255)';
        ctx.beginPath();                // Start drawing
        ctx.rect(0,0,                   // Draws rectangle
            CANVAS_WIDTH,
            CANVAS_HEIGHT);        
        ctx.closePath();                // Ends drawing
        ctx.fill();                     // Fills rectangle w/ active color
    }
	
    // ********************************************************************
    // Function:    draw()
    // Purpose:     Draws all game objects and text to the canvas. 
    // ********************************************************************
    game_draw = function() {
        // Clear the canvas to the level's bg color
        game_clear();
		game_line.draw(0);
		game_car.draw(0);
		game_readout.draw(game_car,game_line);
    }  
	
}

// ********************************************************************
// Function:    startGame()
// Purpose:     Runs the game loop FPS times per second. 
// ********************************************************************
function startGame() {
	stopGame();							// Stop any running version
	
	// zero everything
	game_car.reset();
	game_line.reset();
	game_track.reset();
	game_results.reset();
    game_now = new Date();
    game_start_time = game_now.getTime();
	
	// Start game interval
	game_stop = false;
	game_interval_ID = setInterval(this_game.gameLoop, 1000 / FPS);
}

// ********************************************************************
// Function:    stopGame()
// Purpose:     Stops the game 
// ********************************************************************
function stopGame() {
	game_stop = true;
	if (game_interval_ID) clearInterval(game_interval_ID);
	
	// Process results
	game_results.process(game_current_time - game_start_time);
	game_results.draw();
	
	// Clear canvas
	window.setTimeout(game_clear(),1000);
}


// ********************************************************************
// Function:    initialiseGame()
// Purpose:     Creates a game instance and initialises game
// ********************************************************************
function initialiseGame() {
	canvas_game = document.getElementById('canvas_game'),   // The canvas itself
	ctx = canvas_game.getContext('2d'),           			// 2d graphics context
		
	// Set canvas size    
	canvas_game.width = CANVAS_WIDTH;
	canvas_game.height = CANVAS_HEIGHT;
	
	this_game = new Game();     // Create instance of the game
}
