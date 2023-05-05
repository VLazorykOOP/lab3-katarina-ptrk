#include <cmath>
#include <iostream>
#include <string>

using namespace std;

//---TASK 1

class Circle {
public:
  Circle() { // конструктор за замовчуванням
    radius = 1;
    color = "red";
  }

  Circle(double r) { // конструктор з параметром
    setRadius(r);
    color = "red";
  }

  Circle(double r, string c) { // конструктор з двома параметрами
    setRadius(r);
    setColor(c);
  }

  double getRadius() const { // функція-член, що повертає радіус
    return radius;
  }

  string getColor() const { // функція-член, що повертає колір
    return color;
  }

  void setRadius(double r) { // функція-член, що встановлює радіус
    if (r >= 0) {
      radius = r;
    } else {
      cout << "Invalid radius. Setting to default value of 1." << endl;
      radius = 1;
    }
  }

  void setColor(string c) { // функція-член, що встановлює колір
    color = c;
  }

  double getArea() const { // функція-член, що обчислює площу круга
    return M_PI * pow(radius, 2);
  }

  double getCircumference() const { // функція-член, що обчислює довжину кола
    return 2 * M_PI * radius;
  }

  void print() const { // функція-член, що виводить інформацію про об'єкт
    cout << "Circle with radius " << radius << " and color " << color << endl;
    cout << "Area: " << getArea() << endl;
    cout << "Circumference: " << getCircumference() << endl;
  }

private:
  double radius;
  string color;
};

//---TASK 2

class Complex {
private:
  float re, im;
  int state;
  static int count;

public:
  // constructor w/o parameters
  Complex() {
    re = 0; // init in 0
    im = 0;
    state = 0;
    count++; // counter of class elements
  }

  // c-tor with one param float
  Complex(float num) {
    re = num;
    im = num;
    state = 0;
    count++;
  }

  //  ctor with array pointer
  //  Complex(float *arr) {
  //    if (arr == nullptr) {
  //      state = -1; // помилка: вказівник нульовий
  //      return;
  //    }
  //    re = arr[0];
  //    im = arr[1];
  //    state = 0;
  //    count++;
  //  }

  // ctor with two float params
  Complex(float re_, float im_) {
    re = re_;
    im = im_;
    state = 0;
    count++;
  }

  // destructor
  ~Complex() {
    std::cout << "Object destroyed. State: " << state << endl;
    count--;
  }

  // getters and setters
  float getRe() const { return re; };
  void setRe(float newRe = 1) { re = newRe; }
  float getIm() const { return im; }
  void setIm(float newIm = 1) { im = newIm; }
  static int getCount() { return count; }

  // Copy c-tor
  Complex(const Complex &other)
      : re(other.re), im(other.im), state(other.state) {}

  // Assignment operator
  Complex &operator=(const Complex &other) {
    if (this != &other) {
      re = other.re;
      im = other.im;
      state = other.state;
    }
    return *this;
  }

  // print function
  void print() const {
    std::cout << "(" << re << ", " << im << ")" << std::endl;
  }

  // addition operator
  Complex operator+(const Complex &other) const {
    return Complex(re + other.re, im + other.im);
  }

  // subtraction operator
  Complex operator-(const Complex &other) const {
    return Complex(re - other.re, im - other.im);
  }

  // multiplication operator
  Complex operator*(const Complex &other) const {
    return Complex(re * other.re - im * other.im,
                   re * other.im + im * other.re);
  }

  // division operator
  Complex operator/(const Complex &other) const {
    if (other.re == 0 && other.im == 0) {
      Complex result(0);
      result.state = 1;
      return result;
    }
    float denominator = other.re * other.re + other.im * other.im;
    return Complex((re * other.re + im * other.im) / denominator,
                   (im * other.re - re * other.im) / denominator);
  }
  // division by short number
  Complex operator/(short num) {
    if (num == 0) {
      std::cout << "Error! Can't divide by zero. State now is -2." << endl;
      state = -2; // помилка: ділення на нуль
      return *this;
    }
    Complex result;
    result.re = re / num;
    result.im = im / num;
    return result;
  }

  // Calculate norm of complex number
  float norm() const { return std::sqrt(re * re + im * im); }

  // Comparison operators
  bool operator==(const Complex &other) const {
    return (re == other.re) && (im == other.im);
  }

  bool operator>(const Complex &other) const { return norm() > other.norm(); }

  bool operator<(const Complex &other) const { return norm() < other.norm(); }
};

int Complex::count = 0;

//---TASK 3

class Vector {
private:
  long *arr; // array of long elems
  int size;  // size of array

public:
  Vector() {           // ctor wo parameters
    arr = new long[5]; // creating array for 5 elems
    size = 5;          // setting size 5
    for (int i = 0; i < size; i++) {
      arr[i] = 0; // assigning 0 to all elems
    }
  }

  Vector(int n) {      // ctor with size
    arr = new long[n]; // creating array with size
    size = n;          // setting size
    for (int i = 0; i < size; i++) {
      arr[i] = 0; // assigning 0 to all elems
    }
  }

