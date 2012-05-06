//*************************************************************************************************************
//*  File Name:  	Matcher.java
//*  Author:		Sarah Herzog
//*  Purpose:  		Method for matching people to tents.
//*************************************************************************************************************
import java.io.*;
import java.util.*;

public class Matcher {
	
	//*********************************************************************************************************
	//* Data Members
	//*********************************************************************************************************
	static Tent [] tents;				// The working tents which will be filled with people
	static int score;					// current score
	static int num_placed;				// Number of people currently placed
	static Tent [] solution;			// The best solution found so far
	static int solution_score = 0;
	static Person [] people;
	static int debug_val = 1;
	static int best_potential_solution = 0;

    //*********************************************************************************************************
    //* Name:     	main
    //* Purpose:  	Wrapper for program
	//* Arguments:	String[] args: command line arguments
	//* Returns:	---
    //*********************************************************************************************************
	public static void main(String [] args)
	{
		// Load in tents
		tents = new Tent[5];
		tents[0] = new Tent(4);
		tents[1] = new Tent(4);
		tents[2] = new Tent(3);
		tents[3] = new Tent(3);
		tents[4] = new Tent(2);
		solution = new Tent[5];
		solution[0] = new Tent(4);
		solution[1] = new Tent(4);
		solution[2] = new Tent(3);
		solution[3] = new Tent(3);
		solution[4] = new Tent(2);
		
		// Load in instance (votes) from file
		loadPeople();
		
		// Sort people based on number of possible friends (highest to lowest), then based on max points (highest to lowest)
		// Tents are sorted from largest to smallest.
		// Goal is to place people with the most potential points and the most friends in the large tents first. 
		// The people with small potential and/or few friends will be placed in the small tents first.
		sortPeople();
		
		// Calculate best possible solution (everyone gets first choices)
		for (Person person : people) {
			best_potential_solution = best_potential_solution + person.potential;
		}
		debug("Best potential solution: " + best_potential_solution);
		
		// Search for matches
		match();
		
		// Display results
		System.out.println("SOLUTION:");
		System.out.println("Score: " + solution_score);
		for (Tent tent : solution) {
			System.out.println("---\n" + tent);
		}
		
	}

    //*********************************************************************************************************
    //* Name:     	match
	//* Purpose:  	places a person into a tent
	//* Arguments:	---
	//* Returns:	int: score gained from this match
    //*********************************************************************************************************
	static public int match() {
		
		int i = 0;
		while (!tents[i].hasRoom()) { // get to the next tent with room in it.
			++i;
		}
		
		// Place each person in the loop (next first method)
		for (Person person : people) {	// Try best first instead?
			if (!person.placed) {  
				// DO
				score += tents[i].place(person);
				++num_placed;
				
				// If we aren't at the end, keep going (maybe!)
				if (num_placed < people.length) {
					if (score + get_h() < solution_score) { // If we can't possibly beat the solution score, then undo and prune.
						// UNDO
						score += tents[i].remove(person);
						--num_placed;
						return score;
					}
					else {
						match();
					}
				}
				
				// If we are at the end, check if this is the best solution so far
				else {
					if (score > solution_score) { // If it is, copy it into solution
						for (int j = 0; j < tents.length; ++j ) {
							solution[j] = tents[j].copy();
						}
						solution_score = score;
						debug("New Solution! Score: " + score);
					}
				}
				

				// UNDO
				score += tents[i].remove(person);
				--num_placed;
			}
		}
		
		return score;
		
	}

