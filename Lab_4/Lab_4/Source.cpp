// ������� 16
// - D) �������������
// - H) ������

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

// ��������� "�������������� ������".
class IGeoFig {
public:
	// �������.
	virtual double square() const = 0;
	// ��������.
	virtual double perimeter() = 0;
};

// ������
class CVector2D {
public:
	double x, y;
	
	double lenght(CVector2D a) {
		return sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));
	}
};

// ��������� "���������� ������".
class IPhysObject {
public:
	// �����, ��.
	virtual double mass() const = 0;
	// ���������� ������ ����, �.
	virtual CVector2D position() = 0;
	// ��������� �� �����.
	virtual bool operator== (const IPhysObject& ob) const = 0;
	// ��������� �� �����.
	virtual bool operator< (const IPhysObject& ob) const = 0;
};

// ��������� "������������"
class IPrintable {
public:
	// ���������� �� ������
	// (�������� � ��������� ���� ��������� ������).
	virtual void draw() = 0;
};

// ��������� ��� �������, ������� ����� ������ ����� ������ � �������������.
class IDialogInitiable {
public:
	// ������ ��������� ������� � ������� ������� � �������������.
	virtual void initFromDialog() = 0;
};

// ��������� "�����"
class BaseCObject {
public:
	// ��� ������ (���� ������).
	virtual const char* classname() = 0;
	// ������ ���������� ������.
	virtual unsigned int size() = 0;
};

class Base : public BaseCObject, public IGeoFig, public IPhysObject, public IDialogInitiable, public IPrintable {
public:
	virtual ~Base() = default; //����� �����, ��� ���������� ������� ������ ��� ����, ����� ������� ��� �����������
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

	// �������.
	double square() const override {
		return width * height;
	}
	// ��������.
	double perimeter() override {
		return 2 * (width + height);
	}
	// �����, ��.
	double mass() const override {
		return square() * density;
	}
	// ���������� ������ ����, �.
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
	// ��������� �� �����.
	bool operator== (const IPhysObject& ob) const override {
		return this->mass() == ob.mass();
	}
	// ��������� �� �����.
	bool operator< (const IPhysObject& ob) const override {
		return this->mass() < ob.mass();
	}
	// ���������� �� ������ (�������� � ��������� ���� ��������� ������).
	void draw() override {
		std::cout << "���������� ��������������:\n";
		std::cout << a.x << " " << a.y << "\n";
		std::cout << b.x << " " << b.y << "\n";
		std::cout << c.x << " " << c.y << "\n";
		std::cout << d.x << " " << d.y << "\n";
	}
	// ������ ��������� ������� � ������� ������� � �������������.
	void initFromDialog() override {
		std::cout << "������� ���������� 4 ����� �������������� (������ ����� �� ����� ������, x ������ y): \n";
		std::cin >> a.x >> a.y;
		std::cin >> b.x >> b.y;
		std::cin >> c.x >> c.y;
		std::cin >> d.x >> d.y;
		std::cout << "������� ���������: \n";
		std::cin >> density;
		get_width_height(a, b, c, d);
	}
	// ��� ������ (���� ������).
	const char* classname() override {
		return "Rectangle";
	}
	// ������ ���������� ������.
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

