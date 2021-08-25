#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

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
        bulbs = 1,
        price_per_day,
        price_per_month,
        price_per_year,
        lifespan = 11000;

    char *badchar;

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
                lifespan = strtod(optarg, &badchar);

                if (*badchar != '\0') {
                    printf("error: lifespan should be a number\n");
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

    price_per_day = (watts / 1000) * price * hours * bulbs;
    price_per_month = price_per_day * 30;
    price_per_year = price_per_day * 365;

    printf("\n");
    printf("     %.0f bulbs @ %-5.2f watts\n", bulbs, watts);
    printf("       %-4.1f hours / day\n", hours);
    printf("  +-------+---------+--------+\n");
    printf("  | $/day | $/month | $/year |\n");
    printf("  +-------+---------+--------+\n");
    printf("  |$%-6.2f|$%-6.2f  |$%-6.2f |\n", price_per_day, price_per_month, price_per_year);
    printf("  +-------+---------+--------+\n");
    printf("  | Lifespan: %-6.2f years   |\n", lifespan / hours / 365);
    printf("  +--------------------------+\n\n");

    exit(0);
}