    //*********************************************************************************************************
    //* Name:     	get_h()
	//* Purpose:  	Finds the best possible remaining score.
	//* Arguments:	---
	//* Returns:	int: Best possible score from remaining unplaced people.
    //*********************************************************************************************************
	static public int get_h() { 
		int h = 0;
		
		for (Person person : people) {
			if (!person.placed) {  
				int temp_potential = person.potential;
				
				// loop through tents. Remove any potential friends in tents that are full.
				for (Tent tent : tents) {
					if (!tent.hasRoom()) { // Add potential from people who haven't been placed yet
						for (Person friend : tent.people) {
							temp_potential -= person.getScore(friend.name);
						}
					}
					else { // add potential for people who are in tents that aren't full
						for (Person occupant : tent.people) {
							if (occupant != null) {
								temp_potential += occupant.getScore(person.name);
							}
						}
					}
				}
				h += temp_potential;
			}
		}
		
		return h;
	}

    //*********************************************************************************************************
    //* Name:     	debug
	//* Purpose:  	Prints a debug statement
	//* Arguments:	String statement - statement to be printed
	//*				int level (optional) - level of debugging
	//* Returns:	---
    //*********************************************************************************************************
	static public void debug(String statement) {
		debug(statement, 1); // defaults to level 1 debugging (always shown if debugging is on)
	}
	static public void debug(String statement, int level) {
		if (debug_val >= level) System.out.println(statement);
	}

    //*********************************************************************************************************
    //* Name:     	loadPeople
	//* Purpose:  	Loads in people into an array from file
	//* Arguments:	---
	//* Returns:	---
    //*********************************************************************************************************
	static public void loadPeople() {
		
		// Open the file
		Scanner src;
		try {
			src = new Scanner(new FileReader("instance.txt"));
		} catch(FileNotFoundException e) {
			System.out.println("Cannot open instance.txt");
			return;
		}

		List<Person> people_list = new ArrayList<Person>();
		Person person = null;
		String name = null;
		List<String> friends = new ArrayList<String>();
		List<String> scores = new ArrayList<String>();
		String line;
		String [] words;
		
		while(src.hasNextLine()) {
			
			// Read in a line
			line = src.nextLine();
			words = line.split("\\s+");
			debug(words[0]); debug(words[1]); debug(words[2]);
			
			// If it's a new name, add the current person to the array and start a new one.
			if (words[2].equals("0")) // If the friend has a score of zero, throw out.
				continue;
			if (name == null)
				name = words[0];
			if (!words[0].equals(name)){
				int[] score_array = new int[scores.size()];
				int i = 0;
				for (String score : scores) {
					score_array[i] = Integer.parseInt(score);
					++ i;
				}
				String[] friend_array = friends.toArray(new String[friends.size()]);
				person = new Person(name, friend_array, score_array);
				people_list.add(person);
				name = words[0];
				friends = new ArrayList<String>();
				scores = new ArrayList<String>();
			}
			
			// Add friend and score for this line to the current list
			friends.add(words[1]);
			scores.add(words[2]);
			
		}
		
		// We still have the last person to store.
		int[] score_array = new int[scores.size()];
		int i = 0;
		for (String score : scores) {
			score_array[i] = Integer.parseInt(score);
			++ i;
		}
		String[] friend_array = friends.toArray(new String[friends.size()]);
		person = new Person(name, friend_array, score_array);
		people_list.add(person);
		
		// Close out the file
		src.close();
		
		// Convert list of people to array of people
		people = people_list.toArray(new Person[people_list.size()]);

		// Print the results if debug is on
		debug("Instance: ");
		for (Person personi: people) {
			debug(personi.toString());
		}
	}


    //*********************************************************************************************************
    //* Name:     	sortPeople
	//* Purpose:  	Sorts instance from least friends to most friends, from best value to least value.
	//* Arguments:	---
	//* Returns:	---
    //*********************************************************************************************************
	static public void sortPeople() {
		
		// Sort people based on total potential score
		Arrays.sort(people, new PersonSortByPotential());

		// Sort people based on number friends
		Arrays.sort(people, new PersonSortByNumFriends());
		
		// Debug print sorted instance
		debug("Sorted Instance: ");
		for (Person person: people) {
			debug(person.toString()+"\n---");
		}
		
		
	}
	
}
