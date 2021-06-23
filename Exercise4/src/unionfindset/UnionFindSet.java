package unionfindset;

/* This class implements the UnionfindSet data
structure, with compression path and union by rank
for optimizing findset() and union() operations. */ 

import java.util.HashMap;
import java.util.Collection;

public class UnionFindSet<T> {

  /* HashMap to keep track of the parent
  of every element inside the data structure. */ 
  private HashMap<T, T> parent;
  /* HashMap to keep track of the ranks
  of all of the set representative. */ 
  private HashMap<T, Integer> rank;

  /* Class constructor */ 
  public UnionFindSet(){
    parent = new HashMap<T, T>();
    rank = new HashMap<T, Integer>();
  }

  /**
   * Create a UnionFind Set from an initial collection of element 
   * @param c the collection of elements
   * @throws UnionFindSetException if the collection is null
   */
  public UnionFindSet(Collection<T> c) throws UnionFindSetException{
    if(c == null){
      throw new UnionFindSetException("UnionFindSet constructor: c parameter cannot be null");
    }

    parent = new HashMap<T, T>();
    rank = new HashMap<T, Integer>();

    for (T elem : c) {
      makeSet(elem);
    }
  }


  /**
   * Create a new set with the starting element x. To create this,
   * the element will be added to the Parent HashMap with himself
   * as parent, and an initial rank = 0 is setted in the other HashMap rank.
   * @param x The element to be added
   * @throws UnionFindSetException if x parameter is null
   */ 
  public void makeSet(T x) throws UnionFindSetException{
    if(x == null){
      throw new UnionFindSetException("UnionFindSet makeSet: x parameter cannot be null");
    }

    parent.put(x, x);
    rank.put(x, 0);
  }

  /**
   * Given an element x, this function returns the representative of
   * its set. If x is not the parent of itself, the method continues
   * to search with recursion, while it applies the compression path
   * tecnique to reduce the tree height of the set.
   * @param x The input element.
   * @return The element which is the representative of the x's set.
   * @throws UnionFindSetException if x parameter is null
   */
  public T findSet(T x) throws UnionFindSetException{
    if(x == null){
      throw new UnionFindSetException("UnionFindSet findSet: x parameter cannot be null");
    }

    if(! x.equals(parent.get(x))){
      parent.replace(x, findSet(parent.get(x)));
    }
    return parent.get(x);
  }

  /**
   * Returns the rank of the representative element of the
   * x's set.
   * @param x The input element.
   * @return The rank of the set representative.
   * @throws UnionFindSetException if x parameter is null
   */
  public int getSetRank(T x) throws UnionFindSetException{
    if(x == null){
      throw new UnionFindSetException("UnionFindSet getSetRank: x parameter cannot be null");
    }

    return rank.get(findSet(x));
  }

  /**
   * The core part of the union() function, which makes
   * effective the union between the two set (the two paraters 
   * are already two rapresentatives). It works as follows:
   * 
   * <ul>
   * <li> if the rank(x) > rank(y), x will become the new parent
   *    (that is, the new representative) of y </li>
   * <li> if rank(x) <= rank(y), x will become the new parent of 
   *    y; furthermore if the rank of the two elements is equal,
   *    the parent rank will be incremented </li>
   * </ul>
   * 
   * In both cases, the rank of the elements that became child
   * will be removed.
   * @param x The first element.
   * @param y the second element.
   * @throws UnionFindSetException if x or y parameter is null
   */
  private void link(T x, T y) throws UnionFindSetException{
    if(x == null || y == null){
      throw new UnionFindSetException("UnionFindSet link: x and y parameter cannot be null");
    }

    if(rank.get(x) > rank.get(y)){
      parent.replace(y, x);
      rank.remove(y);
    }
    else{
      parent.replace(x, y);
      if(rank.get(x) == rank.get(y)){
        rank.replace(y, rank.get(y) + 1);
      }
      rank.remove(x);
    }
  }

  
  /**
   * If x and y are not part of the same set, this function
   * creates a new set that is the union between the one
   * where there is x and the one where there is y.
   * @param x The first element.
   * @param y the second element.
   * @throws UnionFindSetException if x or y parameter is null
   */
  public void union(T x, T y) throws UnionFindSetException{
    if(x == null || y == null){
      throw new UnionFindSetException("UnionFindSet union: x and y parameter cannot be null");
    }

    T px = findSet(x);
    T py = findSet(y);
    if(!px.equals(py)){
      link(findSet(px), findSet(py));
    }
  }
}
