#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression {
 protected:
  long myInt;

 public:
  NumExpression(long givenInt) : myInt(givenInt) {}
  virtual ~NumExpression() {}
  virtual std::string toString() const {
    std::stringstream stream;
    stream << myInt;
    std::string myString;
    stream >> myString;
    return myString;
  }
  virtual long evaluate() const { return myInt; }
};

class ArithmeticExpression : public Expression {
 protected:
  Expression * lhs;
  Expression * rhs;
  std::string function;

 public:
  ArithmeticExpression(Expression * givenLhs, Expression * givenRhs) :
      lhs(givenLhs), rhs(givenRhs) {}
  virtual ~ArithmeticExpression() {
    delete lhs;
    delete rhs;
  }
  virtual std::string toString() const {
    return "(" + lhs->toString() + function + rhs->toString() + ")";
  }
};

class PlusExpression : public ArithmeticExpression {
 public:
  PlusExpression(Expression * givenLhs, Expression * givenRhs) :
      ArithmeticExpression(givenLhs, givenRhs) {
    ArithmeticExpression::function = " + ";
  }
  virtual ~PlusExpression() {}
  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
};

class MinusExpression : public ArithmeticExpression {
 public:
  MinusExpression(Expression * givenLhs, Expression * givenRhs) :
      ArithmeticExpression(givenLhs, givenRhs) {
    ArithmeticExpression::function = " - ";
  }
  virtual ~MinusExpression() {}
  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
};

class TimesExpression : public ArithmeticExpression {
 public:
  TimesExpression(Expression * givenLhs, Expression * givenRhs) :
      ArithmeticExpression(givenLhs, givenRhs) {
    ArithmeticExpression::function = " * ";
  }
  virtual ~TimesExpression() {}
  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
};

class DivExpression : public ArithmeticExpression {
 public:
  DivExpression(Expression * givenLhs, Expression * givenRhs) :
      ArithmeticExpression(givenLhs, givenRhs) {
    ArithmeticExpression::function = " / ";
  }
  virtual ~DivExpression() {}
  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
};
