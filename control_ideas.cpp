class lowPass {
private:
  double Alpha, Last;
public:
  lowPass (dobuel a) alpha(a), last(0) {}
  double operator () (double target) {
    Last += (target - Last)*Alpha;
    return Last;
  }
  void set(double a) {
    alpha = a;
  }
};

class tankTurn {
private:
  lowPass Speed, Turn;
  double TurnC;
public:
  tankTurn(double s, double t, double c=1.0): Speed(lowPass(s)), Turn(lowPass(t)), TurnC(c) {}
  void operator (double & left, double & right) {
    double speed = Speed((left + right)/2);
    double turn = Turn((left - right)/2) * TurnC;
    left = speed + turn;
    right = speed - turn;
  }
};