	// �������.
	double square() const override {
		return PI * a * b;
	}
	// ��������.
	double perimeter() override {
		return 4 * (PI * a * b + (a - b) * (a - b)) / (a + b);
	}
	// �����, ��.
	double mass() const override {
		return square() * density;
	}
	// ���������� ������ ����, �.
	CVector2D position() override {
		CVector2D pos;
		pos.x = (f1.x + f2.x) / 2;
		pos.y = (f1.y + f2.y) / 2;
		return pos;
	}
	// ��������� �� �����.
	bool operator== (const IPhysObject& ob) const override {
		return this->mass() == ob.mass();
	}
	// ��������� �� �����.
	bool operator< (const IPhysObject& ob) const override {
		return this->mass() < ob.mass();
	}
	// ���������� �� ������ (�������� � ��������� ���� ��������� ������).
	void draw() override {
		std::cout << "���������� ������� �������:\n";
		std::cout << f1.x << " " << f1.y << "\n";
		std::cout << f2.x << " " << f2.y << "\n";
		std::cout << "a = " << a << "\n";
		std::cout << "b = " << b << "\n";
	}
	// ������ ��������� ������� � ������� ������� � �������������.
	void initFromDialog() override {
		std::cout << "������� ���������� 2 ������� ������� (������ ����� �� ����� ������, x ������ y): \n";
		std::cin >> f1.x >> f1.y;
		std::cin >> f2.x >> f2.y;
		std::cout << "������� a, b: \n";
		std::cin >> a >> b;
		std::cout << "������� ���������: \n";
		std::cin >> density;
		//get_width_height(a, b, c, d);
	}
	// ��� ������ (���� ������).
	const char* classname() override {
		return "Ellipse";
	}
	// ������ ���������� ������.
	unsigned int size() override {
		return sizeof(*this);
	}
};

bool comp(Base * b1, Base * b2) {
	return b1 < b2;
}

int main() {
	setlocale(LC_ALL, "Russian");

	/*std::cout << "�������������\n";
	Rectangle r;
	r.initFromDialog();
	std::cout << "������:" << r.width << "\n";
	std::cout << "������:" << r.height << "\n";
	std::cout << "���������:" << r.density << "\n";
	std::cout << "�������:" << r.square() << "\n";
	std::cout << "��������:" << r.perimeter() << "\n";
	std::cout << "�����:" << r.mass() << "\n";
	std::cout << "��� ������: " << r.classname() << "\n";
	std::cout << "������: " << r.size() << "\n";
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
	std::cout << "������\n";
	Ellipse e;
	e.initFromDialog();
	std::cout << "�������:" << e.square() << "\n";
	std::cout << "��������:" << e.perimeter() << "\n";
	std::cout << "�����:" << e.mass() << "\n";
	std::cout << "��� ������: " << e.classname() << "\n";
	std::cout << "������: " << e.size() << "\n";
	e.draw();
	std::cout << "\n";
	*/
	/*
	2 0
	-2 0
	4 3
	*/

	// �������� ��������� �����
	std::vector<Base*> fig;
	int count;
	std::cout << "������� ���������� �����: ";
	std::cin >> count;

	// ������������ ���������� ����� �������������
	for (int i = 0; i < count; ++i) {
		int t;
		std::cout << "1: �������������\n";
		std::cout << "2: ������\n";
		std::cout << "������� ��� �������: ";
		std::cin >> t;

		if (t == 1)
			fig.push_back(new Rectangle);
		else
			fig.push_back(new Ellipse);

		fig.back()->initFromDialog();
	}

	// ��������� ���� �����
	std::cout << "��������� ���� �����: \n";
	int c = 0;
	for (auto i : fig) {
		c++;
		std::cout << c << "): " << i->classname() << "\n";
		i->draw();
		std::cout << "\n";
	}

	// ��������� ������� ���� �����
	std::cout << "��������� ������� ���� �����: \n";
	double s = 0;
	for (auto i : fig) {
		s += i->square();
	}
	std::cout << s << "\n";

	// ��������� �������� ���� �����
	double p = 0;
	std::cout << "��������� �������� ���� �����: \n";
	for (auto i : fig) {
		p += i->perimeter();
	}
	std::cout << p << "\n";

	// ����� ���� ���� �������
	std::cout << "����� ���� ���� �������:\n";
	double k_x, k_y;
	for (auto i : fig) {
		k_x = i->mass() * i->position().x;
		k_y = i->mass() * i->position().y;
	}
	std::cout << k_x / s << " " << k_y / s << "\n";

	// ������, ���������� ����� ������������ �������
	std::cout << "������, ���������� ����� ������������ �������: ";
	int w = 0;
	for (auto i : fig) {
		w += i->size();
	}
	std::cout << w << "\n";

	// ���������� ����� ����� ����� �� �����
	std::sort(fig.begin(), fig.end(), comp);
	std::cout << "���������� ����� ����� ����� �� �����: \n";
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