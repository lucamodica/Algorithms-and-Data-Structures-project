package graph;

/**
 * Class for the generic Vertex in graph adjacent lists, 
 * that incapsulates the vertex element data and the label 
 * related to the edge
 * @author lucamodica, lorenzopallanza
 */
class Node<V, E> {

  private V elem;
  private E label;

  /**
   * The complete Node constructor
   * @param elem the vertex element
   * @param label the associated label
   */
  public Node(V elem, E label) {
    this.elem = elem;
    this.label = label;
  }

  /**
   * The Node constructor for comparison
   * and deletion
   * @param elem the vertex element
   */
  public Node(V elem) {
    this.elem = elem;
  }
  
  /* Getters for the attributes */ 
  public V getElem() {
    return elem;
  }
  public E getLabel() {
    return label;
  }

  /* Setters for the attributes */ 
  public void setElem(V elem) {
    this.elem = elem;
  }
  public void setLabel(E label) {
    this.label = label;
  }

  @Override
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    result = prime * result + ((elem == null) ? 0 : elem.hashCode());
    return result;
  }

  @Override
  @SuppressWarnings("unchecked")
  public boolean equals(Object o) {
    if ((o == null) || !(o instanceof Node<?,?>)){
      return false;
    }
    Node<V,E> node = (Node<V,E>) o;
    return this.elem.equals(node.elem);
  }

  @Override
  public String toString() {
    return "Node [elem=" + elem + ", label=" + label + "]";
  }
}
