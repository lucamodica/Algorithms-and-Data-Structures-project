package unionfindset;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

import java.util.ArrayList;

import org.junit.Before;
import org.junit.Test;

/**
 * The suit tests for the UnionFindSet class
 * @author lucamodica, lorenzopallanza
 */
public class UnionFindSetTests {

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

  /**
   * The following functions are meant to initialize all the variables 
   * that the tests are going to use soon after.
   * 
   * In order, we initialize three variables for each of 
   * this data types: Integer, String, Double and Person.
   * 
   * Finally, we create an empty UnionFindSet for each data type.
   */

  private Integer i1, i2, i3;
  private ArrayList<Integer> intData;
  private String s1, s2, s3;
  private Double d1, d2, d3;
  private Person p1, p2, p3;
  private UnionFindSet<Integer> setInt;
  private UnionFindSet<String> setString;
  private UnionFindSet<Double> setDouble;
  private UnionFindSet<Person> setPerson;
  
  
  private void initInt() throws UnionFindSetException{
    i1 = 0;
    i2 = 1;
    i3 = 3;
    intData = new ArrayList<>();
    intData.add(i1);
    intData.add(i2);
    intData.add(i3);
    setInt = new UnionFindSet<Integer>(intData);
  }

  private void initString(){
    s1 = "Halo";
    s2 = "Destiny";
    s3 = "Doom";
    setString = new UnionFindSet<String>();
    
  }

  private void initDouble(){
    d1 = 42.117;
    d2 = 777.0470;
    d3 = 666.42069;
    setDouble = new UnionFindSet<Double>();
  }

  private void initPerson(){
    p1 = new Person("Idilio", "Drago");
    p2 = new Person("Giovanni", "Giorgio");
    p3 = new Person("Mr.", "Crab");
    setPerson = new UnionFindSet<Person>();
  }

  
  /**
   * Calls the initialization functions for the following data types:
   * Integer, String, Double and Person.
   * @throws UnionFindSetException
   */
  @Before
  public void createUnionFindSet() throws UnionFindSetException{
    initInt();
    initString();
    initDouble();
    initPerson();
  }

  /** 
   * Testing if all disjointed sets are disjointed
   * by looking at and comparing each rapresentative.
   * The test is the same for every data type.
   */
  @Test
  public void testIsAll_Disjointed() throws Exception{
    /* Test for Integer type */
    assertNotEquals(setInt.findSet(i1),setInt.findSet(i2));
    assertNotEquals(setInt.findSet(i1),setInt.findSet(i3));
    assertNotEquals(setInt.findSet(i2),setInt.findSet(i3));

    /* Test for String type */ 
    setString.makeSet(s1);
    setString.makeSet(s2);
    setString.makeSet(s3);
    assertNotEquals(setString.findSet(s1),setString.findSet(s2));
    assertNotEquals(setString.findSet(s1),setString.findSet(s3));
    assertNotEquals(setString.findSet(s2),setString.findSet(s3));

    /* Test for Double type */ 
    setDouble.makeSet(d1);
    setDouble.makeSet(d2);
    setDouble.makeSet(d3);
    assertNotEquals(setDouble.findSet(d1),setDouble.findSet(d2));
    assertNotEquals(setDouble.findSet(d1),setDouble.findSet(d3));
    assertNotEquals(setDouble.findSet(d2),setDouble.findSet(d3));

    /* Test for Person type */ 
    setPerson.makeSet(p1);
    setPerson.makeSet(p2);
    setPerson.makeSet(p3);
    assertNotEquals(setPerson.findSet(p1),setPerson.findSet(p2));
    assertNotEquals(setPerson.findSet(p1),setPerson.findSet(p3));
    assertNotEquals(setPerson.findSet(p2),setPerson.findSet(p3));
  }

