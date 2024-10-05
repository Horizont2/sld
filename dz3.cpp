#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Shape3D {
protected:
    double wallThickness;
    double unitWeight; // питома вага матеріалу

public:
    Shape3D(double wallThickness, double unitWeight)
        : wallThickness(wallThickness), unitWeight(unitWeight) {}

    virtual double getVolume() const = 0; // Чисті віртуальні функції
    virtual double getArea() const = 0;

    double getWeight() const {
        return getVolume() * unitWeight; // Вага = обєм стін * питома вага
    }

    virtual void display() const = 0; // Виведення даних
};

class Parallelepiped : public Shape3D {
    double length, width, height;

public:
    Parallelepiped(double length, double width, double height, double wallThickness, double unitWeight)
        : Shape3D(wallThickness, unitWeight), length(length), width(width), height(height) {}

    double getVolume() const override {
        return (length * width * height) * wallThickness; // Спрощене обчислення обєму стін
    }

    double getArea() const override {
        return 2 * (length * width + width * height + height * length); // Площа поверхні
    }

    void display() const override {
        cout << "Паралелепіпед: Об'єм = " << getVolume()
             << ", Вага = " << getWeight() << " кг" << endl;
    }
};

class Cylinder : public Shape3D {
    double radius, height;

public:
    Cylinder(double radius, double height, double wallThickness, double unitWeight)
        : Shape3D(wallThickness, unitWeight), radius(radius), height(height) {}

    double getVolume() const override {
        return M_PI * pow(radius, 2) * height * wallThickness; // Об'єм стін
    }

    double getArea() const override {
        return 2 * M_PI * radius * (radius + height); // Площа поверхні
    }

    void display() const override {
        cout << "Циліндр: Об'єм = " << getVolume()
             << ", Вага = " << getWeight() << " кг" << endl;
    }
};

class Sphere : public Shape3D {
    double radius;

public:
    Sphere(double radius, double wallThickness, double unitWeight)
        : Shape3D(wallThickness, unitWeight), radius(radius) {}

    double getVolume() const override {
        return (4.0 / 3.0) * M_PI * pow(radius, 3) * wallThickness; // Об'єм стін
    }

    double getArea() const override {
        return 4 * M_PI * pow(radius, 2); // Площа поверхні
    }

    void display() const override {
        cout << "Куля: Об'єм = " << getVolume()
             << ", Вага = " << getWeight() << " кг" << endl;
    }
};

// Похідний клас "Куб"
class Cube : public Shape3D {
    double sideLength;

public:
    Cube(double sideLength, double wallThickness, double unitWeight)
        : Shape3D(wallThickness, unitWeight), sideLength(sideLength) {}

    double getVolume() const override {
        return pow(sideLength, 3) * wallThickness; // Об'єм стін
    }

    double getArea() const override {
        return 6 * pow(sideLength, 2); // Площа поверхні
    }

    void display() const override {
        cout << "Куб: Об'єм = " << getVolume()
             << ", Вага = " << getWeight() << " кг" << endl;
    }
};

void displayShapes(const vector<Shape3D*>& shapes) {
    for (const auto& shape : shapes) {
        shape->display();
    }
}

int main() {
    vector<Shape3D*> shapes;

    shapes.push_back(new Parallelepiped(2.0, 3.0, 4.0, 0.1, 2500));  // Паралелепіпед
    shapes.push_back(new Cylinder(1.0, 5.0, 0.1, 2700));            // Циліндр
    shapes.push_back(new Sphere(2.0, 0.2, 7800));                   // Куля
    shapes.push_back(new Cube(3.0, 0.1, 5000));                     // Куб

    displayShapes(shapes);

    for (auto& shape : shapes) {
        delete shape;
    }

    return 0;
}
