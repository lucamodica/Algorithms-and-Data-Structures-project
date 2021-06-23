package graph;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;

import java.util.ArrayList;
import java.util.Set;
import java.util.HashSet;

import org.junit.Before;
import org.junit.Test;

import unionfindset.UnionFindSetException;

/**
 * The suit tests for the Graph and the
 * MstKruscal class
 * @author lucamodica, lorenzopallanza
 */
public class GraphTests {

  /* Custom test class */ 
  static class Person {
    private String firstName; /* First name of the person */ 
    private String lastName;  /* Last name of the person */ 

    /* Constructor */ 
    public Person(String firstName, String lastName){
      this.firstName = firstName;
      this.lastName = lastName;
    }

    /* Get-methods for Person attributes */ 
    public String getFirstName(){
      return this.firstName;
    }
    public String getLastName(){
      return this.lastName;
    }

    /* Returns a textual rappresentation for the object */ 
    @Override
    public String toString(){
        return "<" + this.firstName + "," + this.lastName + ">";
    }

    /* Compares the object with another "o" object */ 
    @Override
    public boolean equals(Object o) {
        if ((o == null) || !(o instanceof Person)) return false;
        Person p = (Person) o;
        return (this.firstName.equals(p.firstName)) && 
        (this.lastName.equals(p.lastName));
    }
  }

  /* Graph to be tested */ 
  private Graph<Integer, Integer> gInt;
  private Graph<String, Double> gString;
  private Graph<Double, String> gDouble;
  private Graph<Person, Integer> gPerson;

  /* ArrayList that contain data to fill the graphs */ 
  private ArrayList<Integer> intData;
  private ArrayList<String> stringData;
  private ArrayList<Double> doubleData;
  private ArrayList<Person> personData;

  /* Init the Integer data */ 
  private void initInt() throws GraphException{
    intData = new ArrayList<Integer>();
    gInt = new Graph<Integer,Integer>(false);

    for(int i = 0; i < 100; i++) { 
      intData.add(i);
    }
  }
  
  /* Init the String data */
  private void initString() throws GraphException{
    stringData = new ArrayList<String>();
    gString = new Graph<String, Double>(true);

    stringData.add("Idilio");
    stringData.add("Giovanni");
    stringData.add("Giorgio");
    stringData.add("Mr.");
    stringData.add("Crab");
    stringData.add("Idilio");
    stringData.add("Halo");
    stringData.add("Destiny");
    stringData.add("Doom");
  }
  
  /* Init the Double data */
  private void initDouble() throws GraphException{
    doubleData = new ArrayList<Double>();
    gDouble = new Graph<Double, String>(false);

    for(int i = 0; i < 100; i++) {
      double d = 100/(i+1);
      doubleData.add(d);
    }
  }

  /* Init the Person class data */
  private void initPerson() throws GraphException{
    personData = new ArrayList<Person>();
    gPerson = new Graph<Person, Integer>(true);

    personData.add(new Person("Idilio", "Drago"));
    personData.add(new Person("Giovanni", "Giorgio"));
    personData.add(new Person("Gianluca", "Pozzato"));
    personData.add(new Person("Luca", "Modica"));
    personData.add(new Person("Lorenzo", "Pallanza"));
    personData.add(new Person("Diego", "Magro"));
    personData.add(new Person("Ugo", "De Liguoro"));
    personData.add(new Person("Gaetano", "Pensa"));
    personData.add(new Person("Fabiana", "Vernero"));
    personData.add(new Person("Ciro", "Cattuto"));
  }

  /* Generates an edge set for further test */ 
  private HashSet<Edge<Integer,Integer>> tEdgesSet(){
    HashSet<Edge<Integer,Integer>> t = new HashSet<Edge<Integer,Integer>>();
    t.add(new Edge<Integer,Integer>(1, 2, 3, false));
    t.add(new Edge<Integer,Integer>(2, 3, 4, false));
    t.add(new Edge<Integer,Integer>(3, 4, 5, false));
    t.add(new Edge<Integer,Integer>(4, 1, 8, false));
    t.add(new Edge<Integer,Integer>(5, 2, 9, false));

    return t;
  }