  Vector(int n, long value) { // ctor with size and value
    arr = new long[n];
    size = n;
    for (int i = 0; i < size; i++) {
      arr[i] = value; // setting all elems to value
    }
  }

  Vector(const Vector &vec) { // copy costructor
    arr = new long[vec.size]; // creating new array
    size = vec.size;          // copying size
    for (int i = 0; i < size; i++) {
      arr[i] = vec.arr[i]; // copying elems values
    }
  }

  ~Vector() { delete[] arr; } // removing array

  Vector &operator=(const Vector &vec) { // assignment operator
    if (this != &vec) {                  // if we are not assigning to itself
      delete[] arr;                      // remove current array
      arr = new long[vec.size];          // create new
      size = vec.size;                   // copy size
      for (int i = 0; i < size; i++) {
        arr[i] = vec.arr[i]; // copy elems
      }
    }
    return *this; // return
  }

  void print() { // print all elems
    for (int i = 0; i < size; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }

  long &operator[](int index) {
    return arr[index];
  } // get elem by index operator

  const long &operator[](int index) const { return arr[index]; }

  int getSize() const { return size; }

  void setElement(int pos, long elem) { arr[pos] = elem; }

  long getElement(int pos) { return arr[pos]; }
};

class Matrix {
private:
  Vector *vectors; // array of vector objects
  int rows;
  int cols;
  int error;

public:
  // ctor wo params
  Matrix() : vectors(nullptr), rows(0), cols(0), error(0) {}

  // ctor with size param
  Matrix(int n) : vectors(new Vector[n]), rows(n), cols(0), error(0) {}

  // ctor with size and value
  Matrix(int n, int m, long value = 0)
      : vectors(new Vector[n]), rows(n), cols(m), error(0) {
    for (int i = 0; i < n; i++) {
      vectors[i] = Vector(m, value);
    }
  }

  // copy ctor
  Matrix(const Matrix &other)
      : vectors(nullptr), rows(other.rows), cols(other.cols),
        error(other.error) {
    if (other.vectors != nullptr) {
      vectors = new Vector[rows];
      for (int i = 0; i < rows; i++) {
        vectors[i] = other.vectors[i];
      }
    }
  }

  // assignment operator
  Matrix &operator=(const Matrix &other) {
    if (this != &other) {
      if (vectors != nullptr) {
        delete[] vectors;
      }
      vectors = nullptr;
      rows = other.rows;
      cols = other.cols;
      error = other.error;
      if (other.vectors != nullptr) {
        vectors = new Vector[rows];
        for (int i = 0; i < rows; i++) {
          vectors[i] = other.vectors[i];
        }
      }
    }
    return *this;
  }

  // destructor
  ~Matrix() {
    if (vectors != nullptr) {
      delete[] vectors;
    }
  }

  // set elem
  void setElement(int i, int j, long value = 0) {
    if (i >= 0 && i < rows && j >= 0 && j < cols) {
      vectors[i].setElement(j, value);
    } else {
      error = 1; // index out of range
    }
  }

  long getElement(int i, int j) const {
    if (i >= 0 && i < rows && j >= 0 && j < cols) {
      return vectors[i].getElement(j);
    } else {
      return 0;
    }
  }

  void print() const {
    for (int i = 0; i < rows; i++) {
      vectors[i].print();
    }
  }

