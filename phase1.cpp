#include<iostream>
#include<fstream>
using namespace std;

class OS
{
    char M[100][4], IR[4], R[4], buffer[40];
    int IC, SI;
    bool Toggle;

public:
    void INIT(), LOAD(), STARTEXECUTION(), EXECUTEUSERPROGRAM(), MOS(), READ(), WRITE(), TERMINATE();
    fstream Input, Output;
};

void OS::INIT()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = ' ';
        }
    }
    IR[4] = '\0';
    R[4] = '\0';
    Toggle = false;
}

void OS::LOAD()
{
    int x = 0;
    do
    {
        for (int i = 0; i < 40; i++)
        {
            buffer[i] = '\0';
        }

        Input.getline(buffer, 41);

        if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            INIT();
        }
        else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            STARTEXECUTION();
        }
        else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            x = 0;
            continue;
        }
        else
        {
            int b = 0;

            bool isInstruction = (buffer[0] == 'L' && buffer[1] == 'R') || (buffer[0] == 'S' && buffer[1] == 'R') ||
                                 (buffer[0] == 'C' && buffer[1] == 'R') || (buffer[0] == 'B' && buffer[1] == 'T') ||
                                 (buffer[0] == 'G' && buffer[1] == 'D') || (buffer[0] == 'P' && buffer[1] == 'D') ||
                                 (buffer[0] == 'H');

            if (isInstruction)
            {
                for (; x < 100; x++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        M[x][j] = buffer[b];
                        b++;
                    }

                    if (b == 40 || buffer[b] == ' ' || buffer[b] == '\n')
                    {
                        x++;
                        break;
                    }
                }

            }

        }

    } while (!Input.eof());

    for (int i = 0; i < 100; i++)
    {
        cout << "M[" << i << "]: ";
        for (int j = 0; j < 4; j++)
        {
            cout << M[i][j];
        }
        cout << endl;
    }

}




void OS::STARTEXECUTION()
{
    IC = 0;
    EXECUTEUSERPROGRAM();
}

void OS::EXECUTEUSERPROGRAM()
{
    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            IR[i] = M[IC][i];
        }
        IC++;

        if (IR[0] == 'L' && IR[1] == 'R')
        {
            int add = IR[2] - '0';
            add = (add * 10) + (IR[3] - '0');

            for (int i = 0; i < 4; i++)
                R[i] = M[add][i];
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            int add = IR[2] - '0';
            add = (add * 10) + (IR[3] - '0');

            for (int i = 0; i < 4; i++)
                M[add][i] = R[i];
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            int flag = 0;
            int add = IR[2] - '0';
            add = (add * 10) + (IR[3] - '0');

            for (int i = 0; i < 4; i++) {
                if (R[i] != M[add][i])
                    flag = 1;
            }

            if (flag == 1)
                Toggle = false;
            else
                Toggle = true;
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            int add = IR[2] - '0';
            add = (add * 10) + (IR[3] - '0');
            if (Toggle == true)
                IC = add;
        }
        else if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            MOS();
            break;
        }
    }
}

void OS::MOS()
{
    switch (SI)
    {
    case 1:
        READ();
        break;
    case 2:
        WRITE();
        break;
    case 3:
        TERMINATE();
        break;
    }
}

void OS::READ() {
    for (int i = 0; i < 40; i++) {
        buffer[i] = '\0';
    }

    Input.getline(buffer, 41);

    int b = 0;
    int n = (IR[2] - '0') * 10 + (IR[3] - '0');

    for (int l = 0; l < 10; l++) {
        for (int j = 0; j < 4; j++) {
            M[n][j] = buffer[b];
            b++;
        }
        n++;
    }

    if (M[IR[2] - '0'][IR[3] - '0'] == '$' && M[IR[2] - '0'][IR[3] - '0' + 1] == 'E' && M[IR[2] - '0'][IR[3] - '0' + 2] == 'N' && M[IR[2] - '0'][IR[3] - '0' + 3] == 'D') {
        cout << "End of data encountered. Aborting." << endl;
    }

    SI = 0;
}

void OS::WRITE() {
    for (int i = 0; i < 40; i++) {
        buffer[i] = '\0';
    }

    int b = 0;
    int n = (IR[2] - '0') * 10 + (IR[3] - '0');

    for (int l = 0; l < 10; l++) {
        for (int j = 0; j < 4; j++) {
            buffer[b] = M[n][j];
            b++;
        }
        n++;
    }

    Output << buffer << endl;
    SI = 0;
}


void OS::TERMINATE()
{
    Output << "\n";
    Output << "\n";
    SI = 0;
}

int main()
{
    OS os;
    os.Input.open("job1ALL.txt", ios::in);
    os.Output.open("job1ALL_op.txt", ios::out);
    os.LOAD();
    os.Input.close();
    os.Output.close();
    return 0;
}



/*
$AMJ010200210001
GD30LR36SR40LR35SR41LR34SR42LR33SR43LR32
SR44LR31SR45LR30SR46LR39SR47SR38SR49PD40
H   
$DTA
AMA  PANANAL A CPLANN A A MA
$END0102
$AMJ020100120003
GD20LR20GD30CR33BT07GD40PD40PD20PD30GD40
PD40H   
$DTA
HOPE FOR IT
THERE IS NO HOPE
BUT STILL HOPE
$END0201
$AMJ000300170007
GD20PD20GD30PD30GD40LR40SR20PD20PD30GD40
LR40SR20PD20PD30GD50PD50H   
$DTA
3 LITTLE PIGS WENT TO OS CLASS.
THE WOLF ATE ONE!
2 LI
1 LI
CLASS DISMISSED!
$END0003
$AMJ020200160005
GD20PD20LR20SR30SR31PD30SR40SR41SR42PD40
SR50SR51PD50SR60PD60H   
$DTA
*
$END0202
$AMJ000700200002
GD50LR50SR67LR51SR66LR52SR65LR53SR64LR54
SR63LR55SR62LR56SR61LR57SR60PD50PD60H   
$DTA
   N   U   T   R   A   F   I   N
$END0007
$AMJ030100100003
GD20PD20GD30PD30LR20CR30BT10GD40PD40H   
$DTA
VIT IS GOOD
VIIT IS GOOD
BOTH ARE SISTER INSTITUTES
$END0301
$AMJ030200080003
GD20PD20GD30PD30LR30SR20PD20H   
$DTA
CAT CAN EAT RAT
RAT CAN NOT EAT CAT
$END0302
$AMJ010100040001
GD20LR22SR25PD20H
$DTA
I LIKE THIS PEN OF  
$END0101
$AMJ010200070002
GD20LR26CR20BT06GD30PD30PD20H
$DTA
RAM  IS OLDER THAN  SHRIRAM 
NOT IN EXISTANCE
$END0102
$AMJ040100120004
GD20PD20GD30PD30GD40GD50LR20CR30BT10PD40
PD50H
$DTA
AB CD
ACD
DO NOT
MATCH
$END0401
$AMJ040300130004
GD20GD30GD40GD50LR20CR30BT09PD50HPD40H
$DTA
VIT
VIIT
SAME
NOTSAME
$END0403
$AMJ040200130004
GD20PD20GD30LR30SR20PD20GD40PD40GD50LR50
SR20PD20H   
$DTA
   RAT
   S
   ON
   M
$END0402----
*/
