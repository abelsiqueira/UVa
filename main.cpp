#include <iostream>

class Vector3 {
  public:
    Vector3 (int a = 0, int b = 0, int c = 0) {
      v[0] = a;
      v[1] = b;
      v[2] = c;
    }
    ~Vector3 () { }

    void set (int a, int b, int c) {
      V[0] = a;
      V[1] = b;
      V[2] = c;
    }
  private:
    int v[3];
};

float solve (Vector3 *P, Vector3 *Q) {
  return 1.0;
}

int main () {
  size_t T = 0;
  int x, y, z;
  float d = 0.0;
  Vector3 P[4], Q[4];

  cin >> T;
  while (T > 0) {
    T--;
    for (size_t i = 0; i < 4; i++) {
      cin >> x >> y >> z;
      P[i].set(x,y,z);
    }
    for (size_t i = 0; i < 4; i++) {
      cin >> x >> y >> z;
      Q[i].set(x,y,z);
    }
    d = solve (P, Q);
    printf ("%0.2f\n", d);
  }
}
