#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

class Vector3 {
  public:
    Vector3 (double a = 0, double b = 0, double c = 0) {
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
    void set (double a, double b, double c) {
      v[0] = a;
      v[1] = b;
      v[2] = c;
    }
    double get (int i) const {
      return v[i];
    }
    double sqrdist (const Vector3 & P) {
      double d = pow(v[0] - P.get(0), 2) +
        pow(v[1] - P.get(1), 2) +
        pow(v[2] - P.get(2), 2);
      return d;
    }
    double dist (const Vector3 & P) {
      double d = pow(v[0] - P.get(0), 2) +
        pow(v[1] - P.get(1), 2) +
        pow(v[2] - P.get(2), 2);
      return sqrt(d);
    }
    void axpy (double alpha, const Vector3 & P) {
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
    double norm () const {
      double n = 0;
      for (size_t i = 0; i < 3; i++)
        n += v[i]*v[i];
      return sqrt(n);
    }
    double sqrnorm () const {
      double n = 0.0;
      for (size_t i = 0; i < 3; i++)
        n += v[i]*v[i];
      return n;
    }
    double dot (const Vector3 & P) const {
      double d = 0.0;
      for (size_t i = 0; i < 3; i++)
        d += v[i]*P.get(i);
      return d;
    }
  private:
    double v[3];
};

double distance_to_plane (const Vector3 & normal, const Vector3 & planePoint, 
    const Vector3 & point) {
  double d = fabs( normal.dot(planePoint) - normal.dot(point) );
  return d/normal.norm();
}

double upper_bound (Vector3 *P, Vector3 *Q) {
  double d = 1e9, t = 0.0;
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      t = P[i].sqrdist(Q[j]);
      if (t < d)
        d = t;
    }
  }
  return sqrt(d);
}

double grid_all_combination (Vector3 *P, Vector3 *Q) {
  double d = 1e9, t = 0.0;
  double step = 0.025;
  Vector3 distance;
  for (size_t i = 1; i < 4; i++) {
    P[i].axpy(-1, P[0]);
    Q[i].axpy(-1, Q[0]);
  }
  Vector3 b(P[0]);
  b.axpy(-1, Q[0]);
  for (    double a1 = 0; a1 <= 1.0; a1 += step) {
    for (  double a2 = 0; a2 <= 1.0 - a1; a2 += step) {
      for (double a3 = 0; a3 <= 1.0 - a1 - a2; a3 += step) {
        for (    double b1 = 0; b1 <= 1.0; b1 += step) {
          for (  double b2 = 0; b2 <= 1.0 - b1; b2 += step) {
            for (double b3 = 0; b3 <= 1.0 - b1 - b2; b3 += step) {
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

double calc_sqrdist(Vector3 *P, Vector3 *Q, const Vector3 & a, const Vector3 & b) {
  Vector3 distance = P[0];
  distance.axpy(-1, Q[0]);
  for (size_t i = 0; i < 3; i++) {
    distance.axpy(a.get(i), P[i+1]);
    distance.axpy(-b.get(i), Q[i+1]);
  }
  return distance.sqrnorm();
}

double projs (Vector3 *P, Vector3 *Q) {
  Vector3 c1(0,0,0), c2(0,0,0);
  double d = 1e9, t = 0.0;
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

double drand () {
  double a = rand()%1000;
  a = 2*a/1000.0 - 1;
  return a;
}

bool will_be_feasible (const Vector3 & s, double step, const Vector3 & d) {
  double sum = 0.0, aux;
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

double solve (Vector3 *P, Vector3 *Q) {
  Vector3 *SDs;
  size_t n = 15;
  double athird=1.0/3.0;
  SDs = new Vector3[n];
//  for (size_t i = 0; i < n; i++)
//    SDs[i].set(drand(), drand(), drand());
  //Setting movements for faces.
  SDs[0].set(1, 0, 0);
  SDs[1].set(0, 1, 0);
  SDs[2].set(0, 0, 1);
  SDs[3].set(-1,0,0);
  SDs[4].set(0,-1,0);
  SDs[5].set(0,0,-1);
  SDs[6].set(0.5,-0.5,0);
  SDs[7].set(-0.5,0.5,0);
  SDs[8].set(0.5,0,-0.5);
  SDs[9].set(-0.5,0,0.5);
  SDs[10].set(0,0.5,-0.5);
  SDs[11].set(0,-0.5,0.5);
  SDs[12].set(2*athird,-athird,-athird);
  SDs[13].set(-athird,2*athird,-athird);
  SDs[14].set(-athird,-athird,2*athird);
  for (size_t i = 1; i < 4; i++) {
    P[i].axpy(-1, P[0]);
    Q[i].axpy(-1, Q[0]);
  }
  double step=1.0, minstep = 2e-6;
  double d=1e9, t=0.0;
  Vector3 a(0.25,0.25,0.25), b(0.25,0.25,0.25);
  Vector3 direction(0,0,0);
  bool fast = true;

  while (step > minstep) {
    bool decreased = false;
    size_t besti = 0;
    for (size_t i = 0; i < n; i++) {
      if (fast && decreased) continue;
      if (will_be_feasible(a, step, SDs[i]))
        a.axpy(step,SDs[i]);
      else
        continue;
      t = calc_sqrdist(P,Q,a,b);
      if (t < d) {
        besti = i;
        d = t;
        decreased = true;
      }
      a.axpy(-step,SDs[i]);
    }
    for (size_t i = 0; i < n; i++) {
      if (fast && decreased) continue;
      if (will_be_feasible(b, step, SDs[i]))
        b.axpy(step,SDs[i]);
      else
        continue;
      t = calc_sqrdist(P,Q,a,b);
      if (t < d) {
        besti = n + i;
        d = t;
        decreased = true;
      }
      b.axpy(-step,SDs[i]);
    }
    if (!decreased) {
      step = step/2.0;
    } else {
      if (besti < n)
        a.axpy(step, SDs[besti]);
      else
        b.axpy(step, SDs[besti - n]);
    }
  }
  return sqrt(d);
}

int main () {
  size_t T = 0;
  int x, y, z;
  double d = 0.0;
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
