#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

class Edge
{
public:
    int edge[3][3];
    int color;

    Edge()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                edge[i][j] = 0;
    }

    Edge(int color_) :
            color(color_)
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                edge[i][j] = color;
    }

    ~Edge() = default;

    void print_edge()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                cout << edge[i][j] << " ";
            cout << "\n";
        }
    }
    //bool operator==(Edge)
};

class Cube
{
public:
    Edge cube[6];//0-D, 1-F, 2-R, 3-B, 4-L, 5-U
    string s;
    int color[6];
    //bool is_correct;
    vector<int> moves;
    Cube()
    {
        for (int i = 0; i < 6; i++)
        {
            cube[i] = Edge(i);
            color[i] = i;
        }
        s = "";
        //is_correct = true;
    }

    Cube(const Cube &other)
    {
        for (int i = 0; i < 6; i++)
        {
            cube[i] = Edge(i);
            color[i] = other.color[i];
        }
        for (int k = 0; k < 6; k++)
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    cube[k].edge[i][j] = other.cube[k].edge[i][j];
        s = other.s;
        //is_correct = true;
    }

    ~Cube() = default;

    void read(string name)
    {
        ifstream fin;
        char c;
        fin.open(name);
        if (!fin.is_open())
            cerr << "input file is not open";
        for (int i = 0; i < 6; i++)
        {
            fin >> c;
            switch (c)
            {
                case 'D':
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            fin >> cube[0].edge[i][j];
                    break;
                case 'F':
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            fin >> cube[1].edge[i][j];
                    break;
                case 'R':
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            fin >> cube[2].edge[i][j];
                    break;
                case 'B':
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            fin >> cube[3].edge[i][j];
                    break;
                case 'L':
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            fin >> cube[4].edge[i][j];
                    break;
                case 'U':
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            fin >> cube[5].edge[i][j];
                    break;
                default:
                    cerr << "Wrong input file";
                    break;
            }
            color[0] = cube[0].edge[1][1];
            color[1] = cube[1].edge[1][1];
            color[2] = cube[2].edge[1][1];
            color[3] = cube[3].edge[1][1];
            color[4] = cube[4].edge[1][1];
            color[5] = cube[5].edge[1][1];
        }
    }
    void write(string name)
    {
        ofstream fout;
        fout.open(name);
        if (!fout.is_open())
            cerr << "output file is not open";
        fout << "D\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                fout << cube[0].edge[i][j] << " ";
            fout << "\n";
        }
        fout << "F\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                fout << cube[1].edge[i][j] << " ";
            fout << "\n";
        }
        fout << "R\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                fout << cube[2].edge[i][j] << " ";
            fout << "\n";
        }
        fout << "B\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                fout << cube[3].edge[i][j] << " ";
            fout << "\n";
        }
        fout << "L\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                fout << cube[4].edge[i][j] << " ";
            fout << "\n";
        }
        fout << "U\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                fout << cube[5].edge[i][j] << " ";
            fout << "\n";
        }
    }

    void rotation(int(&edge)[3][3])
    {
        int t = edge[0][0];
        edge[0][0] = edge[2][0];
        edge[2][0] = edge[2][2];
        edge[2][2] = edge[0][2];
        edge[0][2] = t;
        t = edge[0][1];
        edge[0][1] = edge[1][0];
        edge[1][0] = edge[2][1];
        edge[2][1] = edge[1][2];
        edge[1][2] = t;
    }

    void rotation_(int(&edge)[3][3])
    {
        int t = edge[0][0];
        edge[0][0] = edge[0][2];
        edge[0][2] = edge[2][2];
        edge[2][2] = edge[2][0];
        edge[2][0] = t;
        t = edge[0][1];
        edge[0][1] = edge[1][2];
        edge[1][2] = edge[2][1];
        edge[2][1] = edge[1][0];
        edge[1][0] = t;
    }

    string F()
    {
        rotation(cube[1].edge);
        int t1 = cube[2].edge[0][0];
        int t2 = cube[2].edge[1][0];
        int t3 = cube[2].edge[2][0];
        cube[2].edge[0][0] = cube[5].edge[2][0];
        cube[2].edge[1][0] = cube[5].edge[2][1];
        cube[2].edge[2][0] = cube[5].edge[2][2];
        cube[5].edge[2][0] = cube[4].edge[2][2];
        cube[5].edge[2][1] = cube[4].edge[1][2];
        cube[5].edge[2][2] = cube[4].edge[0][2];
        cube[4].edge[2][2] = cube[0].edge[0][2];
        cube[4].edge[1][2] = cube[0].edge[0][1];
        cube[4].edge[0][2] = cube[0].edge[0][0];
        cube[0].edge[0][2] = t1;
        cube[0].edge[0][1] = t2;
        cube[0].edge[0][0] = t3;
        moves.push_back(1);
        return "F";
    }
    string B()
    {
        rotation(cube[3].edge);
        int t1 = cube[4].edge[0][0];
        int t2 = cube[4].edge[1][0];
        int t3 = cube[4].edge[2][0];
        cube[4].edge[0][0] = cube[5].edge[0][2];
        cube[4].edge[1][0] = cube[5].edge[0][1];
        cube[4].edge[2][0] = cube[5].edge[0][0];
        cube[5].edge[0][2] = cube[2].edge[2][2];
        cube[5].edge[0][1] = cube[2].edge[1][2];
        cube[5].edge[0][0] = cube[2].edge[0][2];
        cube[2].edge[2][2] = cube[0].edge[2][0];
        cube[2].edge[1][2] = cube[0].edge[2][1];
        cube[2].edge[0][2] = cube[0].edge[2][2];
        cube[0].edge[2][0] = t1;
        cube[0].edge[2][1] = t2;
        cube[0].edge[2][2] = t3;
        moves.push_back(3);
        return "B";
    }
    string L()
    {
        rotation(cube[4].edge);
        int t1 = cube[1].edge[0][0];
        int t2 = cube[1].edge[1][0];
        int t3 = cube[1].edge[2][0];
        cube[1].edge[0][0] = cube[5].edge[0][0];
        cube[1].edge[1][0] = cube[5].edge[1][0];
        cube[1].edge[2][0] = cube[5].edge[2][0];
        cube[5].edge[0][0] = cube[3].edge[2][2];
        cube[5].edge[1][0] = cube[3].edge[1][2];
        cube[5].edge[2][0] = cube[3].edge[0][2];
        cube[3].edge[2][2] = cube[0].edge[0][0];
        cube[3].edge[1][2] = cube[0].edge[1][0];
        cube[3].edge[0][2] = cube[0].edge[2][0];
        cube[0].edge[0][0] = t1;
        cube[0].edge[1][0] = t2;
        cube[0].edge[2][0] = t3;
        moves.push_back(4);
        return "L";
    }
    string R()
    {
        rotation(cube[2].edge);
        int t1 = cube[1].edge[0][2];
        int t2 = cube[1].edge[1][2];
        int t3 = cube[1].edge[2][2];
        cube[1].edge[0][2] = cube[0].edge[0][2];
        cube[1].edge[1][2] = cube[0].edge[1][2];
        cube[1].edge[2][2] = cube[0].edge[2][2];
        cube[0].edge[0][2] = cube[3].edge[2][0];
        cube[0].edge[1][2] = cube[3].edge[1][0];
        cube[0].edge[2][2] = cube[3].edge[0][0];
        cube[3].edge[2][0] = cube[5].edge[0][2];
        cube[3].edge[1][0] = cube[5].edge[1][2];
        cube[3].edge[0][0] = cube[5].edge[2][2];
        cube[5].edge[0][2] = t1;
        cube[5].edge[1][2] = t2;
        cube[5].edge[2][2] = t3;
        moves.push_back(2);
        return "R";
    }
    string U()
    {
        rotation(cube[5].edge);
        int t1 = cube[1].edge[0][0];
        int t2 = cube[1].edge[0][1];
        int t3 = cube[1].edge[0][2];
        cube[1].edge[0][0] = cube[2].edge[0][0];
        cube[1].edge[0][1] = cube[2].edge[0][1];
        cube[1].edge[0][2] = cube[2].edge[0][2];
        cube[2].edge[0][0] = cube[3].edge[0][0];
        cube[2].edge[0][1] = cube[3].edge[0][1];
        cube[2].edge[0][2] = cube[3].edge[0][2];
        cube[3].edge[0][0] = cube[4].edge[0][0];
        cube[3].edge[0][1] = cube[4].edge[0][1];
        cube[3].edge[0][2] = cube[4].edge[0][2];
        cube[4].edge[0][0] = t1;
        cube[4].edge[0][1] = t2;
        cube[4].edge[0][2] = t3;
        moves.push_back(5);
        return "U";
    }
    string D()
    {
        rotation(cube[0].edge);
        int t1 = cube[1].edge[2][0];
        int t2 = cube[1].edge[2][1];
        int t3 = cube[1].edge[2][2];
        cube[1].edge[2][0] = cube[4].edge[2][0];
        cube[1].edge[2][1] = cube[4].edge[2][1];
        cube[1].edge[2][2] = cube[4].edge[2][2];
        cube[4].edge[2][0] = cube[3].edge[2][0];
        cube[4].edge[2][1] = cube[3].edge[2][1];
        cube[4].edge[2][2] = cube[3].edge[2][2];
        cube[3].edge[2][0] = cube[2].edge[2][0];
        cube[3].edge[2][1] = cube[2].edge[2][1];
        cube[3].edge[2][2] = cube[2].edge[2][2];
        cube[2].edge[2][0] = t1;
        cube[2].edge[2][1] = t2;
        cube[2].edge[2][2] = t3;
        moves.push_back(0);
        return "D";
    }
    string F_()
    {
        //rotation_(cube[1].edge);
        F(); F(); F();
        return "F'";
    }
    string B_()
    {
        //rotation_(cube[3].edge);
        B(); B(); B();
        return "B'";
    }
    string L_()
    {
        //rotation_(cube[4].edge);
        L(); L(); L();
        return "L'";
    }
    string R_()
    {
        //rotation_(cube[2].edge);
        R(); R(); R();
        return "R'";
    }
    string U_()
    {
        //rotation_(cube[5].edge);
        U(); U(); U();
        return "U'";
    }
    string D_()
    {
        //rotation_(cube[0].edge);
        D(); D(); D();
        return "D'";
    }
    string F__()
    {
        F();
        F();
        return "F''";
    }
    string B__()
    {
        B();
        B();
        return "B''";
    }
    string L__()
    {
        L();
        L();
        return "L''";
    }
    string R__()
    {
        R();
        R();
        return "R''";
    }
    string U__()
    {
        U();
        U();
        return "U''";
    }
    string D__()
    {
        D();
        D();
        return "D''";
    }

    void generate()
    {
        int j;
        string tmp = "";
        std::srand(unsigned(std::time(nullptr)));
        for (int i = 0; i < 25; i++)
        {
            j = rand() % 6;
            switch (j)
            {
                case 0:
                    tmp += D();
                    break;
                case 1:
                    tmp += F();
                    break;
                case 2:
                    tmp += R();
                    break;
                case 3:
                    tmp += B();
                    break;
                case 4:
                    tmp += L();
                    break;
                default:
                    tmp += U();
                    break;
            }

        }
        cout << "generate:\n" << tmp << endl;
    }

    void print_current()
    {

        cout << "*****************************************************\n";
        cout << "Current:\n\n";
        cout << "D\n";
        cube[0].print_edge();
        cout << "F\n";
        cube[1].print_edge();
        cout << "R\n";
        cube[2].print_edge();
        cout << "B\n";
        cube[3].print_edge();
        cout << "L\n";
        cube[4].print_edge();
        cout << "U\n";
        cube[5].print_edge();
        cout << "*****************************************************\n";
    }

    string step1()
    {
        string tmp = "";
        int count = 0;

        while (count < 4) {
            if (cube[(0 + 1) % 6].edge[1][1] == cube[(0 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[2][1] == cube[(5 + 1) % 6].edge[1][1]) {
                tmp += F__();
                count = 0;
            }
            else if (cube[(1 + 1) % 6].edge[1][1] == cube[(1 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[1][2] == cube[(5 + 1) % 6].edge[1][1]) {
                tmp += R__();
                count = 0;
            }
            else if (cube[(3 + 1) % 6].edge[1][1] == cube[(3 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[1][0] == cube[(5 + 1) % 6].edge[1][1]) {
                tmp += L__();
                count = 0;
            }
            else if (cube[(2 + 1) % 6].edge[1][1] == cube[(2 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[0][1] == cube[(5 + 1) % 6].edge[1][1]) {
                tmp += B__();
                count = 0;
            }
            else if (cube[(0 + 1) % 6].edge[1][1] == cube[(4 + 1) % 6].edge[2][1] && cube[(0 + 1) % 6].edge[0][1] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += U_();
                tmp += R_();
                tmp += F();
                tmp += R();
                count = 0;
            }
            else if (cube[(1 + 1) % 6].edge[1][1] == cube[(4 + 1) % 6].edge[1][2] && cube[(1 + 1) % 6].edge[0][1] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += U_();
                tmp += B_();
                tmp += R();
                tmp += B();


                count = 0;
            }
            else if (cube[(3 + 1) % 6].edge[1][1] == cube[(4 + 1) % 6].edge[1][0] && cube[(3 + 1) % 6].edge[0][1] == cube[(5 + 1) % 6].edge[1][1]) {


                tmp += U_();
                tmp += F_();
                tmp += L();
                tmp += F();

                count = 0;
            }
            else if (cube[(2 + 1) % 6].edge[1][1] == cube[(4 + 1) % 6].edge[0][1] && cube[(2 + 1) % 6].edge[0][1] == cube[(5 + 1) % 6].edge[1][1]) {


                tmp += U_();
                tmp += L_();
                tmp += B();
                tmp += L();

                count = 0;
            }
            else if (cube[(0 + 1) % 6].edge[1][2] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += F_();
                tmp += U_();
                tmp += F();

                count = 0;
            }
            else if (cube[(1 + 1) % 6].edge[1][2] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += R_();
                tmp += U_();
                tmp += R();

                count = 0;
            }
            else if (cube[(3 + 1) % 6].edge[1][2] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += L_();
                tmp += U_();
                tmp += L();

                count = 0;
            }
            else if (cube[(2 + 1) % 6].edge[1][2] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += B_();
                tmp += U_();
                tmp += B();

                count = 0;
            }
            else if (cube[(0 + 1) % 6].edge[1][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += F();
                tmp += U_();
                tmp += F_();

                count = 0;
            }
            else if (cube[(1 + 1) % 6].edge[1][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += R();
                tmp += U_();
                tmp += R_();

                count = 0;
            }
            else if (cube[(3 + 1) % 6].edge[1][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += L();
                tmp += U_();
                tmp += L_();

                count = 0;
            }
            else if (cube[(2 + 1) % 6].edge[1][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += B();
                tmp += U_();
                tmp += B_();

                count = 0;
            }
            else if (cube[(0 + 1) % 6].edge[2][1] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += F__();
                tmp += U_();
                tmp += F__();

                count = 0;
            }
            else if (cube[(1 + 1) % 6].edge[2][1] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += R__();
                tmp += U_();
                tmp += R__();

                count = 0;
            }
            else if (cube[(3 + 1) % 6].edge[2][1] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += L__();
                tmp += U_();
                tmp += L__();

                count = 0;
            }
            else if (cube[(2 + 1) % 6].edge[2][1] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += B__();
                tmp += U_();
                tmp += B__();

                count = 0;
            }
            else if (cube[(5 + 1) % 6].edge[1][1] == cube[(5 + 1) % 6].edge[0][1] && cube[(0 + 1) % 6].edge[2][1] != cube[(0 + 1) % 6].edge[1][1]) {

                tmp += F__();
                tmp += U_();
                tmp += F__();

                count = 0;
            }
            else if (cube[(5 + 1) % 6].edge[1][1] == cube[(5 + 1) % 6].edge[1][2] && cube[(1 + 1) % 6].edge[2][1] != cube[(1 + 1) % 6].edge[1][1]) {

                tmp += R__();
                tmp += U_();
                tmp += R__();

                count = 0;
            }
            else if (cube[(5 + 1) % 6].edge[1][1] == cube[(5 + 1) % 6].edge[1][0] && cube[(3 + 1) % 6].edge[2][1] != cube[(3 + 1) % 6].edge[1][1]) {

                tmp += L__();
                tmp += U_();
                tmp += L__();

                count = 0;
            }
            else if (cube[(5 + 1) % 6].edge[1][1] == cube[(5 + 1) % 6].edge[2][1] && cube[(2 + 1) % 6].edge[2][1] != cube[(2 + 1) % 6].edge[1][1]) {

                tmp += B__();
                tmp += U_();
                tmp += B__();

                count = 0;
            }
            else {
                tmp += U();
                count++;
            }
        }

        return tmp;
    }

    string step2()
    {
        string tmp = "";
        int count = 0;

        while (count < 4) {
            if (cube[(0 + 1) % 6].edge[0][2] == cube[(5 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[2][2] == cube[(0 + 1) % 6].edge[1][1]
                && cube[(1 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1]) {

                tmp += F_();
                tmp += U_();
                tmp += F();

                count = 0;
            }
            else if (cube[(0 + 1) % 6].edge[0][0] == cube[(0 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[2][0] == cube[(3 + 1) % 6].edge[1][1]
                     && cube[(3 + 1) % 6].edge[0][2] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += L_();
                tmp += U_();
                tmp += L();

                count = 0;
            }
            else if (cube[(2 + 1) % 6].edge[0][0] == cube[(2 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1]
                     && cube[(1 + 1) % 6].edge[0][2] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += R_();
                tmp += U_();
                tmp += R();

                count = 0;
            }
            else if (cube[(3 + 1) % 6].edge[0][0] == cube[(3 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[0][0] == cube[(2 + 1) % 6].edge[1][1]
                     && cube[(2 + 1) % 6].edge[0][2] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += B_();
                tmp += U_();
                tmp += B();

                count = 0;
            }
            else if (cube[(0 + 1) % 6].edge[0][2] == cube[(0 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[2][2] == cube[(1 + 1) % 6].edge[1][1]
                     && cube[(1 + 1) % 6].edge[0][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += R();
                tmp += U();
                tmp += R_();


                count = 0;
            }
            else if (cube[(3 + 1) % 6].edge[0][2] == cube[(3 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[2][0] == cube[(0 + 1) % 6].edge[1][1]
                     && cube[(0 + 1) % 6].edge[0][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += F();
                tmp += U();
                tmp += F_();

                count = 0;
            }
            else if (cube[(1 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[0][2] == cube[(2 + 1) % 6].edge[1][1]
                     && cube[(2 + 1) % 6].edge[0][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += B();
                tmp += U();
                tmp += B_();

                count = 0;
            }
            else if (cube[(2 + 1) % 6].edge[0][2] == cube[(2 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[0][0] == cube[(3 + 1) % 6].edge[1][1]
                     && cube[(3 + 1) % 6].edge[0][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += L();
                tmp += U();
                tmp += L_();

                count = 0;
            }
            else if (cube[(0 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1]
                     && cube[(4 + 1) % 6].edge[2][2] == cube[(5 + 1) % 6].edge[1][1]
                     && cube[(1 + 1) % 6].edge[0][0] == cube[(0 + 1) % 6].edge[1][1]) {



                tmp += R();
                tmp += U_();
                tmp += R_();
                tmp += U__();
                tmp += R();
                tmp += U();
                tmp += R_();



                count = 0;
            }
            else if (cube[(3 + 1) % 6].edge[0][2] == cube[(0 + 1) % 6].edge[1][1]
                     && cube[(4 + 1) % 6].edge[2][0] == cube[(5 + 1) % 6].edge[1][1]
                     && cube[(0 + 1) % 6].edge[0][0] == cube[(3 + 1) % 6].edge[1][1]) {



                tmp += F();
                tmp += U_();
                tmp += F_();
                tmp += U__();
                tmp += F();
                tmp += U();
                tmp += F_();



                count = 0;
            }
            else if (cube[(1 + 1) % 6].edge[0][2] == cube[(2 + 1) % 6].edge[1][1]
                     && cube[(4 + 1) % 6].edge[0][2] == cube[(5 + 1) % 6].edge[1][1]
                     && cube[(2 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1]) {



                tmp += B();
                tmp += U_();
                tmp += B_();
                tmp += U__();
                tmp += B();
                tmp += U();
                tmp += B_();



                count = 0;
            }
            else if (cube[(2 + 1) % 6].edge[0][2] == cube[(3 + 1) % 6].edge[1][1]
                     && cube[(4 + 1) % 6].edge[0][0] == cube[(5 + 1) % 6].edge[1][1]
                     && cube[(3 + 1) % 6].edge[0][0] == cube[(2 + 1) % 6].edge[1][1]) {



                tmp += L();
                tmp += U_();
                tmp += L_();
                tmp += U__();
                tmp += L();
                tmp += U();
                tmp += L_();



                count = 0;
            }
            else if (cube[(0 + 1) % 6].edge[2][2] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += F_();
                tmp += U_();
                tmp += F();


                count = 0;
            }
            else if (cube[(3 + 1) % 6].edge[2][2] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += L_();
                tmp += U_();
                tmp += L();

                count = 0;
            }
            else if (cube[(1 + 1) % 6].edge[2][2] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += R_();
                tmp += U_();
                tmp += R();

                count = 0;
            }
            else if (cube[(2 + 1) % 6].edge[2][2] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += B_();
                tmp += U_();
                tmp += B();

                count = 0;
            }
            else if (cube[(1 + 1) % 6].edge[2][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += F_();
                tmp += U_();
                tmp += F();

                count = 0;
            }
            else if (cube[(0 + 1) % 6].edge[2][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += L_();
                tmp += U_();
                tmp += L();

                count = 0;
            }
            else if (cube[(2 + 1) % 6].edge[2][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += R_();
                tmp += U_();
                tmp += R();

                count = 0;
            }
            else if (cube[(3 + 1) % 6].edge[2][0] == cube[(5 + 1) % 6].edge[1][1]) {

                tmp += B_();
                tmp += U_();
                tmp += B();

                count = 0;
            }
            else if (cube[(5 + 1) % 6].edge[0][0] == cube[(5 + 1) % 6].edge[1][1]
                     && (cube[(0 + 1) % 6].edge[2][0] != cube[(0 + 1) % 6].edge[1][1] || cube[(3 + 1) % 6].edge[2][2] != cube[(3 + 1) % 6].edge[1][1])) {

                tmp += F();
                tmp += U_();
                tmp += F_();

                count = 0;
            }
            else if (cube[(5 + 1) % 6].edge[0][2] == cube[(5 + 1) % 6].edge[1][1]
                     && (cube[(0 + 1) % 6].edge[2][2] != cube[(0 + 1) % 6].edge[1][1] || cube[(1 + 1) % 6].edge[2][0] != cube[(1 + 1) % 6].edge[1][1])) {

                tmp += R();
                tmp += U_();
                tmp += R_();

                count = 0;
            }
            else if (cube[(5 + 1) % 6].edge[2][2] == cube[(5 + 1) % 6].edge[1][1]
                     && (cube[(1 + 1) % 6].edge[2][2] != cube[(1 + 1) % 6].edge[1][1] || cube[(2 + 1) % 6].edge[2][0] != cube[(2 + 1) % 6].edge[1][1])) {

                tmp += B();
                tmp += U_();
                tmp += B_();

                count = 0;
            }
            else if (cube[(5 + 1) % 6].edge[2][0] == cube[(5 + 1) % 6].edge[1][1]
                     && (cube[(2 + 1) % 6].edge[2][2] != cube[(2 + 1) % 6].edge[1][1] || cube[(3 + 1) % 6].edge[2][0] != cube[(3 + 1) % 6].edge[1][1])) {

                tmp += L();
                tmp += U_();
                tmp += L_();

                count = 0;
            }
            else {
                tmp += U();
                count++;
            }
        }

        return tmp;
    }

    string step3()
    {
        string tmp = "";
        int count = 0;
        again3:
        // Part 1
        if (cube[(0 + 1) % 6].edge[1][1] == cube[(0 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[2][1] == cube[(3 + 1) % 6].edge[1][1]) {
            tmp += U_();
            tmp += L_();
            tmp += U();
            tmp += L();
            tmp += U();
            tmp += F();
            tmp += U_();
            tmp += F_();

            count = 0; goto again3;
        }
        else if (cube[(1 + 1) % 6].edge[1][1] == cube[(1 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[1][2] == cube[(0 + 1) % 6].edge[1][1]) {
            tmp += U_();
            tmp += F_();
            tmp += U();
            tmp += F();
            tmp += U();
            tmp += R();
            tmp += U_();
            tmp += R_();

            count = 0; goto again3;
        }
        else if (cube[(2 + 1) % 6].edge[1][1] == cube[(2 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[0][1] == cube[(1 + 1) % 6].edge[1][1]) {
            tmp += U_();
            tmp += R_();
            tmp += U();
            tmp += R();
            tmp += U();
            tmp += B();
            tmp += U_();
            tmp += B_();

            count = 0; goto again3;
        }
        else if (cube[(3 + 1) % 6].edge[1][1] == cube[(3 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[1][0] == cube[(2 + 1) % 6].edge[1][1]) {
            tmp += U_();
            tmp += B_();
            tmp += U();
            tmp += B();
            tmp += U();
            tmp += L();
            tmp += U_();
            tmp += L_();

            count = 0; goto again3;
        }
        else if (cube[(0 + 1) % 6].edge[1][1] == cube[(0 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[2][1] == cube[(1 + 1) % 6].edge[1][1]) {
            tmp += U();
            tmp += R();
            tmp += U_();
            tmp += R_();
            tmp += U_();
            tmp += F_();
            tmp += U();
            tmp += F();

            count = 0; goto again3;
        }
        else if (cube[(3 + 1) % 6].edge[1][1] == cube[(3 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[1][0] == cube[(0 + 1) % 6].edge[1][1]) {
            tmp += U();
            tmp += F();
            tmp += U_();
            tmp += F_();
            tmp += U_();
            tmp += L_();
            tmp += U();
            tmp += L();

            count = 0; goto again3;
        }
        else if (cube[(2 + 1) % 6].edge[1][1] == cube[(2 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[0][1] == cube[(3 + 1) % 6].edge[1][1]) {
            tmp += U();
            tmp += L();
            tmp += U_();
            tmp += L_();
            tmp += U_();
            tmp += B_();
            tmp += U();
            tmp += B();

            count = 0; goto again3;
        }
        else if (cube[(1 + 1) % 6].edge[1][1] == cube[(1 + 1) % 6].edge[0][1] && cube[(4 + 1) % 6].edge[1][2] == cube[(2 + 1) % 6].edge[1][1]) {
            tmp += U();
            tmp += B();
            tmp += U_();
            tmp += B_();
            tmp += U_();
            tmp += R_();
            tmp += U();
            tmp += R();

            count = 0; goto again3;
        }
        else
        {
            // Part 2?
            tmp += U();
            count++;
            if (count < 4)
                goto again3;
        }


        if (cube[(0 + 1) % 6].edge[1][2] != cube[(0 + 1) % 6].edge[1][1] || cube[(1 + 1) % 6].edge[1][0] != cube[(1 + 1) % 6].edge[1][1])
        {
            tmp += U();
            tmp += R();
            tmp += U_();
            tmp += R_();
            tmp += U_();
            tmp += F_();
            tmp += U();
            tmp += F();

            count = 0;
            goto again3;
        }
        else if (cube[(0 + 1) % 6].edge[1][0] != cube[(0 + 1) % 6].edge[1][1] || cube[(3 + 1) % 6].edge[1][2] != cube[(3 + 1) % 6].edge[1][1])
        {
            tmp += U();
            tmp += F();
            tmp += U_();
            tmp += F_();
            tmp += U_();
            tmp += L_();
            tmp += U();
            tmp += L();

            count = 0;
            goto again3;
        }
        else if (cube[(2 + 1) % 6].edge[1][2] != cube[(2 + 1) % 6].edge[1][1] || cube[(3 + 1) % 6].edge[1][0] != cube[(3 + 1) % 6].edge[1][1])
        {

            tmp += U();
            tmp += L();
            tmp += U_();
            tmp += L_();
            tmp += U_();
            tmp += B_();
            tmp += U();
            tmp += B();

            count = 0;
            goto again3;
        }
        else if (cube[(2 + 1) % 6].edge[1][0] != cube[(2 + 1) % 6].edge[1][1] || cube[(1 + 1) % 6].edge[1][2] != cube[(1 + 1) % 6].edge[1][1])
        {

            tmp += U();
            tmp += B();
            tmp += U_();
            tmp += B_();
            tmp += U_();
            tmp += R_();
            tmp += U();
            tmp += R();

            count = 0;
            goto again3;
        }
        else
            return tmp;
    }

    string step4()
    {
        string tmp = "";
        if (cube[(4 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[1][0] == cube[(4 + 1) % 6].edge[1][1]
            && cube[(0 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1]
            && cube[(1 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1])
        {
            tmp += F();
            tmp += U();
            tmp += R();
            tmp += U_();
            tmp += R_();
            tmp += F_();

        }
        else if (cube[(4 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[1][2] == cube[(4 + 1) % 6].edge[1][1]
                 && cube[(0 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1]
                 && cube[(3 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1])
        {
            tmp += L();
            tmp += U();
            tmp += F();
            tmp += U_();
            tmp += F_();
            tmp += L_();
        }
        else if (cube[(4 + 1) % 6].edge[1][0] == cube[(4 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[2][1] == cube[(4 + 1) % 6].edge[1][1]
                 && cube[(2 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1]
                 && cube[(1 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1])
        {
            tmp += R();
            tmp += U();
            tmp += B();
            tmp += U_();
            tmp += B_();
            tmp += R_();
        }
        else if (cube[(4 + 1) % 6].edge[1][2] == cube[(4 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[2][1] == cube[(4 + 1) % 6].edge[1][1]
                 && cube[(2 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1]
                 && cube[(3 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1])
        {
            tmp += B();
            tmp += U();
            tmp += L();
            tmp += U_();
            tmp += L_();
            tmp += B_();
        }
            //
        else if (cube[(4 + 1) % 6].edge[1][0] == cube[(4 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[1][1] == cube[(4 + 1) % 6].edge[1][2]
                 && cube[(0 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1]
                 && cube[(2 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1])
        {
            tmp += F();
            tmp += R();
            tmp += U();
            tmp += R_();
            tmp += U_();
            tmp += F_();
        }
        else if (cube[(4 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1] && cube[(4 + 1) % 6].edge[1][1] == cube[(4 + 1) % 6].edge[2][1]
                 && cube[(1 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1]
                 && cube[(3 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1])
        {
            tmp += R();
            tmp += B();
            tmp += U();
            tmp += B_();
            tmp += U_();
            tmp += R_();
        }
        else if (cube[(0 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1]
                 && cube[(1 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1]
                 && cube[(2 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1]
                 && cube[(3 + 1) % 6].edge[0][1] == cube[(4 + 1) % 6].edge[1][1])
        {
            tmp += F();
            tmp += U();
            tmp += R();
            tmp += U_();
            tmp += R_();
            tmp += F_();
            tmp += R();
            tmp += B();
            tmp += U();
            tmp += B_();
            tmp += U_();
            tmp += R_();
        }
        return tmp;
    }

    string step5()
    {
        string tmp = "";
        // 1
        if (cube[(1 + 1) % 6].edge[0][1] == cube[(0 + 1) % 6].edge[1][1])
        {
            tmp += U();
            tmp += L_();
            tmp += U__();
            tmp += L();
            tmp += U();
            tmp += L_();
            tmp += U();
            tmp += L();
        }
        else if (cube[(3 + 1) % 6].edge[0][1] == cube[(0 + 1) % 6].edge[1][1])
        {
            tmp += U();
            tmp += B_();
            tmp += U__();
            tmp += B();
            tmp += U();
            tmp += B_();
            tmp += U();
            tmp += B();
        }
        else if (cube[(2 + 1) % 6].edge[0][1] == cube[(0 + 1) % 6].edge[1][1])
        {
            tmp += U();
            tmp += R_();
            tmp += U__();
            tmp += R();
            tmp += U();
            tmp += R_();
            tmp += U();
            tmp += R();
            tmp += U();
            tmp += B_();
            tmp += U__();
            tmp += B();
            tmp += U();
            tmp += B_();
            tmp += U();
            tmp += B();
            tmp += U();
            tmp += R_();
            tmp += U__();
            tmp += R();
            tmp += U();
            tmp += R_();
            tmp += U();
            tmp += R();
        }


        // 2
        if (cube[(2 + 1) % 6].edge[0][1] == cube[(1 + 1) % 6].edge[1][1])
        {
            tmp += U();
            tmp += F_();
            tmp += U__();
            tmp += F();
            tmp += U();
            tmp += F_();
            tmp += U();
            tmp += F();
        }
        else if (cube[(3 + 1) % 6].edge[0][1] == cube[(1 + 1) % 6].edge[1][1])
        {
            tmp += U();
            tmp += B_();
            tmp += U__();
            tmp += B();
            tmp += U();
            tmp += B_();
            tmp += U();
            tmp += B();
            tmp += U();
            tmp += L_();
            tmp += U__();
            tmp += L();
            tmp += U();
            tmp += L_();
            tmp += U();
            tmp += L();
            tmp += U();
            tmp += B_();
            tmp += U__();
            tmp += B();
            tmp += U();
            tmp += B_();
            tmp += U();
            tmp += B();
        }


        // 3
        if (cube[(3 + 1) % 6].edge[0][1] == cube[(2 + 1) % 6].edge[1][1])
        {
            tmp += U();
            tmp += R_();
            tmp += U__();
            tmp += R();
            tmp += U();
            tmp += R_();
            tmp += U();
            tmp += R();
        }

        return tmp;
    }

    string step6()
    {
        string tmp = "";
        again6:
        if (
                (cube[(0 + 1) % 6].edge[0][0] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[2][0] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1]) ||

                (cube[(0 + 1) % 6].edge[0][0] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[2][0] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1]) ||

                (cube[(0 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[2][0] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1]) ||

                (cube[(0 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[2][0] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][2] == cube[(0 + 1) % 6].edge[1][1]) ||

                (cube[(0 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[2][0] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][2] == cube[(0 + 1) % 6].edge[1][1]) ||

                (cube[(0 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[2][0] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1]))
        {
            tmp += F_();
            tmp += L_();
            tmp += F();
            tmp += R_();
            tmp += F_();
            tmp += L();
            tmp += F();
            tmp += R();
            goto again6;
        }
        else if (

                (cube[(1 + 1) % 6].edge[0][2] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(2 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1]) ||

                (cube[(1 + 1) % 6].edge[0][2] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(2 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1]) ||

                (cube[(1 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(2 + 1) % 6].edge[0][0] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1]) ||

                (cube[(1 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(2 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][2] == cube[(0 + 1) % 6].edge[1][1]) ||

                (cube[(1 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(2 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][2] == cube[(0 + 1) % 6].edge[1][1]) ||

                (cube[(1 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(2 + 1) % 6].edge[0][0] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1])

                )
        {
            tmp += R_();
            tmp += F_();
            tmp += L_();
            tmp += F();
            tmp += R();
            tmp += F_();
            tmp += L();
            tmp += F();
            goto again6;
        }
        else if (

                (cube[(2 + 1) % 6].edge[0][2] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1]) ||

                (cube[(2 + 1) % 6].edge[0][2] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1]) ||

                (cube[(2 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][0] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1]) ||

                (cube[(2 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][0] == cube[(0 + 1) % 6].edge[1][1]) ||

                (cube[(2 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][0] == cube[(0 + 1) % 6].edge[1][1]) ||

                (cube[(2 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1] &&
                 cube[(3 + 1) % 6].edge[0][0] == cube[(0 + 1) % 6].edge[1][1] &&
                 cube[(4 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1])

                )
        {
            tmp += F_();
            tmp += L_();
            tmp += B_();
            tmp += L();
            tmp += F();
            tmp += L_();
            tmp += B();
            tmp += L();
            goto again6;
        }
        else
        {
            again6_two:
            if (
                    (cube[(0 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][2] == cube[(2 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[2][0] == cube[(4 + 1) % 6].edge[1][1]) ||

                    (cube[(0 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[2][0] == cube[(2 + 1) % 6].edge[1][1]) ||

                    (cube[(0 + 1) % 6].edge[0][0] == cube[(2 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[2][0] == cube[(4 + 1) % 6].edge[1][1]) ||

                    (cube[(0 + 1) % 6].edge[0][0] == cube[(2 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[2][0] == cube[(1 + 1) % 6].edge[1][1]) ||

                    (cube[(0 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[2][0] == cube[(2 + 1) % 6].edge[1][1]) ||

                    (cube[(0 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][2] == cube[(2 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[2][0] == cube[(1 + 1) % 6].edge[1][1])
                    )
            {
                tmp += B_();
                tmp += R_();
                tmp += B();
                tmp += L_();
                tmp += B_();
                tmp += R();
                tmp += B();
                tmp += L();
                goto again6_two;
            }
            else if (

                    (cube[(2 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][0] == cube[(2 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1]) ||

                    (cube[(2 + 1) % 6].edge[0][2] == cube[(1 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[0][0] == cube[(2 + 1) % 6].edge[1][1]) ||

                    (cube[(2 + 1) % 6].edge[0][2] == cube[(2 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1]) ||

                    (cube[(2 + 1) % 6].edge[0][2] == cube[(2 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1]) ||

                    (cube[(2 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[0][0] == cube[(2 + 1) % 6].edge[1][1]) ||

                    (cube[(2 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1] &&
                     cube[(3 + 1) % 6].edge[0][0] == cube[(2 + 1) % 6].edge[1][1] &&
                     cube[(4 + 1) % 6].edge[0][0] == cube[(1 + 1) % 6].edge[1][1])

                    )
            {
                tmp += L_();
                tmp += B_();
                tmp += R_();
                tmp += B();
                tmp += L();
                tmp += B_();
                tmp += R();
                tmp += B();
                goto again6_two;
            }
        }
        return tmp;
    }

    bool is_solved()
    {
        for (int k = 0; k < 3; k++)
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (cube[k].edge[i][j] != color[k])
                        return false;
        return true;
    }
    string step7()
    {
        string tmp = "";
        if (cube[(1 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1])
        {
            tmp += F_();
            tmp += R();
            tmp += F();
            tmp += R_();
            tmp += F_();
            tmp += R();
            tmp += F();
            tmp += R_();
        }
        else if (cube[(0 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1])
        {
            tmp += R();
            tmp += F_();
            tmp += R_();
            tmp += F();
            tmp += R();
            tmp += F_();
            tmp += R_();
            tmp += F();
        }
        else
        {
            tmp += U();
        }

        for (int i = 0; i < 3; ++i) {
            if (cube[(1 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1])
            {
                tmp += F_();
                tmp += R();
                tmp += F();
                tmp += R_();
                tmp += F_();
                tmp += R();
                tmp += F();
                tmp += R_();
            }
            else if (cube[(0 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1])
            {
                tmp += R();
                tmp += F_();
                tmp += R_();
                tmp += F();
                tmp += R();
                tmp += F_();
                tmp += R_();
                tmp += F();
            }
            tmp += U();
        }

        if (cube[(1 + 1) % 6].edge[0][0] == cube[(4 + 1) % 6].edge[1][1])
        {
            tmp += F_();
            tmp += R();
            tmp += F();
            tmp += R_();
            tmp += F_();
            tmp += R();
            tmp += F();
            tmp += R_();
        }
        else if (cube[(0 + 1) % 6].edge[0][2] == cube[(4 + 1) % 6].edge[1][1])
        {
            tmp += R();
            tmp += F_();
            tmp += R_();
            tmp += F();
            tmp += R();
            tmp += F_();
            tmp += R_();
            tmp += F();
        }

        int count = 0;
        while (!is_solved() && count < 6)
        {
            tmp += U();
            count++;
        }
        if (count == 6)
            return tmp + "\nNOT CORRECT!!";
        else
            return tmp;
    }

    string solve()
    {
        //step1
        s = "STEP 1\n";
        s += step1() + "\n";
        //step2
        s += "STEP 2\n";
        s += step2() + "\n";
        //step3
        s += "STEP 3\n";
        s += step3() + "\n";
        //step4
        s += "STEP 4\n";
        s += step4() + "\n";
        //step5
        s += "STEP 5\n";
        s += step5() + "\n";
        //step6
        s += "STEP 6\n";
        s += step6() + "\n";
        //step7
        s += "STEP 7\n";
        s += step7() + "\n";

        //cout << s;
        return s;
    }
    bool is_correct()
    {
        Cube c(*this);
        c.solve();
        if (c.is_solved())
            return true;
        else
            return false;
    }

    void clear()
    {
        moves.clear();
        //shuffle_moves.clear();
        for (int k = 0; k < 6; ++k)
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    cube[k].edge[i][j] = k;
    }
};

/*
int main()
{
	Cube c;
	
	c.D()
	c.F();
	c.R();
	c.B();
	c.L();
	c.U();
	c.U_();
	c.L_();
	c.B_();
	c.R_();
	c.F_();
	c.D_();
	c.print_current();
	

	c.generate();
	c.print_current();
	cout << "is correct: " << c.is_correct() << "\n";
	cout << "solution: \n" << c.solve();
	cout << "is correct: " << c.is_correct() << "\n";
	c.print_current();
	c.read("input.txt");
	c.print_current();
	cout << "is correct: " << c.is_correct() << "\n";
	cout << "solution: \n" << c.solve();
	c.write("output.txt");

	
	int i = 0;
	while (c.is_solved())
	{
		c.generate();
		c.solve();
		cout << i << endl << endl;
		i++;
	}
	
	system("pause");
	return 0;
}
*/
/*
in file input and output in format:
		  .............
		  . 00  01 02 .
		  . 10 (5) 12 .
		  . 20  21 22 .
...............................................
00  01 02 . 00  01 02 . 00  01 02 . 00  01 02 .
10 (4) 12 . 10 (1) 12 . 10 (2) 12 . 10 (3) 12 .
20  21 22 . 20  21 22 . 20  21 22 . 20  21 22 .
...............................................
		  . 00  01 02 .
		  . 10 (0) 12 .
		  . 20  21 22 .
		  .............

where
(0) - D
(1) - F
(2) - R
(3) - B
(4) - L
(5) - U
*/