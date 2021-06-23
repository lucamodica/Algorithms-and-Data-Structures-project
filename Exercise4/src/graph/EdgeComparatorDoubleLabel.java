package graph;

import java.util.Comparator;

/**
 * Comparator class for edges with Double type label
 * used in the Kruscal algorithm to sort the edges
 * @author lucamodica, lorenzopallanza
 */
class EdgeComparatorDoubleLabel<V> implements Comparator<Edge<V,Double>> {

  @Override
  public int compare(Edge<V,Double> e1, Edge<V,Double> e2) {
    int result = Double.compare(e1.getLabel(), e2.getLabel());
    if(result != 0){
      return result;
    }

    return e1.getLabel().compareTo(e2.getLabel());
   }

}