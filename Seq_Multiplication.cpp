#include <iostream>
#include <string>

using namespace std;

string addition(string A, string B)
{
    int la = A.length();
    int lb = B.length();

    string C;

    int n = max(la, lb) + 1;

    int carry[n];
    for (int i = 0; i < n; i++)
    {
        carry[i] = 0;
    }

    for (int i = 0; i < min(la, lb); i++)
    {
        if (carry[i] == 0)
        {
            if ((A[la - 1 - i] == '1' && B[lb - 1 - i] == '0') || (A[la - 1 - i] == '0' && B[lb - 1 - i] == '1'))
            {
                C = '1' + C;
                carry[i + 1] = 0;
            }
            else if (A[la - 1 - i] == '0' && B[lb - 1 - i] == '0')
            {
                C = '0' + C;
                carry[i + 1] = 0;
            }
            else
            {
                C = '0' + C;
                carry[i + 1] = 1;
            }
        }
        else
        {
            if ((A[la - 1 - i] == '1' && B[lb - 1 - i] == '0') || (A[la - 1 - i] == '0' && B[lb - 1 - i] == '1'))
            {
                C = '0' + C;
                carry[i + 1] = 1;
            }
            else if (A[la - 1 - i] == '0' && B[lb - 1 - i] == '0')
            {
                C = '1' + C;
                carry[i + 1] = 0;
            }
            else
            {
                C = '1' + C;
                carry[i + 1] = 1;
            }
        }
    }
    string nw;
    if (la > lb)
    {
        nw = A;
    }
    if (lb > la)
    {
        nw = B;
    }
    for (int i = min(la, lb); i < max(la, lb); i++)
    {
        if (carry[i] == 0)
        {
            if (nw[(nw.length()) - 1 - i] == '0')
            {
                C = '0' + C;
            }
            else
            {
                C = '1' + C;
            }
        }
        else
        {
            if (nw[(nw.length()) - 1 - i] == '0')
            {
                C = '1' + C;
            }
            else
            {
                C = '0' + C;
                carry[i + 1] = 1;
            }
        }
    }
    if (carry[max(la, lb)] == 1)
    {
        C = '1' + C;
    }

    return C;
}

string rshift(string A, string B)
{
    string str1 = A;
    string str2 = B;

    for (int i = 0; i < str2.length(); i++)
    {
        str2[str2.length() - 1 - i] = str2[str2.length() - 2 - i];
    }
    str2[0] = str1[str1.length() - 1];

    return str2;
}

string dec_to_bin(int Dec)
{
    int d = Dec;
    string bin;

    while (d / 2 != 0)
    {
        if (d % 2 == 0)
        {
            bin = "0" + bin;
        }
        else
        {
            bin = "1" + bin;
        }
        d = d / 2;
    }

    bin = "1" + bin;

    return bin;
}

int main()
{
    cout << "--------PERFORMING SEQUENTIAL MULTIPLICATION--------" << endl;

    string M; // multiplicand
    string Q; // multiplier
    string A, nwA;
    string product;
    string carry = "0";
    int dec;

    cout << "\nEnter '1' - if you want to enter in Decimal numbers,";
    cout << "\nEnter '2' - if you want to enter in Binary Numbers, ";
    cout << "\nEnter your choice : ";
    int opt;
    cin >> opt;

    if (opt == 1)
    {
        cout << "\nEnter the Multiplicand (M) in Decimal form : ";
        cin >> dec;
        M = dec_to_bin(dec);

        cout << "Enter the Multiplier (Q) in binary form : ";
        cin >> dec;
        Q = dec_to_bin(dec);
    }
    else if (opt == 2)
    {
        cout << "\nEnter the Multiplicand (M) in binary form : ";
        cin >> M;

        cout << "Enter the Multiplier (Q) in binary form : ";
        cin >> Q;
    }
    else
    {
        cout << "\nInvalid input !";
        return 0;
    }

    for (int i = 0; i < M.length(); i++)
    {
        if (M[i] != '0' && M[i] != '1')
        {
            cout << "Please enter only Binary numbers ! " << endl;
            return 0;
        }
    }
    for (int i = 0; i < Q.length(); i++)
    {
        if (Q[i] != '0' && Q[i] != '1')
        {
            cout << "Please enter only Binary numbers !" << endl;
            return 0;
        }
    }

    cout << "\nEntered values are, \n1. Multiplicand(M) : " << M << "\n2. Multiplier(Q) : " << Q << endl;

    if (M.length() != Q.length())
    {
        if (M.length() > Q.length())
        {
            int diff = M.length() - Q.length();

            for (int i = 0; i < diff; i++)
            {
                Q = "0" + Q;
            }
        }
        else
        {
            int diff = Q.length() - M.length();

            for (int i = 0; i < diff; i++)
            {
                M = "0" + M;
            }
        }
    }

    string add = addition(M, Q);

    cout << "Binary addition of M and Q is :" << add << endl;

    for (int i = 0; i < M.length(); i++)
    {
        A = '0' + A;
    }
    cout << "\nInitial Configuration: " << endl;
    cout << "M : " << M << " | C:" << carry << " | A: " << A << " | Q: " << Q << endl;

    for (int i = 0; i < (M.length()); i++)
    {
        cout << "\n"
             << i + 1 << "th iteration" << endl;
        if (Q[Q.length() - 1] == '1')
        {
            nwA = addition(A, M);

            if (nwA.length() > A.length())
            {
                carry = "1";
                for (int i = 0; i < A.length(); i++)
                {
                    A[i] = nwA[i + 1];
                }
            }
            else
            {
                carry = "0";
                A = nwA;
            }
            cout << " Adding A and M :-" << endl;
            cout << " M : " << M << " | C:" << carry << " | A: " << A << " | Q: " << Q << endl;
            Q = rshift(A, Q);
            A = rshift(carry, A);
            carry = "0";
            cout << " Right Shifting C, A and Q :-" << endl;
            cout << " M : " << M << " | C:" << carry << " | A: " << A << " | Q: " << Q << endl;
        }
        else
        {
            Q = rshift(A, Q);
            A = rshift(carry, A);
            cout << " Right Shifting C, A and Q :-" << endl;
            cout << " M : " << M << " | C:" << carry << " | A: " << A << " | Q: " << Q << endl;
        }
        carry = "0";
    }

    cout << "\nFinal Configuration : "
         << "\n M : " << M << " | C:" << carry << " | A: " << A << " | Q: " << Q << endl;

    product = A + " " + Q;
    cout << "\nProduct of M and Q is : " << product << "\n"
         << endl;

    return 0;
}