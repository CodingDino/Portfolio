import java.util.Comparator;

public class PersonSortByPotential implements Comparator<Person>{

    public int compare(Person a, Person b) {
        return  b.potential - a.potential;
    }
    
}