  // operation + for two matrix objects
  Matrix operator+(Matrix &other) {
    if (rows == other.rows && cols == other.cols) {
      Matrix result(rows, cols);
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          result.setElement(i, j, getElement(i, j) + other.getElement(i, j));
        }
      }
      return result;
    } else {
      error = 2; // matrices have different dimensions
      return Matrix();
    }
  }

  Matrix operator*(Matrix &other) {
    if (cols == other.rows) {
      Matrix result(rows, other.cols);
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
          long sum = 0;
          for (int k = 0; k < cols; k++) {
            sum += getElement(i, k) * other.getElement(k, j);
          }
          result.setElement(i, j, sum);
        }
      }
      return result;
    } else {
      error = 3; // неправильні розміри матриць для множення
      return Matrix();
    }
  }

  Matrix operator-(Matrix &other) {
    if (rows == other.rows && cols == other.cols) {
      Matrix result(rows, cols);
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          result.setElement(i, j, getElement(i, j) - other.getElement(i, j));
        }
      }
      return result;
    } else {
      error = 2; // матриці мають різні розміри
      return Matrix();
    }
  }

  Matrix operator/(const long scalar) {
    if (scalar == 0) {
      return *this;
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result.setElement(i, j, getElement(i, j) / scalar);
      }
    }
    return result;
  }

  bool operator>(const Matrix &mat) const {
    if (rows != mat.rows || cols != mat.cols) {
      return false;
    }
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (getElement(i, j) <= mat.getElement(i, j)) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator<(const Matrix &mat) const {
    if (rows != mat.rows || cols != mat.cols) {
      return false;
    }
    for (int i = 0; i < mat.rows; i++) {
      for (int j = 0; j < mat.cols; j++) {
        if (getElement(i, j) >= mat.getElement(i, j)) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator==(const Matrix &mat) {
    if (rows != mat.rows || cols != mat.cols) {
      return false;
    }
    for (int i = 0; i < mat.rows; i++) {
      for (int j = 0; j < mat.cols; j++) {
        if (getElement(i, j) != mat.getElement(i, j)) {
          return false;
        }
      }
    }
    return true;
  }
};

int main() {
  cout << endl << "---Task 1---" << endl;
  // створення об'єкту класу Circle
  Circle circle1(5, "blue");

  // вивід інформації за допомогою функції print
  cout << "Circle 1" << endl;
  circle1.print();

  // зміна значень деяких полів та виклик функцій-членів
  circle1.setRadius(10);
  circle1.setColor("green");
  cout << "New Radius: " << circle1.getRadius() << endl;
  cout << "New Color: " << circle1.getColor() << endl;
  cout << "New Area: " << circle1.getArea() << endl;
  cout << "New Circumference: " << circle1.getCircumference() << endl;
  // створення об'єкту класу Circle за допомогою конструктора за замовчуванням
  cout << "Circle 2" << endl;
  Circle circle2;
  circle2.print();
  cout << endl << "---Task 2---" << endl;
  // Create some complex numbers to test with
  Complex complex1(2.0f, 3.0f);
  Complex complex2(3.0f, 4.0f);
  Complex complex3(0.0f, 0.0f);
  Complex complex4(2.0f);

  // Test getters and setters
  std::cout << "c1 = ";
  complex1.print();
  std::cout << "Real part of c1 = " << complex1.getRe() << std::endl;
  std::cout << "Imaginary part of c1 = " << complex1.getIm() << std::endl;
  complex1.setRe(5.0f);
  complex1.setIm(6.0f);
  std::cout << "c1 after setting new real and imaginary parts = ";
  complex1.print();

  // Test addition operator
  std::cout << "c1 + c2 = ";
  (complex1 + complex2).print();

  // Test subtraction operator
  std::cout << "c1 - c2 = ";
  (complex1 - complex2).print();

  // Test multiplication operator
  std::cout << "c1 * c2 = ";
  (complex1 * complex2).print();

  // Test division operator
  std::cout << "c1 / c2 = ";
  (complex1 / complex2).print();
  std::cout << "c3 / c2 = ";
  (complex3 / complex2).print();

  // Test division by short number
  std::cout << "c1 / 2 = ";
  (complex1 / 2).print();
  std::cout << "c1 / 0 = ";
  (complex1 / 0).print();

  // Test norm function
  std::cout << "Norm of c1 = " << complex1.norm() << std::endl;

  // Test comparison operators
  std::cout << "Is c1 equal to c2? " << (complex1 == complex2) << std::endl;
  std::cout << "Is c1 greater than c2? " << (complex1 > complex2) << std::endl;
  std::cout << "Is c1 less than c2? " << (complex1 < complex2) << std::endl;

  // Test copy constructor and assignment operator
  Complex c5 = complex1;
  Complex c6(complex2);
  std::cout << "c5 = ";
  c5.print();
  std::cout << "c6 = ";
  c6.print();
  c5 = complex2;
  std::cout << "c5 after assignment = ";
  c5.print();

  // Test count of Complex objects
  std::cout << "Number of Complex objects created = " << Complex::getCount()
            << std::endl;
  //---TASK 3
  cout << endl << "---TASK 3---" << endl;
  // create and test vectors
  Vector v1; // default constructor
  cout << "V1, default contrustor:" << endl;
  v1.print(); // expected output: 0 0 0 0 0

  Vector v2(3); // constructor with size argument
  cout << "V2, ctor with size argument:" << endl;
  v2[0] = 1;
  v2[2] = 2;
  v2.print(); // expected output: 1 0 2

  cout << "V3, ctor with size and value:" << endl;
  Vector v3(4, 7); // constructor with size and value arguments
  v3.print();      // expected output: 7 7 7 7

  cout << "V4, copy ctor of v3" << endl;
  Vector v4(v3); // copy constructor
  v4[2] = 5;
  cout << "Setting v4[2] = 5. V4:" << endl;
  v4.print(); // expected output: 7 7 5 7

  Vector v5;
  v5 = v4; // assignment operator
  v5[3] = 3;
  cout << "V5, assignment operator, v5[3] = 3. v5:" << endl;
  v5.print(); // expected output: 7 7 5 3

  // Testing Matrix class
  Matrix m1(2, 3, 1), m2(2, 3, 2), m3(3, 2);
  cout << "m1: " << endl;
  m1.print();
  cout << "m2: " << endl;
  m2.print();
  cout << "m3: " << endl;
  m3.print();
  m3 = m1 + m2;
  cout << "m1 + m2: " << endl;
  m3.print();
  m3 = m1 * m2;
  cout << "m1 * m2: " << endl;
  m3.print();
  cout << "m1 == m2: " << (m1 == m2) << endl;
  return 0;
}
