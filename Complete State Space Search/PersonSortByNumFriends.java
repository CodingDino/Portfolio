import java.util.Comparator;

public class PersonSortByNumFriends implements Comparator<Person>{

    public int compare(Person a, Person b) {
		return Math.min(4,b.friends.length) - Math.min(4,a.friends.length);
    }
    
}
