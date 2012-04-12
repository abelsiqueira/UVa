#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
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
    Vector3 operator+(const Vector3 & P) {
      Vector3 Q(P);
      Q.axpy(1,*this);
      return Q;
    }
    Vector3 operator-(const Vector3 & P) {
      Vector3 Q(*this);
      Q.axpy(-1,P);
      return Q;
    }
    Vector3 plus (double a) {
      Vector3 Q(*this);
      for (size_t i = 0; i < 3; i++)
        Q.v[i] *= a;
      return Q;
    }
    double sum () {
      double a = 0;
      for (size_t i = 0; i < 3; i++)
        a += v[i];
      return a;
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

float calc_sqrdist(Vector3 *P, Vector3 *Q, const Vector3 & a, const Vector3 & b) {
  Vector3 distance = P[0];
  distance.axpy(-1, Q[0]);
  for (size_t i = 0; i < 3; i++) {
    distance.axpy(a.get(i), P[i+1]);
    distance.axpy(-b.get(i), Q[i+1]);
  }
  return distance.sqrnorm();
}

float projs (Vector3 *P, Vector3 *Q) {
  Vector3 c1(0,0,0), c2(0,0,0);
  float d = 1e9, t = 0.0;
  for (size_t i = 0; i < 4; i++) {
    c1.axpy(0.25, P[i]);
    c2.axpy(0.25, Q[i]);
  }
  Vector3 dist(c2);
  dist.axpy(-1,c1);

  for (size_t i = 0; i < 4; i++) {
    P[i].axpy(-1, c1);
    Q[i].axpy(-1, c2);
  }

  bool Pbelongs[4], Qbelongs[4];
  size_t Ps = 0, Qs = 0;
  for (size_t i = 0; i < 4; i++) {
    if (dist.dot(P[i]) > 0) {
      Pbelongs[i] = true;
      Ps++;
    } else
      Pbelongs[i] = false;
    if (dist.dot(Q[i]) < 0) {
      Qbelongs[i] = true;
      Qs++;
    } else
      Qbelongs[i] = false;
  }
  for (size_t i = 0; i < 4; i++) {
    P[i].axpy(1, c1);
    Q[i].axpy(1, c2);
  }
//  if ( (Ps == 1) && (Qs == 1) ) {
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        if (Pbelongs[i] && Qbelongs[j]) {
          t = P[i].sqrdist(Q[j]);
          if (t < d)
            d = t;
        }
      }
    }
//  }
  cout << "Ps = " << Ps << endl;
  cout << "Qs = " << Qs << endl;

  return sqrt(d);
}

float drand () {
  float a = rand()%1000;
  a = 2*a/1000.0 - 1;
  return a;
}

bool will_be_feasible (const Vector3 & s, float step, const Vector3 & d) {
  float sum = 0.0, aux;
  for (size_t i = 0; i < 3; i++) {
    aux = s.get(i) + step*d.get(i);
    if (aux < 0)
      return false;
    else
      sum += aux;
  }
  if (sum <= 1)
    return true;
  return false;
}

float solve (Vector3 *P, Vector3 *Q) {
  Vector3 *SDs;
  size_t n = 6;
  SDs = new Vector3[n];
//  SDs[0].set(1, 0, 0);
//  SDs[1].set(0, 1, 0);
//  SDs[2].set(0, 0, 1);
  for (size_t i = 0; i < n; i++)
    SDs[i].set(drand(), drand(), drand());
//  SDs[3].set(-1, 0, 0);
//  SDs[4].set(0, -1, 0);
//  SDs[5].set(0, 0, -1);
//  SDs[3].set(-1, 1, -1);
//  SDs[4].set(-1, -1, 1);
//  SDs[5].set(1, -1, -1);
//  SDs[6].set(1, -1, 1);
//  SDs[7].set(-1, 1, 1);
//  SDs[8].set(1, 1, -1);
  for (size_t i = 1; i < 4; i++) {
    P[i].axpy(-1, P[0]);
    Q[i].axpy(-1, Q[0]);
  }
  double step=1.0;
  double d=1e9, t=0.0;
  Vector3 a(0,0,0), b(0,0,0);
  Vector3 direction(0,0,0);

//  for (size_t i = 0; i < 3; i++)
//    cout << a.get(i) << ",";
//  for (size_t i = 0; i < 3; i++)
//    cout << b.get(i) << ",";
//  cout << endl;
  while (step > 2e-8) {
    bool decreased = false;
    size_t besti = 0;
    for (size_t i = 0; i < n; i++) {
      if (will_be_feasible(a, step, SDs[i]))
        a.axpy(step,SDs[i]);
      else
        continue;
//      direction = P[0];
//      direction.axpy(-1,Q[0]);
//      direction = P[0] - Q[0];
//      for (size_t j = 0; j < 3; j++) {
//        direction.axpy(a.get(j), P[j+1]);
//        direction.axpy(-b.get(j), Q[j+1]);
//      }
//      t = direction.sqrnorm();
      t = calc_sqrdist(P,Q,a,b);
      if (t < d) {
        besti = i;
        d = t;
        decreased = true;
        a.axpy(-step,SDs[i]);
//        break;
      } else
        a.axpy(-step,SDs[i]);
    }
    for (size_t i = 0; i < n; i++) {
      if (will_be_feasible(b, step, SDs[i]))
        b.axpy(step,SDs[i]);
      else
        continue;
//      direction = P[0];
//      direction.axpy(-1,Q[0]);
//      direction = P[0] - Q[0];
//      for (size_t j = 0; j < 3; j++) {
//        direction.axpy(a.get(j), P[j+1]);
//        direction.axpy(-b.get(j), Q[j+1]);
//      }
//      t = direction.sqrnorm();
      t = calc_sqrdist(P,Q,a,b);
      if (t < d) {
        besti = n + i;
        b.axpy(-step,SDs[i]);
        d = t;
        decreased = true;
//        break;
      } else 
        b.axpy(-step,SDs[i]);
    }
    if (!decreased)
      step /= 2;
    else {
      if (besti < n)
        a.axpy(step, SDs[besti]);
      else
        b.axpy(step, SDs[besti - n]);
//      for (size_t i = 0; i < 3; i++)
//        printf("%5.2lf,", a.get(i));
//      for (size_t i = 0; i < 3; i++)
//        printf("%5.2lf,", b.get(i));
//      cout << endl;
    }
  }
  return sqrt(d);
}

int main () {
  size_t T = 0;
  int x, y, z;
  float d = 0.0;
  Vector3 P[4], Q[4];
  srand(time(0));

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
