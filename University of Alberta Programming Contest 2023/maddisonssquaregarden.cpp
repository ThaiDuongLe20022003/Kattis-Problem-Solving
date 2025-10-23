#include <bits/stdc++.h>
using namespace std;
int n;
double d;
double xh[1000100];
double yh[1000100];
double xw[1000100];
double yw[1000100];
double t[1000100];

double box_dist(double x, double y, double sz) {
    double xd = abs(x-0.5) - sz/2;
    double yd = abs(y-0.5) - sz/2;
    return hypot(max(xd,0.0), max(yd,0.0)) + min(max(xd,yd),0.0);
}
bool test(int i, double sz) {
    auto f = [&](double pt) { return make_pair(xh[i]*(1-pt) + xw[i]*pt, yh[i]*(1-pt) + yw[i]*pt); };
    // find a point inside the box (if any)
    double lo = 0;
    double hi = 1;
    double mid, x, y, d1;
    while (hi - lo > 1e-7) {
        mid = (lo + hi)/2;
        auto pt = f(mid);
        x = pt.first;
        y = pt.second;
        auto [x2, y2] = f(mid+1e-10);
        d1 = box_dist(x, y, sz);
        double d2 = box_dist(x2, y2, sz);
        if (d1 <= 0)
            break;
        if (d1 < d2)
            hi = mid;
        else
            lo = mid;
    }
    if (d1 <= 0) {
        // line hits the box at (x, y)

        // find point where it enters
        double lo = 0;
        double hi = mid;
        while (hi - lo > 1e-7) {
            double mid = (lo + hi)/2;
            auto [x, y] = f(mid);
            double d1 = box_dist(x, y, sz);
            if (d1 < 0)
                hi = mid;
            else
                lo = mid;
        }
        double enter_at = (lo + hi)/2;
        // find point where it leaves
        lo = mid;
        hi = 1;
        while (hi - lo > 1e-7) {
            double mid = (lo + hi)/2;
            auto [x, y] = f(mid);
            double d1 = box_dist(x, y, sz);
            if (d1 > 0)
                hi = mid;
            else
                lo = mid;
        }
        double leave_at = (lo + hi)/2;
        auto fe = f(enter_at);
        auto fl = f(leave_at);
        auto f0 = f(0);
        auto f1 = f(1);
        // cout << "enter " << enter_at << " " << box_dist(fe.first,fe.second,sz) << endl;
        // cout << "leave " << leave_at << " " << box_dist(fl.first,fl.second,sz) << endl;
        // cout << fe.first << " " << fe.second << endl;
        // cout << fl.first << " " << fl.second << endl;
        double el_dist = hypot(fl.first-fe.first,fl.second-fe.second);
        double time = el_dist/(0.1*d)
            + (hypot(f1.first-f0.first, f1.second-f0.second)-el_dist)/0.1;
        // cout << "time " << time << endl;
        if (time > t[i])
            return false;
    } else {
        // line never hits the box
        double time = hypot(xh[i]-xw[i], yh[i]-yw[i])/0.1;
        if (time > t[i])
            return false;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> d;
    for (int i = 0; i < n; i++)
        cin >> xh[i] >> yh[i] >> xw[i] >> yw[i] >> t[i];
    double top = 1;
    double lo, hi;
    for (int i = 0; i < n; i++) {
        lo = 0;
        hi = top;
        while (hi - lo > 1e-7) {
            double mid = (lo + hi)/2;
            if (test(i, mid))
                lo = mid;
            else
                hi = mid;
        }
        if (test(i, lo))
            top = min(top, hi);
        else {
            cout << -1 << endl;
            return 0;
        }
    }
    cout << fixed << setprecision(10);
    cout << (lo + hi)/2 << endl;
}