#pragma once

void _3(int &a, int &b);
void _3(int *a, int *b);
void _8(double &c);
void _8(double *c);
void _11(double &radius, double &delta);
void _11(double *radius, double *delta);
void _16(int &n, int &m, int &i1, int &i2, std::vector<std::vector <int> > &matrix);
void _16(int n, int m, int i1, int i2, std::vector<std::vector <int> > *matrix);

//void _16_pointer(int n, int m, int i1, int i2, std::vector<std::vector <int> > *(*matrix[])[]);
//void _16_link(int &n, int &m, int &i1, int &i2, int matrix);
//void _16_pointer(int n, int m, int i1, int i2, int matrix[]);