#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

class Vector3 {
  public:
    Vector3 (int a = 0, int b = 0, int c = 0) {
      v[0] = a;
      v[1] = b;
      v[2] = c;
    }
    ~Vector3 () { }

    void set (int a, int b, int c) {
      v[0] = a;
      v[1] = b;
      v[2] = c;
    }
    int get (int i) const {
      return v[i];
    }
    float sqrdist (const Vector3 & P) {
      float d = pow(v[0] - P.get(0), 2) +
        pow(v[1] - P.get(1), 2) +
        pow(v[2] - P.get(2), 2);
      return d;
    }
    float dist (const Vector3 & P) {
      float d = pow(v[0] - P.get(0), 2) +
        pow(v[1] - P.get(1), 2) +
        pow(v[2] - P.get(2), 2);
      return sqrt(d);
    }
    template < typename number >
    void axpy (number alpha, const Vector3 & P) {
      for (size_t i = 0; i < 3; i++)
        v[i] += alpha*P.get(i);
    }
    void cross (const Vector3 & P, const Vector3 & Q) {
      v[0] = P.get(1)*Q.get(2) - P.get(2)*Q.get(1);
      v[1] = P.get(2)*Q.get(0) - P.get(0)*Q.get(2);
      v[2] = P.get(0)*Q.get(1) - P.get(1)*Q.get(0);
    }
    void normal (const Vector3 P1, Vector3 P2, Vector3 P3) {
      P2.axpy(-1,P1);
      P3.axpy(-1,P1);
      cross(P2, P3);
    }
    float norm () const {
      float n = 0;
      for (size_t i = 0; i < 3; i++)
        n += v[i]*v[i];
      return sqrt(n);
    }
    float sqrnorm () const {
      float n = 0;
      for (size_t i = 0; i < 3; i++)
        n += v[i]*v[i];
      return n;
    }
    float dot (const Vector3 & P) const {
      float d = 0.0;
      for (size_t i = 0; i < 3; i++)
        d += v[i]*P.get(i);
      return d;
    }
  private:
    int v[3];
};

float distance_to_plane (const Vector3 & normal, const Vector3 & planePoint, 
    const Vector3 & point) {
  float d = fabs( normal.dot(planePoint) - normal.dot(point) );
  return d/normal.norm();
}

float upper_bound (Vector3 *P, Vector3 *Q) {
  float d = 1e9, t = 0.0;
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      t = P[i].sqrdist(Q[j]);
      if (t < d)
        d = t;
    }
  }
  return sqrt(d);
}

float solve (Vector3 *P, Vector3 *Q) {
  float d = upper_bound(P, Q), t = 0.0;
  Vector3 normal;
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = i+1; j < 4; j++) {
      for (size_t k = j+1; k < 4; k++ ) {
        // Point P[i], P[j] and P[k] form the plane
        normal.normal(P[i], P[j], P[k]);
        for (size_t q = 0; q < 4; q++) {
          t = distance_to_plane (normal, P[i], Q[q]);
          if (t < d)
            d = t;
        }
      }
    }
  }
  return sqrt(d);
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
