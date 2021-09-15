#include <iostream>
#include <windows.h>
#include <cstdio>
#include <vector>

#include <RNS.h>

using namespace std;

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int n = -1;
    int m = -1;
    bool base_ready = false;
    int *baza;
    Base base;

    int nums[5];

    char key = 0;
    int num;
    while(key != 'q' && key != 'Q')
    {
        system("cls");
        SetConsoleTextAttribute(hConsole, 6);
        cout << "                                       Residue number system                                       " << endl;
        SetConsoleTextAttribute(hConsole, 7);
        cout << "---------------------------------------------------------------------------------------------------" << endl;
        SetConsoleTextAttribute(hConsole, 3);
        cout << "   Button 's' - set base                                                                           " << endl;
        cout << "   Button 'c' - create number from decimal system                                                  " << endl;
        cout << "   Button 'f' - create number from RNS representation                                              " << endl;
        cout << "   Button 'd' - operate on the numbers                                                             " << endl;
        cout << "   Button 'q' - exit                                                                               " << endl;

        SetConsoleTextAttribute(hConsole, 7);
        cout << "---------------------------------------------------------------------------------------------------" << endl;
        if(n == -1)
        {
            cout << "base not specifed yet" << endl;
        }
        else
        {
            cout << "base: [ ";
            for(int i = 0; i<n; i++)
                cout << baza[i] << " ";
            cout << "]" << endl;
        }
        for(int i = 0; i<5; i++)
        {
            cout << "number " << i+1;
            if(m < i)
                cout << " not specifed yet" << endl;
            else
            {
                RNS x = RNS(&base, nums[i]);
                cout << " = " << x << " = " << x.to_decimal() << endl;
            }

        }

        key = getchar();

        if(key == 's' || key == 'S')
        {
            if(base_ready)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "You have already set base!" << endl;
                system("pause");
                SetConsoleTextAttribute(hConsole, 7);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 13);
                cout << "Specify the base length." << endl;
                SetConsoleTextAttribute(hConsole, 7);
                cin >> n;
                base_ready = true;
                if(n<2)
                {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "Bad base length!" << endl;
                    system("pause");
                    SetConsoleTextAttribute(hConsole, 7);
                    exit(0);
                }

                baza = new int[n];
                SetConsoleTextAttribute(hConsole, 13);
                cout << "Specify " << n << " relatively prime numbers!" << endl;
                SetConsoleTextAttribute(hConsole, 7);
                for(int i = 0; i<n; i++)
                {
                    cin >> baza[i];
                }

                if(base.base_init(baza, n) == -1)
                {
                    base = Base(baza, n);
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "Bad numbers!" << endl;
                    system("pause");
                    SetConsoleTextAttribute(hConsole, 7);
                    exit(0);
                }
                SetConsoleTextAttribute(hConsole, 2);
                cout << "Base initialized correctly!" << endl;
                system("pause");
                SetConsoleTextAttribute(hConsole, 7);
            }

        }
        else if(key == 'c' || key == 'C')
        {
            if(!base_ready)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "Firstly, set the base!" << endl;
                system("pause");
                SetConsoleTextAttribute(hConsole, 7);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 13);
                cout << "Specify the number in decimal system." << endl;
                SetConsoleTextAttribute(hConsole, 7);
                cin >> num;
                m++;
                if(m < 5)
                {
                    nums[m] = num;
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "You have already defined 5 numbers!" << endl;
                    system("pause");
                    SetConsoleTextAttribute(hConsole, 7);
                }


            }
        }
        else if(key == 'f' || key == 'F')
        {
            if(!base_ready)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "Firstly, set the base!" << endl;
                system("pause");
                SetConsoleTextAttribute(hConsole, 7);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 13);
                cout << "Specify n consecutive numbers!" << endl;
                SetConsoleTextAttribute(hConsole, 7);
                int repr[n];
                for(int i = 0; i<n; i++)
                    cin >> repr[i];
                RNS y = RNS(&base, repr);
                m++;
                nums[m] = y.to_decimal();
            }

        }
        else if(key == 'd' ||  key== 'D')
        {
            SetConsoleTextAttribute(hConsole, 13);
            cout << "Specify operation:" << endl;
            cout << "--> addition -  'a'" << endl;
            cout << "--> subtraction -  's'" << endl;
            cout << "--> multiplication  -  'm'" << endl;
            cout << "--> division -  'd'" << endl;
            int x1,x2;
            char c;
            cin >> c;
            if(c == 'a' || c == 'A')
            {
                cout << "x1 + x2 = " << endl;
                cout << "Specify the numer of the number x1!" << endl;
                cin >> x1;
                cout << "Specify the numer of the number x2!" << endl;
                cin >> x2;
                x1--;
                x2--;
                if(x1 >= 0 && x1 <= m && x2 >= 0 && x2 <= m)
                {
                    SetConsoleTextAttribute(hConsole, 6);
                    RNS X1 = RNS(&base, nums[x1]);
                    RNS X2 = RNS(&base, nums[x2]);
                    RNS X3 = X1+X2;
                    cout << "x1 + x2 = " << X1 << " + " << X2 << " = " << X3 << endl;
                    cout << "x1 + x2 = " << X1.to_decimal() << " + " << X2.to_decimal() << " = " << X3.to_decimal() << endl;
                    system("pause");
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "Wrong numers or not specified numbers!" << endl;
                    SetConsoleTextAttribute(hConsole, 7);
                    system("pause");
                }

            }
            else if(c == 's' || c == 'S')
            {
                cout << "x1 - x2 = " << endl;
                cout << "Specify the numer of the number x1!" << endl;
                cin >> x1;
                cout << "Specify the numer of the number x2!" << endl;
                cin >> x2;
                x1--;
                x2--;
                if(x1 >= 0 && x1 <= m && x2 >= 0 && x2 <= m)
                {
                    SetConsoleTextAttribute(hConsole, 6);
                    RNS X1 = RNS(&base, nums[x1]);
                    RNS X2 = RNS(&base, nums[x2]);
                    RNS X3 = X1-X2;
                    cout << "x1 - x2 = " << X1 << " - " << X2 << " = " << X3 << endl;
                    cout << "x1 - x2 = " << X1.to_decimal() << " - " << X2.to_decimal() << " = " << X3.to_decimal() << endl;
                    system("pause");
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "Wrong numers or not specified numbers!" << endl;
                    SetConsoleTextAttribute(hConsole, 7);
                    system("pause");
                }
            }
            else if(c == 'm' || c == 'M')
            {
                cout << "x1 * x2 = " << endl;
                cout << "Specify the numer of the number x1!" << endl;
                cin >> x1;
                cout << "Specify the numer of the number x2!" << endl;
                cin >> x2;
                x1--;
                x2--;
                if(x1 >= 0 && x1 <= m && x2 >= 0 && x2 <= m)
                {
                    SetConsoleTextAttribute(hConsole, 6);
                    RNS X1 = RNS(&base, nums[x1]);
                    RNS X2 = RNS(&base, nums[x2]);
                    RNS X3 = X1*X2;
                    cout << "x1 * x2 = " << X1 << " * " << X2 << " = " << X3 << endl;
                    cout << "x1 * x2 = " << X1.to_decimal() << " * " << X2.to_decimal() << " = " << X3.to_decimal() << endl;
                    system("pause");
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "Wrong numers or not specified numbers!" << endl;
                    SetConsoleTextAttribute(hConsole, 7);
                    system("pause");
                }
            }
            else if(c == 'd' || c == 'D')
            {
                cout << "x1 / x2 = " << endl;
                cout << "Specify the numer of the number x1!" << endl;
                cin >> x1;
                cout << "Specify the numer of the number x2!" << endl;
                cin >> x2;
                x1--;
                x2--;
                if(x1 >= 0 && x1 <= m && x2 >= 0 && x2 <= m)
                {
                    SetConsoleTextAttribute(hConsole, 6);
                    RNS X1 = RNS(&base, nums[x1]);
                    RNS X2 = RNS(&base, nums[x2]);
                    RNS X3 = X1/X2;
                    cout << "x1 / x2 = " << X1 << " / " << X2 << " = " << X3 << endl;
                    cout << "x1 / x2 = " << X1.to_decimal() << " / " << X2.to_decimal() << " = " << X3.to_decimal() << endl;
                    system("pause");
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "Wrong numers or not specified numbers!" << endl;
                    SetConsoleTextAttribute(hConsole, 7);
                    system("pause");
                }
            }
            else
                system("pause");
            SetConsoleTextAttribute(hConsole, 7);
        }
    }


    return 0;
}
