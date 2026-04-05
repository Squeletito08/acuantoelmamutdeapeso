using ll = long long;
using i16 = short int;

// nodo avl
struct avl_n
{
  avl_n *l, *r; // izq/der
  i16 h; // altura
  ll sz; // tamaño subárbol
  int x; // valor

  // constructor
  avl_n(int x) : l(0), r(0), h(1), sz(1), x(x)
  { }

  // computa balance
  inline i16 balance() { return (r ? r->h : 0) - (l ? l->h : 0); }

  // encuentra el mínimo del subárbol
  avl_n *min()
  {
    avl_n *r = this;
    while (r->l)
      r = r->l;
    return r;
  }

  // encuentra el máximo del subárbol
  avl_n *max()
  {
    avl_n *r = this;
    while (r->r)
      r = r->r;
    return r;
  }
};

// arbol avl
struct avl_t
{
  // raíz
  avl_n *r;

  // constructor
  avl_t() : r(0)
  { }

  // auxiliar para computar el tamaño de un nodo posiblemente nulo
  inline int v_sz(avl_n *&v) { return v ? v->sz : 0; }
  // auxiliar para computar la altura de un nodo posiblemente nulo
  inline int v_h(avl_n *&v) { return v ? v->h : 0; }

  // actualiza altura y tamaño de un subárbol (vértice)
  inline void update(avl_n *&v)
  {
    if (!v)
      return;
    v->h = 1 + max(v_h(v->l), v_h(v->r));
    v->sz = 1 + v_sz(v->l) + v_sz(v->r);
  }

  // obtiene el tamaño del árbol
  inline int sz() { return v_sz(r); }

  // giro izq
  void lrot(avl_n *&v)
  {
    avl_n *y = v->r, *t = y->l;
    y->l = v, v->r = t;
    update(v), update(y);
    v = y;
  }

  // giro der
  void rrot(avl_n *&v)
  {
    avl_n *x = v->l, *t = x->r;
    x->r = v, v->l = t;
    update(v), update(x);
    v = x;
  }

  // actualiza el balance y realiza las rotaciones para mantenerlo
  void updateb(avl_n *&v)
  {
    if (!v)
      return;
    i16 b = v->balance();
    if (b > 1)
    {
      if (v->r->balance() < 0)
        rrot(v->r);
      lrot(v);
    }
    else if (b < -1)
    {
      if (v->l->balance() > 0)
        lrot(v->l);
      rrot(v);
    }
  }

  // inserta un nuevo valor al arbol
  void insert(avl_n *&v, int x)
  {
    if (v)
    {
      if (x < v->x)
        insert(v->l, x);
      else
        insert(v->r, x);
      update(v), updateb(v);
    }
    else
    {
      v = new avl_n(x);
    }
  }

  // busca si el valor se encuentra en el árbol
  avl_n *search(int &x)
  {
    avl_n *v = r;
    while (v)
    {
      if (x == v->x)
        break;
      v = (x < v->x ? v->l : v->r);
    }
    return v;
  }

  // borra el valor del árbol si existe
  void erase(avl_n *&v, int &x)
  {
    if (!v)
      return;
    if (x < v->x)
      erase(v->l, x);
    else if (x > v->x)
      erase(v->r, x);
    else
    {
      if (!v->l)
        v = v->r;
      else if (!v->r)
        v = v->l;
      else
      {
        v->x = v->r->min()->x;
        erase(v->r, v->x);
      }
    }
    update(v), updateb(v);
  }

  // inserta un valor al árbol
  void insert(int x)
  {
    insert(r, x);
  }

  // elimina un valor del árbol
  void erase(int x)
  {
    erase(r, x);
  }

  // encuentra el k-ésimo elemento
  avl_n *kth(int i)
  {
    avl_n *v = r;
    while (i != v_sz(v->l))
    {
      if (i < v_sz(v->l))
      {
        v = v->l;
      }
      else
      {
        i -= v_sz(v->l) + 1;
        v = v->r;
      }
    }
    return v;
  }

  // imprime la mediana (o su promedio si hay dos, o indica que no hay elementos
  // suficientes para una mediana)
  void print_median()
  {
    if (sz() == 0)
    {
      cout << "Empty!\n";
    }
    else if (sz() % 2)
    {
      cout << kth(sz() / 2)->x << '\n';
    }
    else
    {
      avl_n *upmed = kth(sz() >> 1);
      avl_n *downmed = (upmed->l ? upmed->l->max() : kth((sz() >> 1) - 1));
      cout << (downmed->x + ((upmed->x - downmed->x) >> 1)) << '\n';
    }
  }
};
