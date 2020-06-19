// вариант 16
// - D) Прямоугольник
// - H) Эллипс

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

// Интерфейс "Геометрическая фигура".
class IGeoFig {
public:
	// Площадь.
	virtual double square() const = 0;
	// Периметр.
	virtual double perimeter() = 0;
};

// Вектор
class CVector2D {
public:
	double x, y;
	
	double lenght(CVector2D a) {
		return sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));
	}
};

// Интерфейс "Физический объект".
class IPhysObject {
public:
	// Масса, кг.
	virtual double mass() const = 0;
	// Координаты центра масс, м.
	virtual CVector2D position() = 0;
	// Сравнение по массе.
	virtual bool operator== (const IPhysObject& ob) const = 0;
	// Сравнение по массе.
	virtual bool operator< (const IPhysObject& ob) const = 0;
};

// Интерфейс "Отображаемый"
class IPrintable {
public:
	// Отобразить на экране
	// (выводить в текстовом виде параметры фигуры).
	virtual void draw() = 0;
};

// Интерфейс для классов, которые можно задать через диалог с пользователем.
class IDialogInitiable {
public:
	// Задать параметры объекта с помощью диалога с пользователем.
	virtual void initFromDialog() = 0;
};

// Интерфейс "Класс"
class BaseCObject {
public:
	// Имя класса (типа данных).
	virtual const char* classname() = 0;
	// Размер занимаемой памяти.
	virtual unsigned int size() = 0;
};

class Base : public BaseCObject, public IGeoFig, public IPhysObject, public IDialogInitiable, public IPrintable {
public:
	virtual ~Base() = default; //чтобы знать, что деструктор написан только для того, чтобы сделать его виртуальным
};

class Rectangle : public Base {
public:

	CVector2D a, b, c, d;
	double width, height, diagonal, density = 1;

	void get_width_height(CVector2D a, CVector2D b, CVector2D c, CVector2D d) {
		double l[3];
		l[0] = a.lenght(b);
		l[1] = a.lenght(c);
		l[2] = a.lenght(d);
		std::sort(l, l + 3);
		this->width = l[0];
		this->height = l[1];
		this->diagonal = l[2];
	}
	Rectangle() :
		width(1),
		height(2),
		a({0, 0}),
		b({0, 1}),
		c({2, 1}),
		d({2, 0}),
		density(1)
	{
	}

	Rectangle(CVector2D a1, CVector2D b1, CVector2D c1, CVector2D d1) :
		a(a1),
		b(b1),
		c(c1),
		d(d1)
	{
		get_width_height(a, b, c, d);
	}

	~Rectangle() override = default;

	// Площадь.
	double square() const override {
		return width * height;
	}
	// Периметр.
	double perimeter() override {
		return 2 * (width + height);
	}
	// Масса, кг.
	double mass() const override {
		return square() * density;
	}
	// Координаты центра масс, м.
	CVector2D position() override {
		double x_max = std::max(a.x, std::max(b.x, std::max(c.x, d.x)));
		double x_min = std::min(a.x, std::min(b.x, std::min(c.x, d.x)));
		double y_max = std::max(a.y, std::max(b.y, std::max(c.y, d.y)));
		double y_min = std::min(a.y, std::min(b.y, std::min(c.y, d.y)));
		CVector2D pos;
		pos.x = (x_max + x_min) / 2;
		pos.y = (y_max + y_min) / 2;
		return pos;
	}
	// Сравнение по массе.
	bool operator== (const IPhysObject& ob) const override {
		return this->mass() == ob.mass();
	}
	// Сравнение по массе.
	bool operator< (const IPhysObject& ob) const override {
		return this->mass() < ob.mass();
	}
	// Отобразить на экране (выводить в текстовом виде параметры фигуры).
	void draw() override {
		std::cout << "Координаты прямоугольника:\n";
		std::cout << a.x << " " << a.y << "\n";
		std::cout << b.x << " " << b.y << "\n";
		std::cout << c.x << " " << c.y << "\n";
		std::cout << d.x << " " << d.y << "\n";
	}
	// Задать параметры объекта с помощью диалога с пользователем.
	void initFromDialog() override {
		std::cout << "Введите координаты 4 точек прямоугольника (каждая точка на новой строке, x пробел y): \n";
		std::cin >> a.x >> a.y;
		std::cin >> b.x >> b.y;
		std::cin >> c.x >> c.y;
		std::cin >> d.x >> d.y;
		std::cout << "Введите плотность: \n";
		std::cin >> density;
		get_width_height(a, b, c, d);
	}
	// Имя класса (типа данных).
	const char* classname() override {
		return "Rectangle";
	}
	// Размер занимаемой памяти.
	unsigned int size() override {
		return sizeof(*this);
	}
};

class Ellipse : public Base {
public:
	double PI = 3.141592653589793;
	CVector2D f1, f2;
	double a, b, density;

	/*void get_width_height(CVector2D a, CVector2D b, CVector2D c, CVector2D d) {
		double l[3];
		l[0] = a.lenght(b);
		l[1] = a.lenght(c);
		l[2] = a.lenght(d);
		std::sort(l, l + 3);
		this->width = l[0];
		this->height = l[1];
		this->diagonal = l[2];
	}*/

	Ellipse() :
		f1({ 1, 0 }),
		f2({-1, 0}),
		a(3),
		b(2),
		density(1)
	{
	}

	Ellipse(CVector2D f11, CVector2D f21, double a1, double b1) :
		f1(f11),
		f2(f21),
		a(a1),
		b(b1)		
	{
		//get_width_height(a, b, c, d);
	}

