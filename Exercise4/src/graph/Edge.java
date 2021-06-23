package graph;

/**
 * This class allows to format and edge between 2 nodes in a
 * easier way for the Kruscal algorithm
 * @author lucamodica, lorenzopallanza
 */
public class Edge<V,E> {

  private V src;
  private V dest;
  private E label;
  private boolean directed;

  /**
   * Tne complete constructor for Edge
   * @param src source
   * @param dest destination
   * @param label edge label
   * @param direction mark ad a directed graph (true) or not (false)
   */
  public Edge(V src, V dest, E label, boolean direction){
    this.src = src;
    this.dest = dest;
    this.label = label;
    this.directed = direction;
  }

  /* Cosntructor version without the label, used for
  deletion operations */ 
  public Edge(V src, V dest, boolean direction) {
    this.src = src;
    this.dest = dest;
    this.directed = direction;
  }


  /* Getter/Setter for source */ 
  public V getSrc() {
    return src;
  }
  public void setSrc(V src) {
    this.src = src;
  }

  /* Getter/Setter for destination */ 
  public V getDest() {
    return dest;
  }
  public void setDest(V dest) {
    this.dest = dest;
  }

  /* Getter/Setter for label */ 
  public E getLabel() {
    return label;
  }
  public void setLabel(E label) {
    this.label = label;
  }

  /* Check if an edge is directed or not */ 
  public boolean isDirected() {
    return directed;
  }

  /**
   * Returns a hash code value for the object.
   * Depending on if the edge is directed or not,
   * if is true it will be calcolated a different
   * hashCode between this edge and the return one,
   * the same hashCode otherwise
   */
  @Override
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    
    if (directed) {
      result = prime * result + ((dest == null) ? 0 : dest.hashCode());
      result = prime * result + ((src == null) ? 0 : src.hashCode());
    }
    else{
      result = prime * result + (((dest == null) ? 0 : dest.hashCode()) + ((src == null) ? 0 : src.hashCode()));
    }

    return result;
  }
  

  /**
   * Indicates whether some other object is "equal to" this one.
   * This comparison is only based on the source and the destination
   * and does not change if this 2 element is swapped and the edge is
   * not directed
   */
  @Override
  @SuppressWarnings("unchecked")
  public boolean equals(Object o) {
    if ((o == null) || !(o instanceof Edge)){
      return false;
    }
    Edge<V,E> edge = (Edge<V,E>) o;

    return this.src.equals(edge.src) && 
      this.dest.equals(edge.dest) || 
      (!directed && this.src.equals(edge.dest) && this.dest.equals(edge.src));
  }

  @Override
  public String toString() {
    return "Edge [dest=" + dest + ", label=" + label + ", src=" + src + "]";
  }
}
