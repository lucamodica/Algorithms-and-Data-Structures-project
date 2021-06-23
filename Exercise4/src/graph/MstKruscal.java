package graph;


import java.util.ArrayList;
import java.util.LinkedList;

import unionfindset.UnionFindSet;
import unionfindset.UnionFindSetException;

/**
 * This class implements the Kruscal algorithm and 
 * handles the necessary data for the generated
 * mst, based on the graph passed in the constructor
 * @author lucamodica, lorenzopallanza
 */
public class MstKruscal<V> {

  private Double weight; /* Total weight (must be double) */ 
  private int vertices; /* Number of vertices */ 
  /* The mst itsself, that is an Edge linked list */ 
  private LinkedList<Edge<V,Double>> mst; 

  /**
   * The Mstkruscal constructor
   * @param g the origin graph
   * @throws MstKruscalException if the g parameter is null, or if the parameter graph is directed
   * @throws UnionFindSetException to handle the UnionFindSet class exceptions
   */
  public MstKruscal(Graph<V,Double> g) throws MstKruscalException, UnionFindSetException {
    if (g == null) {
      throw new MstKruscalException("MstKruscal constructor: g parameter cannot be null");
    }
    if (g.isDirected()) {
      throw new MstKruscalException("MstKruscal constructor: the parameter graph cannot be directed");
    }

    weight = (double) 0;
    vertices = g.getVerticesCount();
    mst = this.makeMstKruscal(g);
  }
  
  /* Gets the total weight of the mst */ 
  public Double getWeight() {
    return weight;
  } 
  
  /* Gets the number of vertices of the mst */ 
  public int getVerticesCount() {
    return vertices;
  }
  
  /* Gets the number of edges of the mst */ 
  public int getEdgesCount() {
    return mst.size();
  }

  /* Gets the mst itsself */ 
  public LinkedList<Edge<V,Double>> getMST() {
    return mst;
  }
  
  /**
   * The Kruscal algorithm. Starting from the UnionFind Set with all the graph vertices
   * and the edges list (sorted by weight), the mst will be created
   * @param g the origin graph
   * @return the resulting mst
   * @throws UnionFindSetException to handle the UnionFindSet class exceptions
   */
  private LinkedList<Edge<V,Double>> makeMstKruscal(Graph<V,Double> g) throws UnionFindSetException {
    LinkedList<Edge<V,Double>> mst = new LinkedList<Edge<V,Double>>();
    UnionFindSet<V> sets = new UnionFindSet<V>(g.getVertices());
    ArrayList<Edge<V,Double>> edges = new ArrayList<Edge<V,Double>>(g.getEdges());
    edges.sort(new EdgeComparatorDoubleLabel<V>());

    for (Edge<V,Double> edge : edges) {
      if (sets.findSet(edge.getSrc()) != sets.findSet(edge.getDest())) {
        mst.add(edge);
        weight += edge.getLabel();
        sets.union(edge.getSrc(), edge.getDest());
      }
    }

    return mst;
  }

}
