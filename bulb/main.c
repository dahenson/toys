#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "energy_math.h"

static const char *PROG_NAME = "bulb";

void print_help_message(void) {
    printf("usage: %s [-hapw]\n", PROG_NAME);
    printf("\t-h        print the help message\n");
    printf("\t-a hours  the average hours the bulb is on\n");
    printf("\t-b bulbs  the number of bulbs in the fixture (default: 1)\n");
    printf("\t-l life   expected lifespan in hours (default: 11000)\n");
    printf("\t-p price  the price per kWh\n");
    printf("\t-w watts  the wattage of the bulb\n\n");
}

int main(int argc, char *const argv[]) {
    int opt;

    double
        hours = 0,
        watts = 0,
        price = 0,
        bulbs = 1, /* Default to 1 bulb per fixture */
        kwh = 0,
        cpd = 0,
        life = 11000;

    char *badchar;

    /* Running the program without arguments won't do anything. */
    if (argc == 1) {
        print_help_message();
        exit(0);
    }

    while ((opt = getopt(argc, argv, ":ha:b:l:p:w:")) != -1) {
        switch (opt){
            case 'a':
                hours = strtod(optarg, &badchar);

                if (*badchar != '\0') {
                    printf("error: hours should be a number\n");
                    exit(1);
                }
                break;
            case 'b':
                bulbs = strtod(optarg, &badchar);

                if (*badchar != '\0') {
                    printf("error: bulbs should be a number\n");
                    exit(1);
                }
                break;
            case 'l':
                life = strtod(optarg, &badchar);

                if (*badchar != '\0') {
                    printf("error: life should be a number\n");
                    exit(1);
                }
                break;
            case 'p':
                price = strtod(optarg, &badchar);

                if (*badchar != '\0') {
                    printf("error: price should be a number\n");
                    exit(1);
                }
                break;
            case 'w':
                watts = strtod(optarg, &badchar);

                if (*badchar != '\0') {
                    printf("error: watts should be a number\n");
                    exit(1);
                }
                break;
            case 'h':
                print_help_message();
                exit(0);
            case '?':
                print_help_message();
                exit(1);
            default:
                print_help_message();
                exit(0);
        }
    }

    if (hours < 0 || hours > 24) {
        printf("error: hours must be between 0 and 24\n");
        exit(1);
    }

    kwh = kilowatt_hours(watts, hours);
    cpd = cost_per_day(kwh, price);

    printf("\n");
    printf("      %.0f bulbs @ %-5.2f watts\n", bulbs, watts);
    printf("        %-4.1f hours / day\n", hours);
    printf("  +--------+---------+--------+\n");
    printf("  | $/week | $/month | $/year |\n");
    printf("  +--------+---------+--------+\n");
    printf("  |$%-6.2f |$%-6.2f  |$%-6.2f |\n", cost_per_week(cpd), cost_per_month(cpd), cost_per_year(cpd));
    printf("  +--------+---------+--------+\n");
    printf("  |Expected Life: %-6.2f years|\n", life_in_years(life, hours));
    printf("  +---------------------------+\n\n");

    exit(0);
}