  /**
   * Testing if after calling union() on two disjointed sets,
   * the parent (representative) is the same between the united sets and different between disjointed ones.
   * @throws Exception
   */
  @Test
  public void testRightParent_AfterUnion() throws Exception{

    /* Testing for Integer type */
    setInt.union(i1, i3);
    assertEquals(setInt.findSet(i1),setInt.findSet(i3));
    assertEquals(setInt.findSet(i3),setInt.findSet(i1));
    assertNotEquals(setInt.findSet(i2),setInt.findSet(i3));


    /* Testing for String type */
    setString.makeSet(s1);
    setString.makeSet(s2);
    setString.makeSet(s3);
    setString.union(s1, s3);
    assertEquals(setString.findSet(s1), setString.findSet(s3));
    assertEquals(setString.findSet(s3), setString.findSet(s1));
    assertNotEquals(setString.findSet(s2),setString.findSet(s3));

    /* Testing for Double type */
    setDouble.makeSet(d1);
    setDouble.makeSet(d2);
    setDouble.makeSet(d3);
    setDouble.union(d1, d3);
    assertEquals(setDouble.findSet(d1),setDouble.findSet(d3));
    assertEquals(setDouble.findSet(d3),setDouble.findSet(d1));
    assertNotEquals(setDouble.findSet(d2),setDouble.findSet(d3));

    /* Testing for Person type */
    setPerson.makeSet(p1);
    setPerson.makeSet(p2);
    setPerson.makeSet(p3);
    setPerson.union(p1, p3);
    assertEquals(setPerson.findSet(p1),setPerson.findSet(p3));
    assertEquals(setPerson.findSet(p3),setPerson.findSet(p1));
    assertNotEquals(setPerson.findSet(p2),setPerson.findSet(p3));
    
  }


  /**
   * On three disjointed sets, we test if after uniting two sets, and then unite the last one,
   * each element has the same parent (representavive): making them a single jointed set.
   * @throws Exception
   */
  @Test
  public void testIsAll_Jointed() throws Exception{
    /* Test for Integer type */
    setInt.union(i1, i2);
    setInt.union(i1, i3);
    setInt.union(i2, i3);
    assertEquals(setInt.findSet(i1),setInt.findSet(i2));
    assertEquals(setInt.findSet(i1),setInt.findSet(i3));
    assertEquals(setInt.findSet(i2),setInt.findSet(i3));

    /* Test for String type */ 
    setString.makeSet(s1);
    setString.makeSet(s2);
    setString.makeSet(s3);
    setString.union(s1, s2);
    setString.union(s1, s3);
    setString.union(s2, s3);
    assertEquals(setString.findSet(s1),setString.findSet(s2));
    assertEquals(setString.findSet(s1),setString.findSet(s3));
    assertEquals(setString.findSet(s2),setString.findSet(s3));

    /* Test for Double type */ 
    setDouble.makeSet(d1);
    setDouble.makeSet(d2);
    setDouble.makeSet(d3);
    setDouble.union(d1, d2);
    setDouble.union(d1, d3);
    setDouble.union(d2, d3);
    assertEquals(setDouble.findSet(d1),setDouble.findSet(d2));
    assertEquals(setDouble.findSet(d1),setDouble.findSet(d3));
    assertEquals(setDouble.findSet(d2),setDouble.findSet(d3));

    /* Test for Person type */ 
    setPerson.makeSet(p1);
    setPerson.makeSet(p2);
    setPerson.makeSet(p3);
    setPerson.union(p1, p2);
    setPerson.union(p1, p3);
    setPerson.union(p2, p3);
    assertEquals(setPerson.findSet(p1),setPerson.findSet(p2));
    assertEquals(setPerson.findSet(p1),setPerson.findSet(p3));
    assertEquals(setPerson.findSet(p2),setPerson.findSet(p3));
  }
  

  /**
   * Various tests that aim to check if the sets have the right rank.
   * We use union() on the Integer and the Double sets, expecting an higher 
   * rank compared to the disjointed String and Person sets.
   * @throws Exception
   */
  @Test
  public void testIsRight_Rank() throws Exception{
    /* Test for Integer type using union() */
    setInt.union(i1, i2);
    setInt.union(i1, i3);
    setInt.union(i2, i3);
    assertEquals(1,setInt.getSetRank(i2));

    /* Test for String type */ 
    setString.makeSet(s1);
    setString.makeSet(s2);
    setString.makeSet(s3);
    assertEquals(0,setString.getSetRank(s1));
    assertEquals(0,setString.getSetRank(s2));
    assertEquals(0,setString.getSetRank(s3));

    /* Test for Double type using union() */ 
    setDouble.makeSet(d1);
    setDouble.makeSet(d2);
    setDouble.makeSet(d3);
    setDouble.union(d1, d2);
    setDouble.union(d1, d3);
    setDouble.union(d2, d3);
    assertNotEquals(0,setDouble.getSetRank(d2));

    /* Test for Person type */ 
    setPerson.makeSet(p1);
    setPerson.makeSet(p2);
    setPerson.makeSet(p3);
    assertNotEquals(1,setPerson.getSetRank(p1));
    assertNotEquals(1,setPerson.getSetRank(p2));
    assertNotEquals(1,setPerson.getSetRank(p3));
  }
}
