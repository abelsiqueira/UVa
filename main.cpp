#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>

using namespace std;

class Vector3 {
  public:
    Vector3 (float a = 0, float b = 0, float c = 0) {
      v[0] = a;
      v[1] = b;
      v[2] = c;
    }
    Vector3 (const Vector3 & P) {
      for (size_t i = 0; i < 3; i++)
        v[i] = P.get(i);
    }
    ~Vector3 () { }
    void operator=(const Vector3 & P) {
      for (size_t i = 0; i < 3; i++)
        v[i] = P.get(i);
    }

    void print () {
      for (size_t i = 0; i < 3; i++)
        cout << v[i] << ' ';
      cout << endl;
    }
    void reset () {
      v[0] = 0;
      v[1] = 0;
      v[2] = 0;
    }
    void set (float a, float b, float c) {
      v[0] = a;
      v[1] = b;
      v[2] = c;
    }
    float get (int i) const {
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
    void axpy (float alpha, const Vector3 & P) {
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
      float n = 0.0;
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
    float v[3];
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

float grid_all_combination (Vector3 *P, Vector3 *Q) {
  float d = 1e9, t = 0.0;
  float step = 0.025;
  Vector3 distance;
  for (size_t i = 1; i < 4; i++) {
    P[i].axpy(-1, P[0]);
    Q[i].axpy(-1, Q[0]);
  }
  Vector3 b(P[0]);
  b.axpy(-1, Q[0]);
  for (    float a1 = 0; a1 <= 1.0; a1 += step) {
    for (  float a2 = 0; a2 <= 1.0 - a1; a2 += step) {
      for (float a3 = 0; a3 <= 1.0 - a1 - a2; a3 += step) {
        for (    float b1 = 0; b1 <= 1.0; b1 += step) {
          for (  float b2 = 0; b2 <= 1.0 - b1; b2 += step) {
            for (float b3 = 0; b3 <= 1.0 - b1 - b2; b3 += step) {
              distance = P[0];
              distance.axpy(a1, P[1]);
              distance.axpy(a2, P[2]);
              distance.axpy(a3, P[3]);
              distance.axpy(-1, Q[0]);
              distance.axpy(-b1, Q[1]);
              distance.axpy(-b2, Q[2]);
              distance.axpy(-b3, Q[3]);
              t = distance.sqrnorm();
              if (t < d)
                d = t;
            }
          }
        }
      }
    }
  }
  return sqrt(d);
}

float solve (Vector3 *P, Vector3 *Q) {
  return grid_all_combination (P, Q);
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
