// Primero se aplica cualquier cosa sobre X y después sobre Y. Esto aplica a
// todas las funciones siguientes, por lo que se debe llamar su versión en X.

// La entrada es una matriz a[][], y el árbol se almacena sobre t[][]

// CONSTRUCCIÓN

// Esto es interno, se debe llamar build_x el cual llamará esta función
// Build the Y-axis segment tree for a fixed X-node vx
// vx: index in X-axis segment tree
// lx, rx: X-range covered by vx
// vy: index in Y-axis segment tree for this vx
// ly, ry: Y-range covered by vy
void build_y(int vx, int lx, int rx, int vy, int ly, int ry) {
	if (ly == ry)
		if (lx == rx)
			t[vx][vy] = a[lx][ly];
		else
			t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
	else {
		int my = (ly + ry) / 2;
		build_y (vx, lx, rx, vy*2, ly, my);
		build_y (vx, lx, rx, vy*2+1, my+1, ry);
		t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
	}
}
 
// Sobre el segment-tree en X se construyen segment trees en Y
// Build the X-axis segment tree
// vx: index in X-axis segment tree
// lx, rx: X-range covered by vx
void build_x(int vx, int lx, int rx) {
	if (lx != rx) {
		int mx = (lx + rx) / 2;
		build_x (vx*2, lx, mx);
		build_x (vx*2+1, mx+1, rx);
	}
	build_y (vx, lx, rx, 1, 0, m-1);
}

// EJEMPLO DE QUERY

// Esto es interno, realmente se debería llamar sum_x, pues se procesa primero
// un strip en X y después los strips en Y.
// Query the Y-axis segment tree for a fixed X-node vx
// vx: fixed X-node index
// vy: current Y-node index
// tly, try_: total Y-range covered by vy
// ly, ry: query Y-range
int sum_y(int vx, int vy, int tly, int try_, int ly, int ry) {
	if (ly > ry)
		return 0;
	if (ly == tly && try_ == ry)
		return t[vx][vy];
	int tmy = (tly + try_) / 2;
	return sum_y (vx, vy*2, tly, tmy, ly, min(ry,tmy))
		+ sum_y (vx, vy*2+1, tmy+1, try_, max(ly,tmy+1), ry);
}
 
// O(logn logm) pues se hacen todos los strips en Y sobre el strip en X
// Query the X-axis segment tree
// vx: current X-node index
// tlx, trx: total X-range covered by vx
// lx, rx: query X-range
// ly, ry: query Y-range
int sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
	if (lx > rx)
		return 0;
	if (lx == tlx && trx == rx)
		return sum_y (vx, 1, 0, m-1, ly, ry);
	int tmx = (tlx + trx) / 2;
	return sum_x (vx*2, tlx, tmx, lx, min(rx,tmx), ly, ry)
		+ sum_x (vx*2+1, tmx+1, trx, max(lx,tmx+1), rx, ly, ry);
}

// EJEMPLO DE UPDATE

// De nuevo, esto es interno, se debería llamar update_x
// Update the Y-axis segment tree for a fixed X-node vx
// vx: fixed X-node index
// lx, rx: X-range covered by vx
// vy: current Y-node index
// ly, ry: Y-range covered by vy
// x, y: coordinates to update
// new_val: new value to set at (x, y)
void update_y (int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
	if (ly == ry) {
		if (lx == rx)
			t[vx][vy] = new_val;
		else
			t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
	}
	else {
		int my = (ly + ry) / 2;
		if (y <= my)
			update_y (vx, lx, rx, vy*2, ly, my, x, y, new_val);
		else
			update_y (vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
		t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
	}
}
 
// O(logn logm + k)
// Update the X-axis segment tree
// vx: current X-node index
// lx, rx: X-range covered by vx
// x, y: coordinates to update
// new_val: new value to set at (x, y)
void update_x (int vx, int lx, int rx, int x, int y, int new_val) {
	if (lx != rx) {
		int mx = (lx + rx) / 2;
		if (x <= mx)
			update_x (vx*2, lx, mx, x, y, new_val);
		else
			update_x (vx*2+1, mx+1, rx, x, y, new_val);
	}
	update_y (vx, lx, rx, 1, 0, m-1, x, y, new_val);
}
