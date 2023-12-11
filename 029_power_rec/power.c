unsigned power(unsigned x, unsigned y);

unsigned power_helper(unsigned x, unsigned y, unsigned result) {
  if (y == 0) {
    return result;
  }
  else {
    return power_helper(x, y - 1, result * x);
  }
}

unsigned power(unsigned x, unsigned y) {
  return power_helper(x, y, 1);
}
