// linea 2d

using ff = float;

// distancia linea-punto, donde la línea se define por a->b
ff dist_lin_v2(v2 p, v2 a, v2 b) {
    ff A = cross(b-a, p-a);
    return fabs(A)/((b-a).norm());
}

// si se intersectan dos líneas (p->r y q->s), y en out dónde
bool intersect_lin_lin(v2 p, v2 r, v2 q, v2 s, v2 &out){
  double rxs = cross(r, s);
  if (fabs(rxs) < 1e-12) 
    return false;
  double t = cross(q - p, s) / rxs;
  out = { p.x + t * r.x,
          p.y + t * r.y };
  return true;
}
