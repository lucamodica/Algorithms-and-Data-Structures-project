
public class Node<T> {
    
  private T elem;
  private Node<T> parent;
  private int rank;

  // Crea un nuovo nodo con valore @elem e successore @next.
  public Node(T elem) {
    this.elem = elem;
    this.parent = this;
    this.rank = 0;
  }

  // Ritorna l'elemento contenuto in questo nodo.
  public T getElem() {
    return this.elem;
  }

  // Cambia l'intero contenuto nel nodo al nuovo valore @elem.
  public void setElem(T elem) {
    this.elem = elem;
  }

  // Ritorna il riferimento al nodo successore, oppure null se non c'e' un successore.
  public Node<T> getParent() {
    return this.parent;
  }

  // Cambia il riferimento al nodo successore con @next.
  public void setParent(Node<T> parent) {
    this.parent = parent;
  }

  public int getRank(){
    return this.rank;
  }

  public void setRank(int rank){
    this.rank = rank;
  }
}