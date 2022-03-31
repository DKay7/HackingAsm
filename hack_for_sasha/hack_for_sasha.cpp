#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "default_hash_functions.h"
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define EPSILON 1e-7

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const int ROOTS_ARR_LEN = 100;
const int MAX_NUM_ROOTS = 8;
bool already_checked_roots[ROOTS_ARR_LEN];
bool WAS_PREVIOUS_PASSWORD_ROOT = true;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int PASSW_COUNTER = 0;

const int INCREASE_COEFF    = 3;
const int TARGET_PASSW_NUMS = 424242 / INCREASE_COEFF;
const uint64_t HASH_PASSW_NOT_ABOBA = 2741087425025687488;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintAccess (bool is_acces, int key);
bool AskPassword (int* call_counter);
bool Shiza (int num);
bool CheckPolynomRoot (int x);
bool WasAllRootsFound ();
bool CheckPasswordLengthByPoly (char* password);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{   
    int call_counter = 0;
    while (!AskPassword (&call_counter));
    // 0 -- open password
    // 1 -- input wrong password 424242 times
    // 2 -- input passwordes same lens as polynonial roots

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintAccess (bool is_acces, int key)
{   
    if (is_acces && key == -1)
        printf ("Access granted!\n");
    
    if (is_acces && key == 0)
        printf ("Ну это была самая простая, удачи в поисках следующих!\n");

    else if (is_acces && key == 1)
        printf ("Заюзал первую уязвимость, поздравляю!\n");

    else if (is_acces && key == 2)
        printf ("Заюзал вторую уязвимость, ниче ты гений!\n");

    else
        printf ("Sorry, wrong password!\n");
    
    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool AskPassword (int* call_counter)
{   
    char* passw = NULL;
    printf ("Введите пароль: ");
    scanf ("%ms",  &passw);
    
    (*call_counter) += 1;
    int local_call_counter = (*call_counter);

    // 0th vulnerability
    if (strcmp (passw, "hackers_password") == 0)
    {
        PrintAccess (true, 0);
        free (passw);
        return true;
    }

    // poly roots 2nd vulnerability
    if (CheckPasswordLengthByPoly (passw))
    {
        PrintAccess (true, 2);
        free (passw);
        return true;
    }

    // shiza (1st vulnerability)
    if (local_call_counter % INCREASE_COEFF == 0)
        PASSW_COUNTER += 1;

    if (bool result = Shiza (PASSW_COUNTER))
    {
        PrintAccess (result, 1);
        free (passw);
        return true;
    }

    // check real password
    // definatly !not aboba
    if (str_hash (passw) == HASH_PASSW_NOT_ABOBA)
    {   
        PrintAccess (true, -1);
        free (passw);
        return true;
    }

    else
        PrintAccess (false, 0);

    free (passw);
    return false;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool Shiza (int num)
{   
    int shiza_useless = 0;
    switch (num)
    {   
        case TARGET_PASSW_NUMS - 3:
            shiza_useless += 7;
            return false;

        case TARGET_PASSW_NUMS - 2:
            shiza_useless += 6;
            return false;

        case TARGET_PASSW_NUMS - 1:
            shiza_useless += 5;
            return false;

        case TARGET_PASSW_NUMS:
            shiza_useless += 4;
            return true;

        case TARGET_PASSW_NUMS + 1:
            shiza_useless += 3;
            return false;

        case TARGET_PASSW_NUMS + 2:
            shiza_useless += 2;
            return false;

        case TARGET_PASSW_NUMS + 3:
            shiza_useless += 1;
            return false;

        default:
            return false;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool CheckPolynomRoot (int x)
{   
    double result = + 1.0 * pow (x, 8)+ -134.0 * pow (x, 7)+ 7112.0 * pow (x, 6)+ -192530.0 * pow (x, 5)+ 2852171.0 * pow (x, 4)+ -22906328.0 * pow (x, 3)+ 91789900.0 * pow (x, 2)+ -152270832.0 * pow (x, 1)+ 80720640.0 * pow (x, 0);

    printf ("\nX: %d | RESULT %lf | IS LESS EPS %d\n", x, result, fabs (result) < EPSILON);

    if (fabs (result) < EPSILON)
        return true;

    return false;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool CheckPasswordLengthByPoly (char* password)
{   
    int pass_len = strlen (password);
    if (CheckPolynomRoot (pass_len) && pass_len < ROOTS_ARR_LEN && WAS_PREVIOUS_PASSWORD_ROOT)
    {
        WAS_PREVIOUS_PASSWORD_ROOT = true;
        already_checked_roots[pass_len] = true;
        return WasAllRootsFound ();
    }

    WAS_PREVIOUS_PASSWORD_ROOT = false;
    return false;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool WasAllRootsFound ()
{   
    int roots_counter = 0;
    for (int i = 0; i < ROOTS_ARR_LEN; i++)
    {   
        if (already_checked_roots[i])
            roots_counter += 1;
    }

    if (roots_counter == MAX_NUM_ROOTS)
        return true;
    
    return false;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