  /**
   * Init tests function, that initialize all the 
   * necessary data structures 
   * @throws GraphException to handle Graph class exceptions
   */
  @Before
  public void createGraph() throws GraphException{
    initInt();
    initString();
    initDouble();
    initPerson();
  }

  /* Testing for with empty graphs */ 
  @Test
  public void testEmptyGraph() throws Exception{
    assertEquals(0, gInt.getVerticesCount());
    assertEquals(0, gDouble.getVerticesCount());
    assertEquals(0, gString.getVerticesCount());
    assertEquals(0, gPerson.getVerticesCount());

    assertEquals(0, gInt.getEdgesCount());
    assertEquals(0, gDouble.getEdgesCount());
    assertEquals(0, gString.getEdgesCount());
    assertEquals(0, gPerson.getEdgesCount());
  }

  /* Checking the graphs direction criteria */ 
  @Test
  public void testCheckDirected() throws Exception{
    assertFalse(gInt.isDirected());
    assertTrue(gString.isDirected());
    assertFalse(gDouble.isDirected());
    assertTrue(gPerson.isDirected());
  }

  /* Testing for the graphs with one edge */ 
  @Test 
  public void testOneEdge() throws Exception{
    gInt.addEdge(intData.get(0), intData.get(1), intData.get(2));

    assertTrue(gInt.hasVertex(intData.get(0)));
    assertTrue(gInt.hasVertex(intData.get(1)));

    assertTrue(gInt.hasEdge(intData.get(0), intData.get(1)));
    assertTrue(gInt.hasEdge(intData.get(1), intData.get(0)));

    assertEquals(2, gInt.getVerticesCount());
    assertEquals(1, gInt.getEdgesCount());

    assertEquals(intData.get(2), gInt.getEdgeLabel(intData.get(0), intData.get(1)));



    gString.addEdge(stringData.get(0), stringData.get(1), doubleData.get(2));

    assertTrue(gString.hasVertex(stringData.get(0)));
    assertTrue(gString.hasVertex(stringData.get(1)));

    assertTrue(gString.hasEdge(stringData.get(0), stringData.get(1)));
    assertFalse(gString.hasEdge(stringData.get(1), stringData.get(0)));

    assertEquals(2, gString.getVerticesCount());
    assertEquals(1, gString.getEdgesCount());

    assertEquals(doubleData.get(2), gString.getEdgeLabel(stringData.get(0), stringData.get(1)));



    gDouble.addEdge(doubleData.get(0), doubleData.get(1), stringData.get(2));

    assertTrue(gDouble.hasVertex(doubleData.get(0)));
    assertTrue(gDouble.hasVertex(doubleData.get(1)));

    assertTrue(gDouble.hasEdge(doubleData.get(0), doubleData.get(1)));
    assertTrue(gDouble.hasEdge(doubleData.get(1), doubleData.get(0)));

    assertEquals(2, gDouble.getVerticesCount());
    assertEquals(1, gDouble.getEdgesCount());

    assertEquals(stringData.get(2), gDouble.getEdgeLabel(doubleData.get(0), doubleData.get(1)));


    
    gPerson.addEdge(personData.get(0), personData.get(1), intData.get(2));

    assertTrue(gPerson.hasVertex(personData.get(0)));
    assertTrue(gPerson.hasVertex(personData.get(1)));

    assertTrue(gPerson.hasEdge(personData.get(0), personData.get(1)));
    assertFalse(gPerson.hasEdge(personData.get(1), personData.get(0)));

    assertEquals(2, gPerson.getVerticesCount());
    assertEquals(1, gPerson.getEdgesCount());

    assertEquals(intData.get(2), gPerson.getEdgeLabel(personData.get(0), personData.get(1)));
  }

