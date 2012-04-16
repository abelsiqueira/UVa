#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cmath>

using namespace std;

int main () {
  double Ax, Ay, Bx, By, Cx, Cy;
  double Mx, My, Nx, Ny, mM, mN, x, y, R, e;
  while (!cin.eof()) {
    cin >> Ax >> Ay >> Bx >> By >> Cx >> Cy;
    if (cin.eof())
      break;
    Mx = (Ax + Bx)/2;
    My = (Ay + By)/2;
    Nx = (Ax + Cx)/2;
    Ny = (Ay + Cy)/2;
    mM = Ay - By;
    mN = Ay - Cy;
    if (mM == 0) {
      x = Nx;
      y = My + mM*(x - Mx);
    } else if (mN == 0) {
      x = Mx;
      y = Ny + mN*(x - Nx);
    } else {
      mM = -(Ax - Bx)/mM;
      mN = -(Ax - Cx)/mN;
      x = (mN*Nx - mM*Mx - Ny + My)/(mN - mM);
      y = Ny + mN*(x - Nx);
    }
    R = sqrt( pow(Ax - x,2) + pow(Ay - y,2));
    e = x*x + y*y - R*R;

    if (x >= 0)
      printf("(x - %0.3lf)^2 + ", x);
    else 
      printf("(x + %0.3lf)^2 + ", -x);
    if (y >= 0)
      printf("(y - %0.3lf)^2 = %0.3lf^2\n", y, R);
    else
      printf("(y + %0.3lf)^2 = %0.3lf^2\n", -y, R);

    cout << "x^2 + y^2 ";
    if (x >= 0)
      printf("- %0.3lfx ", 2*x);
    else
      printf("+ %0.3lfx ", -2*x);
    if (y >= 0)
      printf("- %0.3lfy ", 2*y);
    else
      printf("+ %0.3lfy ", -2*y);
    if (e >= 0)
      printf("+ %0.3lf = 0\n\n", e);
    else
      printf("- %0.3lf = 0\n\n", -e);
  }
  return 0;
}
