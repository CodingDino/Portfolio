//*************************************************************************************************************
//*  File Name:  	Tent.java
//*  Author:		Sarah Herzog
//*  Purpose:  		Members and happiness total for a tent.
//*************************************************************************************************************

public class Tent {
	
	//*********************************************************************************************************
	//* Data Members
	//*********************************************************************************************************
	int size;				// Number of people the tent can sleep
	int occupants;			// Number of people currently in the tent
	Person [] people;		// People assigned to the tent
	int score;				// Score based on people assigned
	
    //*********************************************************************************************************
    //* Name:     	Constructor
    //* Purpose:  	Initializes data members to provided values
	//* Arguments:	int size: Number of people that will fit in this tent
	//* Returns:	---
    //*********************************************************************************************************
	public Tent (int size) {
		this.size = size;
		this.occupants = 0;
		people = new Person [size];
		score = 0;
	}
	
    //*********************************************************************************************************
    //* Name:     	hasRoom
    //* Purpose:  	Checks if the tent has any room.
	//* Arguments:	---
	//* Returns:	boolean: true if there is room, else false.
    //*********************************************************************************************************	
	public boolean hasRoom() {
		if (occupants < size) return true;
		return false;
	}
	
    //*********************************************************************************************************
    //* Name:     	place
    //* Purpose:  	Places a person into the tent if there is room.
	//* Arguments:	Person person: Person who will be placed in the tent
	//* Returns:	int: -1 if there is not room, else the score increase from the person who was placed.
    //*********************************************************************************************************	
	public int place (Person person) {
		
		if (occupants == size)
			return -1;
		
		if (person.placed)
			return -1;
		
		int new_score = score;
		for (int i = 0; i < people.length; ++i) {
			if (people[i] != null) {
				new_score += people[i].getScore(person.name);
				new_score += person.getScore(people[i].name);
			}
			else {
				if (!person.placed) {
					people[i] = person;
					person.placed = true;
					++occupants;
					//Matcher.debug("Placed: " + person.name);
				}
			}
		}
		
		int diff = new_score - score;
		score = new_score;
		//Matcher.debug("Diff: " + diff);
		//Matcher.debug("New Score: " + new_score);
		return diff;
	}
	
    //*********************************************************************************************************
    //* Name:     	remove
    //* Purpose:  	Removes a person from the tent.
	//* Arguments:	Person person: Person who will be placed in the tent
	//* Returns:	int: score difference from removing the person - if the person was not present, returns 1.
    //*********************************************************************************************************	
	public int remove (Person person) {
		
		boolean found = false;
		for (int i = 0; i < people.length; ++i) {
			if (people[i] == person) {
				found = true;
				people[i] = null;
				person.placed = false;
				occupants--;
			}
		}
		if (!found) return 1;
		
		int new_score = score;
		for (Person occupant : people) {
			if (occupant != null) {
				new_score -= occupant.getScore(person.name);
				new_score -= person.getScore(occupant.name);
			}
		}
		
		int diff = new_score - score;
		score = new_score;
		return diff;
	}

    //*********************************************************************************************************
    //* Name:     	copy()
    //* Purpose:  	Returns a pointer to a new tent object
	//* Arguments:	---
	//* Returns:	Tent: New tent object copied from this one
    //*********************************************************************************************************
	public Tent copy() {
		Tent copy = new Tent(size);
		copy.people = new Person [size];
		
		for (int i=0 ; i < people.length; ++i) {
			copy.people[i] = people[i];
		}
		copy.occupants = occupants;
		copy.score = score;
		return copy;
	}
	

    //*********************************************************************************************************
    //* Name:     	toString
    //* Purpose:  	Returns this Person's values as a string
	//* Arguments:	---
	//* Returns:	String: This Person's data.
    //*********************************************************************************************************	
	public String toString() {
		String return_string = "Tent size: " + size + "\nPeople:";
		for (int i = 0; i < people.length; ++i) {
			return_string = return_string + "  " + people[i].name + " (" + people[i].potential + ")";
		}
		return_string = return_string + "\nScore: " + score;
		return return_string;
	}

}
