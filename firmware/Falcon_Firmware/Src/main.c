/******************************************************************************
 * Project Falcon
 * File: main.c
 * Description: Minimal application entry point.
 ******************************************************************************/

#include "app.h"
#include "self_test.h"

int main(void)
{
    if (!self_test_run())
    {
        while (1)
        {
        }
    }

    app_init();

    while (1)
    {
        app_run();
    }
}
