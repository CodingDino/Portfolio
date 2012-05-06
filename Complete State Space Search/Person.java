//*************************************************************************************************************
//*  File Name:     Person.java
//*  Author:        Sarah Herzog
//*  Purpose:       A person has friends with scores. Also methods for comparing people.
//*************************************************************************************************************

public class Person {
    
    //*********************************************************************************************************
    //* Data Members
    //*********************************************************************************************************
    String name;                // Identity of this Person
    String [] friends;          // Identity of friends
    int [] scores;              // Score of friends
    int potential = 0;
    boolean placed = false;
    
    //*********************************************************************************************************
    //* Name:           Constructor
    //* Purpose:        Initializes data members to provided values
    //* Arguments:      String name: Identity of this Person
    //*                 String [] friends: Identity of friends
    //*                 String [] scores: Score of friends
    //* Returns:        ---
    //*********************************************************************************************************
    public Person (String name, String [] friends, int [] scores) {
        this.name = name;
        this.friends = friends;
        this.scores = scores;

        int num_good = 0;
        int min_good = Integer.MAX_VALUE;
        for (int score : scores) {
            potential += score;
            min_good = Math.min(score,min_good);
            ++num_good; /*
            if (num_good > 4) { // We need to adjust potential if there are more friends than possible tent-mates (4)
                if (score > min_good) { // score will be the new min_good, old min_good is discarded
                    potential -= min_good;
                    min_good = score;
                }
                else { // score is the lowest overall, so it is discarded
                    potential -= score;
                }
            } */
        }
        
    }

    //*********************************************************************************************************
    //* Name:       getScore
    //* Purpose:    Checks the person's friends to see if the requested name is listed, and if so, returns 
    //*             their score.
    //* Arguments:  String other_name: Identity of Person to check
    //* Returns:    int: the score corresponding to the passed in name
    //*********************************************************************************************************    
    public int getScore (String other_name) {
        
        // Loop through list of friends
        for (int i = 0; i < friends.length; ++i) {
            // If the name was found, return the associated score
            if (other_name.equals(friends[i]))
                return scores[i];
        }
        
        // Otherwise return a score of 0
        return 0;
    }

    //*********************************************************************************************************
    //* Name:       toString
    //* Purpose:    Returns this Person's values as a string
    //* Arguments:  ---
    //* Returns:    String: This Person's data.
    //*********************************************************************************************************    
    public String toString() {
        String return_string = "Name: " + name + "\nFriends:";
        for (int i = 0; i < friends.length; ++i) {
            return_string = return_string + " " + friends[i] + " (" + scores[i] + ")";
        }
        return_string = return_string + "\nPotential: " + potential;
        return return_string;
    }

}