  /* Testing for a generic gaph */ 
  @Test
  public void testGenericGraph() throws Exception{
    gInt.addEdge(intData.get(0), intData.get(1), intData.get(2));
    gInt.addEdge(intData.get(2), intData.get(1), intData.get(3));
    gInt.addEdge(intData.get(2), intData.get(3), intData.get(4));
    gInt.addEdge(intData.get(4), intData.get(3), intData.get(5));
    gInt.addEdge(intData.get(4), intData.get(5), intData.get(6));
    gInt.addEdge(intData.get(5), intData.get(0), intData.get(7));
    gInt.addEdge(intData.get(1), intData.get(4), intData.get(8));
    gInt.addEdge(intData.get(2), intData.get(5), intData.get(9));
    gInt.addEdge(intData.get(0), intData.get(3), intData.get(10));

    /* hasVertex() and hasEdge() test */ 
    assertFalse(gInt.hasVertex(intData.get(11)));
    assertTrue(gInt.hasEdge(intData.get(0), intData.get(1)));
    assertTrue(gInt.hasEdge(intData.get(5), intData.get(2)));
    assertFalse(gInt.hasEdge(intData.get(3), intData.get(1)));

    /* Counting functions test */ 
    assertEquals(6, gInt.getVerticesCount());
    assertEquals(9, gInt.getEdgesCount());

    /* getEdgeLabel() test */ 
    assertEquals(intData.get(7), gInt.getEdgeLabel(intData.get(0), intData.get(5)));
    assertEquals(intData.get(10), gInt.getEdgeLabel(intData.get(3), intData.get(0)));

    /* deleteVertex() test */ 
    gInt.deleteVertex(intData.get(0));
    assertEquals(5, gInt.getVerticesCount());
    assertEquals(6, gInt.getEdgesCount());

    /* deleteEdge() test */ 
    gInt.deleteEdge(intData.get(5), intData.get(4));
    assertFalse(gInt.hasEdge(intData.get(4), intData.get(5)));
    assertEquals(5, gInt.getVerticesCount());
    assertEquals(5, gInt.getEdgesCount());

    /* getVertices() test */ 
    assertEquals(new HashSet<Integer>(intData.subList(1, 6)), new HashSet<>(gInt.getVertices()));

    /* getEdges() test */ 
    assertEquals(tEdgesSet(), new HashSet<Edge<Integer,Integer>>(gInt.getEdges()));

    /* getAdjacentVerteces() test */ 
    Set<Node<Integer,Integer>> expAdjacentSet = new HashSet<Node<Integer,Integer>>();
    expAdjacentSet.add(new Node<Integer,Integer>(1,3));
    expAdjacentSet.add(new Node<Integer,Integer>(5,9));
    expAdjacentSet.add(new Node<Integer,Integer>(3,4));
    assertEquals(expAdjacentSet, new HashSet<>(gInt.getAdjacentVerteces(intData.get(2))));
  }

  /* Test for the MstKruscal class */ 
  @Test
  public void testMstKruscal() throws UnionFindSetException, Exception{
    Graph<Integer,Double> g = new Graph<Integer,Double>(false);
    g.addEdge(intData.get(5), intData.get(0), (double) intData.get(7));
    g.addEdge(intData.get(0), intData.get(1), (double) intData.get(2));
    g.addEdge(intData.get(2), intData.get(1), (double) intData.get(3));
    g.addEdge(intData.get(2), intData.get(5), (double) intData.get(9));
    g.addEdge(intData.get(2), intData.get(3), (double) intData.get(4));
    g.addEdge(intData.get(4), intData.get(3), (double) intData.get(5));
    g.addEdge(intData.get(0), intData.get(3), (double) intData.get(10));
    g.addEdge(intData.get(4), intData.get(5), (double) intData.get(6));
    g.addEdge(intData.get(1), intData.get(4), (double) intData.get(8));

    MstKruscal<Integer> mst = new MstKruscal<Integer>(g);
    assertEquals(6, mst.getVerticesCount());
    assertEquals(5, mst.getEdgesCount());
    assertEquals(20, mst.getWeight(),0);
  }
}