	~Ellipse() override = default;

	// Площадь.
	double square() const override {
		return PI * a * b;
	}
	// Периметр.
	double perimeter() override {
		return 4 * (PI * a * b + (a - b) * (a - b)) / (a + b);
	}
	// Масса, кг.
	double mass() const override {
		return square() * density;
	}
	// Координаты центра масс, м.
	CVector2D position() override {
		CVector2D pos;
		pos.x = (f1.x + f2.x) / 2;
		pos.y = (f1.y + f2.y) / 2;
		return pos;
	}
	// Сравнение по массе.
	bool operator== (const IPhysObject& ob) const override {
		return this->mass() == ob.mass();
	}
	// Сравнение по массе.
	bool operator< (const IPhysObject& ob) const override {
		return this->mass() < ob.mass();
	}
	// Отобразить на экране (выводить в текстовом виде параметры фигуры).
	void draw() override {
		std::cout << "Координаты фокусов эллипса:\n";
		std::cout << f1.x << " " << f1.y << "\n";
		std::cout << f2.x << " " << f2.y << "\n";
		std::cout << "a = " << a << "\n";
		std::cout << "b = " << b << "\n";
	}
	// Задать параметры объекта с помощью диалога с пользователем.
	void initFromDialog() override {
		std::cout << "Введите координаты 2 фокусов эллипса (каждая точка на новой строке, x пробел y): \n";
		std::cin >> f1.x >> f1.y;
		std::cin >> f2.x >> f2.y;
		std::cout << "Введите a, b: \n";
		std::cin >> a >> b;
		std::cout << "Введите плотность: \n";
		std::cin >> density;
		//get_width_height(a, b, c, d);
	}
	// Имя класса (типа данных).
	const char* classname() override {
		return "Ellipse";
	}
	// Размер занимаемой памяти.
	unsigned int size() override {
		return sizeof(*this);
	}
};

bool comp(Base * b1, Base * b2) {
	return b1 < b2;
}

int main() {
	setlocale(LC_ALL, "Russian");

	/*std::cout << "Прямоугольник\n";
	Rectangle r;
	r.initFromDialog();
	std::cout << "Ширина:" << r.width << "\n";
	std::cout << "Высота:" << r.height << "\n";
	std::cout << "Плотность:" << r.density << "\n";
	std::cout << "Площадь:" << r.square() << "\n";
	std::cout << "Периметр:" << r.perimeter() << "\n";
	std::cout << "Масса:" << r.mass() << "\n";
	std::cout << "Имя класса: " << r.classname() << "\n";
	std::cout << "Размер: " << r.size() << "\n";
	r.draw();
	std::cout << "\n";
	*/
	/*
	1 1
	1 0
	2 1
	2 0
	2
	*/
	/*
	std::cout << "Эллипс\n";
	Ellipse e;
	e.initFromDialog();
	std::cout << "Площадь:" << e.square() << "\n";
	std::cout << "Периметр:" << e.perimeter() << "\n";
	std::cout << "Масса:" << e.mass() << "\n";
	std::cout << "Имя класса: " << e.classname() << "\n";
	std::cout << "Размер: " << e.size() << "\n";
	e.draw();
	std::cout << "\n";
	*/
	/*
	2 0
	-2 0
	4 3
	*/

	// Хранение множества фигур
	std::vector<Base*> fig;
	int count;
	std::cout << "Введите количество фигур: ";
	std::cin >> count;

	// Динамическое добавление фигур пользователем
	for (int i = 0; i < count; ++i) {
		int t;
		std::cout << "1: Прямоугольник\n";
		std::cout << "2: Эллипс\n";
		std::cout << "Введите тип объекта: ";
		std::cin >> t;

		if (t == 1)
			fig.push_back(new Rectangle);
		else
			fig.push_back(new Ellipse);

		fig.back()->initFromDialog();
	}

	// Отражение всех фигур
	std::cout << "Отражение всех фигур: \n";
	int c = 0;
	for (auto i : fig) {
		c++;
		std::cout << c << "): " << i->classname() << "\n";
		i->draw();
		std::cout << "\n";
	}

	// Суммарная площадь всех фигур
	std::cout << "Суммарная площадь всех фигур: \n";
	double s = 0;
	for (auto i : fig) {
		s += i->square();
	}
	std::cout << s << "\n";

	// Суммарный периметр всех фигур
	double p = 0;
	std::cout << "Суммарный периметр всех фигур: \n";
	for (auto i : fig) {
		p += i->perimeter();
	}
	std::cout << p << "\n";

	// Центр масс всей системы
	std::cout << "Центр масс всей системы:\n";
	double k_x, k_y;
	for (auto i : fig) {
		k_x = i->mass() * i->position().x;
		k_y = i->mass() * i->position().y;
	}
	std::cout << k_x / s << " " << k_y / s << "\n";

	// Память, занимаемая всеми экземплярами классов
	std::cout << "Память, занимаемая всеми экземплярами классов: ";
	int w = 0;
	for (auto i : fig) {
		w += i->size();
	}
	std::cout << w << "\n";

	// Сортировка фигур между собой по массе
	std::sort(fig.begin(), fig.end(), comp);
	std::cout << "Сортировка фигур между собой по массе: \n";
	count = 0;
	for (auto i : fig) {
		count++;
		std::cout << count << "): " << i->classname() << "\n";
		i->draw();
		std::cout << "\n";
	}

	for (auto & i : fig) {
		delete i;
	}
	system("pause");
}